/*
* Copyright (c) 2017-2018 CelePixel Technology Co. Ltd. All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <opencv2/opencv.hpp>
#include <celex4/celex4.h>
#include <celex4/celex4datamanager.h>
#include <celex4/celex4processeddata.h>

#ifdef _WIN32
#include <windows.h>
#else
#include<unistd.h>
#endif

#define FPN_PATH    "./FPN.txt"
using namespace std;
using namespace cv;
class SensorDataObserver : public CeleX4DataManager
{
public:
	SensorDataObserver(CX4SensorDataServer* pServer)
	{
		m_pServer = pServer;
		m_pServer->registerData(this, CeleX4DataManager::CeleX_Frame_Data);
	}
	~SensorDataObserver()
	{
		m_pServer->registerData(this, CeleX4DataManager::CeleX_Frame_Data);
	}
	virtual void onFrameDataUpdated(CeleX4ProcessedData* pSensorData);//overrides Observer operation

	CX4SensorDataServer* m_pServer;
};

void SensorDataObserver::onFrameDataUpdated(CeleX4ProcessedData* pSensorData)
{
	if (NULL == pSensorData)
		return;
	emSensorMode sensorMode = pSensorData->getSensorMode(); //FullPic_Event_Mode or FullPictureMode

	if (EventMode == sensorMode)
	{
		FrameData data = pSensorData->getFrameDataVector(); //get raw event data and corresponding frame number
		cv::Mat mat = cv::Mat::zeros(cv::Size(768, 640), CV_8UC1);

		for (int i = 0; i < data.vecEventData.size() - 1; ++i)
		{
			mat.at<uchar>(640 - data.vecEventData[i].row - 1, 768 - data.vecEventData[i].col - 1) = 255;
		}

		vector<IMUData> imuData;
		imuData = pSensorData->getIMUDataVector(); //get IMU data include accelerometer and gyros parameters
		cout << "ACC:"<<imuData.back().x_ACC << "," << imuData.back().y_ACC <<"," << imuData.back().z_ACC << endl;
		cout << "GYROS:" << imuData.back().x_GYROS << "," << imuData.back().y_GYROS << "," << imuData.back().t_GYROS << endl;

		cv::imshow("show", mat);
		cv::waitKey(10);
	}
}

int main()
{
	CeleX4 *pCelex = new CeleX4;
	if (NULL == pCelex)
		return 0;

	pCelex->openSensor("");
	pCelex->setFpnFile(FPN_PATH);
	emSensorMode sensorMode = EventMode; //EventMode, FullPic_Event_Mode or FullPictureMode
	pCelex->setSensorMode(sensorMode);
	//pCelex->setIMUIntervalTime(200);	//set IMU interval time
	SensorDataObserver* pSensorData = new SensorDataObserver(pCelex->getSensorDataServer());

	while (true)
	{
		pCelex->pipeOutFPGAData();
#ifdef _WIN32
		Sleep(10);
#else
		usleep(1000 * 10);
#endif
	}
	return 1;
}