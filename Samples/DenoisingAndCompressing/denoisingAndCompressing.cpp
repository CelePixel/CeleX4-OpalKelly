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
#include <vector>
#define MAT_ROWS 640
#define MAT_COLS 768
#define FPN_PATH    "../Samples/config/FPN.txt"

#ifdef _WIN32
#include <windows.h>
#else
#include<unistd.h>
#endif

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
	void setCelex4(CeleX4* pCelex4) { m_pCelex4 = pCelex4; };
	CX4SensorDataServer*	m_pServer;
	CeleX4*					m_pCelex4;
};

void SensorDataObserver::onFrameDataUpdated(CeleX4ProcessedData* pSensorData)
{
	if (NULL == pSensorData)
		return;
	emSensorMode sensorMode = pSensorData->getSensorMode();

	if (EventMode == sensorMode)
	{
		cv::Mat mat = cv::Mat::zeros(cv::Size(MAT_COLS, MAT_ROWS), CV_8UC1);

		//you can get binary pic after denoising directly or use corresponding interface(denoisingByTimeInterval) on the raw data 
		//mat = pSensorData->getEventPicMat(EventDenoisedByTimeBinaryPic); //get binary pic after denoising directly

		std::vector<EventData> v = pSensorData->getEventDataVector();

		m_pCelex4->denoisingByTimeInterval(v,mat); //get binary pic after denosing by the interface
		
		//m_pCelex4->denoisingAndCompresing(v,0.5,mat);	//denoising and compressing


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
	emSensorMode sensorMode = EventMode; //EventMode
	pCelex->setSensorMode(sensorMode);
	SensorDataObserver* pSensorData = new SensorDataObserver(pCelex->getSensorDataServer());
	pSensorData->setCelex4(pCelex);
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