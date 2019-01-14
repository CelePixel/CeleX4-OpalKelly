/*
* Copyright (c) 2017-2017-2018 CelePixel Technology Co. Ltd. All Rights Reserved
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
#define BIN_FILE	"BIN"	//your bin file path

int main()
{
	CeleX4 *pCelex = new CeleX4;

	if (pCelex == NULL)
		return 0;
	pCelex->openPlaybackFile(BIN_FILE);	//open the bin file
	pCelex->setFpnFile(FPN_PATH);
	pCelex->setEventFrameParameters(60, 60);	//frame time and interval time just available for event mode
    //pCelex->enableOpticalFlow(true);	//enableOpticalFlow if you want to get the optical flow buffer

	while (true)
	{
		pCelex->readPlayBackData();	//start reading the bin file

		if (pCelex->getAttributes(BIN_FILE).mode == FullPictureMode)	//if the bin file is fullpic mode
		{
			if (!pCelex->getFullPicMat().empty())
			{				
				cv::Mat fullPicMat = pCelex->getFullPicMat();
				cv::imshow("FullPic", fullPicMat);
			}
		}
		else if (pCelex->getAttributes(BIN_FILE).mode == EventMode)		//if the bin file is event mode
		{
			if (!pCelex->getEventPicMat(EventBinaryPic).empty())
			{
				cv::Mat eventAccPicMat = pCelex->getEventPicMat(EventAccumulatedPic);	//the parameter in this method is emEventPicMode
				cv::imshow("Event-FullPic", eventAccPicMat);
				cv::Mat eventPicMat = pCelex->getEventPicMat(EventBinaryPic);
				cv::imshow("Event-EventPic", eventPicMat);
				//cv::Mat opticalFlow = pCelex->getOpticalFlowPicMat();	//get optical flow buffer if enableOpticalFlow is true
				//cv::imshow("OpticalFlow", opticalFlow);
			}
		}
		else if (pCelex->getAttributes(BIN_FILE).mode == FullPic_Event_Mode)		//if the bin file is fullpic-event mode
		{
			if (!pCelex->getEventPicMat(EventBinaryPic).empty())
			{
				cv::Mat fullPicMat = pCelex->getFullPicMat();
				cv::Mat eventPicMat = pCelex->getEventPicMat(EventBinaryPic);
				cv::imshow("FE-FullPic", fullPicMat);
				cv::imshow("FE-EventPic", eventPicMat);
			}
		}
		cv::waitKey(10);
	}
	return 1;
}