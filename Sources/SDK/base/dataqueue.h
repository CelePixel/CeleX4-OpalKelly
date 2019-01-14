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

#ifndef HHDATAQUEUE_H
#define HHDATAQUEUE_H

#include <queue>
#include <stdint.h>

typedef struct DataInfo
{
    unsigned char* pData;
    unsigned long  length;
} DataInfo;

class DataQueue
{
public:
    DataQueue();
    ~DataQueue();

    void push(unsigned char* pData, long length);
    void pop(unsigned char*& pData, long* length);
	unsigned long size();
    void clear();

private:
    std::queue<DataInfo> m_queue;
    unsigned long        m_size;
};


class CirDataQueue
{
public:
    CirDataQueue(int queueCapacity);
    ~CirDataQueue();

    int getLength(); //get the length of the queue
    int getCapacity();

    bool enqueue(unsigned char* pData);  //push a element
    bool dequeue(unsigned char*& pData); //pop a element
    bool isEmpty();
    bool isFull();
    void clear();
    unsigned char* head();

private:
    std::vector<DataInfo>  m_queue;
    int                    m_iHead;
    int                    m_iTail;
    int                    m_iQueueLenth;
    int                    m_iQueueCapacity;
};

#endif // HHDATAQUEUE_H