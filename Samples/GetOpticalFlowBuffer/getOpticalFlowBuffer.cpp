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

	pCelex->setSensorMode(EventMode);
	pCelex->enableOpticalFlow(true); //enable optical-flow option

	int imgSize = 768 * 640;

	unsigned char* pOpticalFlowBuffer = new unsigned char[imgSize];
	unsigned char* pOpticalFlowDirection = new unsigned char[imgSize];
	unsigned char* pOpticalFlowSpeed = new unsigned char[imgSize];

	while (true)
	{
		pCelex->pipeOutFPGAData();

		//get optical-flow data when sensor works in EventMode
		if (pCelex->getEventPicBuffer(EventBinaryPic))
		{
			//optical-flow raw data - display gray image
			memcpy(pOpticalFlowBuffer, pCelex->getOpticalFlowPicBuffer(), imgSize); //optical-flow raw buffer
			cv::Mat matOpticalRaw(640, 768, CV_8UC1, pOpticalFlowBuffer);

			//cv::Mat matOpticalRaw = pCelex->getOpticalFlowPicMat();	//You can get the Mat form of optical flow pic directly.
			cv::imshow("Optical-Flow Raw Buffer - Gray", matOpticalRaw);

			//optical-flow raw data - display color image
			cv::Mat matOpticalRawColor(640, 768, CV_8UC3);
			uchar* pRaw = matOpticalRawColor.ptr<uchar>(0);
			int index = 0;
			for (int i = 0; i < matOpticalRawColor.rows; ++i)
			{
				cv::Vec3b *p = matOpticalRawColor.ptr<cv::Vec3b>(i);
				for (int j = 0; j < matOpticalRawColor.cols; ++j)
				{
					int value = matOpticalRaw.at<uchar>(i, j);
					//std::cout << value << std::endl;
					if (value == 0)
					{
						p[j][0] = 0;
						p[j][1] = 0;
						p[j][2] = 0;
					}
					else if (value < 50)	//blue
					{
						p[j][0] = 255;
						p[j][1] = 0;
						p[j][2] = 0;
					}
					else if (value < 100)
					{
						p[j][0] = 255;
						p[j][1] = 255;
						p[j][2] = 0;
					}
					else if (value < 150)	//green
					{
						p[j][0] = 0;
						p[j][1] = 255;
						p[j][2] = 0;
					}
					else if (value < 200)
					{
						p[j][0] = 0;
						p[j][1] = 255;
						p[j][2] = 255;
					}
					else	//red
					{
						p[j][0] = 0;
						p[j][1] = 0;
						p[j][2] = 255;
					}
				}
			}
			cv::imshow("Optical-Flow Raw Buffer - Color", matOpticalRawColor);

			//direction
			memcpy(pOpticalFlowDirection, pCelex->getOpticalFlowDirectionPicBuffer(), imgSize); //optical-flow direction buffer
			cv::Mat matOpticalDirction(640, 768, CV_8UC1, pOpticalFlowDirection);

			//cv::Mat matOpticalDirction = pCelex->getOpticalFlowDirectionPicMat();	//You can also get the Mat form of optical flow direction pic directly.
			cv::imshow("Optical-Flow Dirction Buffer", matOpticalDirction);

			//speed
			memcpy(pOpticalFlowSpeed, pCelex->getOpticalFlowSpeedPicBuffer(), imgSize); //optical-flow direction buffer
			cv::Mat matOpticalSpeed(640, 768, CV_8UC1, pOpticalFlowSpeed);

			//cv::Mat matOpticalSpeed = pCelex->getOpticalFlowSpeedPicMat();//You can also get the Mat form of optical flow speed pic directly.
			cv::imshow("Optical-Flow Speed Buffer", matOpticalSpeed);

			cvWaitKey(10);
		}
	}
	return 1;
}