/*
* Copyright (c) 2017-2018  CelePixel Technology Co. Ltd.  All rights reserved.
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

#include "dataprocessthread.h"
#include <iostream>

using namespace std;

DataProcessThread::DataProcessThread(const std::string &name)
	: XThread(name)
	, m_emPlaybackState(CeleX4::NoBinPlaying)
{
}

DataProcessThread::~DataProcessThread()
{
	delete[] m_pData;
	m_pData = NULL;
}

void DataProcessThread::addData(unsigned char *data, long length)
{
	m_queueData.push(data, length);
}

void DataProcessThread::clearData()
{
	m_queueData.clear();
	m_dataProcessor.cleanBuffer();
}

void DataProcessThread::setSensorMode(emSensorMode mode)
{
	m_queueData.clear();
	m_dataProcessor.setSensorMode(mode);
}

uint32_t DataProcessThread::queueSize()
{
	return m_queueData.size();
}

FPGADataProcessor *DataProcessThread::getDataProcessor()
{
	return &m_dataProcessor;
}

CeleX4::PlaybackState DataProcessThread::getPlaybackState()
{
	return m_emPlaybackState;
}

void DataProcessThread::setPlaybackState(CeleX4::PlaybackState state)
{
	m_emPlaybackState = state;
	m_dataProcessor.setPlaybackState(state);
}

void DataProcessThread::run()
{
	while (m_bRun)
	{
		//cout << "---------- DataProcessThread::run ----------" << endl;
#ifndef _WIN32
		pthread_mutex_lock(&m_mutex);
		while (m_bSuspended)
		{
			pthread_cond_wait(&m_cond, &m_mutex);
		}
		pthread_mutex_unlock(&m_mutex);
#endif
		if (getPlaybackState()== CeleX4::NoBinPlaying)
		{
			if (m_queueData.size() > 0)
			{
				unsigned char* data = 0;
				long dataLen = 0;
				m_queueData.pop(data, &dataLen);
				if (dataLen > 0)
				{
					m_dataProcessor.processData(data, dataLen);
					delete[] data;
				}
			}	
		}
		else if(getPlaybackState() == CeleX4::Playing)
		{
			if (m_queueData.size() > 0)
			{
				unsigned char* data = 0;
				long dataLen = 0;
				m_queueData.pop(data, &dataLen);
				if (dataLen > 0)
				{
					m_dataProcessor.processData(data, dataLen);
					delete[] data;
				}
			}
			else
			{
				if (m_emPlaybackState == CeleX4::BinReadFinished)
				{
					m_emPlaybackState = CeleX4::PlayFinished;
					m_dataProcessor.setPlaybackState(CeleX4::PlayFinished);
				}
			}
		}
	}
}