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
#define FPN_PATH    "../Samples/config/FPN.txt"

int main()
{
	CeleX4 *pCelex = new CeleX4;
	if (NULL == pCelex)
		return 0;
	pCelex->openSensor("");
	pCelex->setFpnFile(FPN_PATH);

	emSensorMode sensorMode = FullPictureMode; //EventMode, FullPic_Event_Mode and FullPictureMode
	pCelex->setSensorMode(sensorMode);

	int imgSize = 768 * 640;

	unsigned char* pFullPicBuffer = new unsigned char[imgSize];
	unsigned char* pEventBuffer = new unsigned char[imgSize];

	while (true)
	{
		pCelex->pipeOutFPGAData();

		if (sensorMode == FullPictureMode)
		{
			//get fullpic when sensor works in FullPictureMode
			if (pCelex->getFullPicBuffer())
			{
				pFullPicBuffer = pCelex->getFullPicBuffer();
				memcpy(pFullPicBuffer, pCelex->getFullPicBuffer(), imgSize); //full pic
				cv::Mat matFullPic(640, 768, CV_8UC1, pFullPicBuffer);
				cv::imshow("FullPic", matFullPic);
				cvWaitKey(10);
			}
		}
		else if (sensorMode == EventMode)
		{
			//get buffers when sensor works in EventMode
			if (pCelex->getEventPicBuffer(EventBinaryPic))
			{
				memcpy(pFullPicBuffer, pCelex->getEventPicBuffer(EventAccumulatedPic), imgSize); //event accumulative pic
				memcpy(pEventBuffer, pCelex->getEventPicBuffer(EventBinaryPic), imgSize); //event binary pic
				cv::Mat matFullPic(640, 768, CV_8UC1, pFullPicBuffer);
				cv::Mat matEventPic(640, 768, CV_8UC1, pEventBuffer);

				cv::imshow("Event-FullPic", matFullPic);
				cv::imshow("Event-EventPic", matEventPic);
				cvWaitKey(10);
			}
		}
		else if (sensorMode == FullPic_Event_Mode)
		{
			//get buffers when sensor works in FullPic_Event_Mode
			if (pCelex->getEventPicBuffer(EventBinaryPic))
			{
				memcpy(pFullPicBuffer, pCelex->getFullPicBuffer(), imgSize); //full pic
				memcpy(pEventBuffer, pCelex->getEventPicBuffer(EventBinaryPic), imgSize); //event binary pic
				cv::Mat matFullPic(640, 768, CV_8UC1, pFullPicBuffer);
				cv::Mat matEventPic(640, 768, CV_8UC1, pEventBuffer);
				cv::imshow("FE-FullPic", matFullPic);
				cv::imshow("FE-EventPic", matEventPic);
				cvWaitKey(10);
			}
		}
	}
	return 1;
}
