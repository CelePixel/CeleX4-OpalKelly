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
#define BIN_FILE    "BIN"	//your bin file path
#define FPN_PATH    "../Samples/config/FPN.txt"

int main()
{
	CeleX4 *pCelex = new CeleX4;
	cv::VideoWriter writer("event.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30, cv::Size(768, 640), false);

	pCelex->openPlaybackFile(BIN_FILE);	//open bin file
	pCelex->setFpnFile(FPN_PATH);

	pCelex->convertBinToAVI(BIN_FILE, EventBinaryPic, 60, 60, writer);	//convert bin to .avi,you can specify the event pic mode, frame time and interval time
	//pCelex->convertBinToAVI(BIN_FILE, writer);	//convert bin to .avi especially for full pic 
	return 1; 
}