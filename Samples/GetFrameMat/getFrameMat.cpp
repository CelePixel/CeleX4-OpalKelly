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

	if (pCelex == NULL)
		return 0;

	pCelex->openSensor("");	//open snsor
	pCelex->setFpnFile(FPN_PATH);	//load FPN file for denoising

	emSensorMode sensorMode = EventMode; //FullPic_Event_Mode or FullPictureMode
	pCelex->setSensorMode(sensorMode);

	while (true)
	{
		pCelex->pipeOutFPGAData();

		if (sensorMode == FullPictureMode)
		{
			if (!pCelex->getFullPicMat().empty())
			{
				cv::Mat fullPicMat = pCelex->getFullPicMat();
				cv::imshow("FullPic", fullPicMat);
				cv::waitKey(10);
			}
		}
		else if (sensorMode == EventMode)
		{
			if (!pCelex->getEventPicMat(EventBinaryPic).empty())
			{
				cv::Mat fullPicMat = pCelex->getEventPicMat(EventAccumulatedPic);	//the parameter in this method is emEventPicMode
				cv::imshow("Event-FullPic", fullPicMat);
				cv::Mat eventPicMat = pCelex->getEventPicMat(EventBinaryPic);
				cv::imshow("Event-EventPic", eventPicMat);
			}
			cv::waitKey(10);
		}
		else if (sensorMode == FullPic_Event_Mode)
		{
			if (!pCelex->getEventPicMat(EventBinaryPic).empty())
			{
				cv::Mat fullPicMat = pCelex->getFullPicMat();	
				cv::imshow("FE-FullPic", fullPicMat);
				cv::Mat eventPicMat = pCelex->getEventPicMat(EventBinaryPic);	//the parameter in this method is emEventPicMode
				cv::imshow("FE-EventPic", eventPicMat);
			}
			cv::waitKey(10);
		}
	}
	return 1;
}