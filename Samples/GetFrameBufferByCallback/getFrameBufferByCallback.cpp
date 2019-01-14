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
	if (FullPictureMode == sensorMode)
	{
		//get fullpic when sensor works in FullPictureMode
		if (pSensorData->getFullPicBuffer())
		{
			cv::Mat matFullPic(640, 768, CV_8UC1, pSensorData->getFullPicBuffer()); //full pic
			cv::imshow("FullPic", matFullPic);
			cv::waitKey(30);
		}
	}
	else if (EventMode == sensorMode)
	{
		//get buffers when sensor works in EventMode
		if (pSensorData->getEventPicBuffer(EventBinaryPic))
		{
			cv::Mat matFullPic(640, 768, CV_8UC1, pSensorData->getEventPicBuffer(EventAccumulatedPic)); //event accumulative pic
			cv::Mat matEventPic(640, 768, CV_8UC1, pSensorData->getEventPicBuffer(EventBinaryPic)); //event binary pic
			cv::imshow("EventAccumulatedPic", matFullPic);
			cv::imshow("EventPic", matEventPic);
			cvWaitKey(30);
		}
	}
	else if (FullPic_Event_Mode == sensorMode)
	{
		//get buffers when sensor works in FullPic_Event_Mode
		if (pSensorData->getEventPicBuffer(EventBinaryPic))
		{
			cv::Mat matFullPic(640, 768, CV_8UC1, pSensorData->getFullPicBuffer()); //full pic
			cv::Mat matEventPic(640, 768, CV_8UC1, pSensorData->getEventPicBuffer(EventBinaryPic)); //event binary pic
			cv::imshow("FullPic", matFullPic);
			cv::imshow("EventPic", matEventPic);
			cvWaitKey(30);
		}
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