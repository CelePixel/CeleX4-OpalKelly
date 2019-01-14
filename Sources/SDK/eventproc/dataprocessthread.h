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

#ifndef DATAPROCESSTHREAD_H
#define DATAPROCESSTHREAD_H

#include "../base/dataqueue.h"
#include "../base/xthread.h"
#include "fpgadataprocessor.h"
#include "../include/celex4/celex4.h"

class DataProcessThread : public XThread
{
public:
    DataProcessThread(const std::string& name = "DataProcessThread");
    ~DataProcessThread();

    void addData(unsigned char* data, long length);
    void clearData();
    void setSensorMode(emSensorMode mode);
    uint32_t queueSize();
    FPGADataProcessor* getDataProcessor();
    CeleX4::PlaybackState getPlaybackState();
    void setPlaybackState(CeleX4::PlaybackState	state);

protected:
    void run() override;

private:
    DataQueue                m_queueData;
    FPGADataProcessor        m_dataProcessor;
    unsigned char*           m_pData;
    //CirDataQueueEx           m_queueDataEx;
    CeleX4::PlaybackState    m_emPlaybackState;
	bool					 m_bPlaybackBinFile;
};

#endif // DATAPROCESSTHREAD_H
