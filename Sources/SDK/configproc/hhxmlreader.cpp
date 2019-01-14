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

#include "hhxmlreader.h"
#include "../base/xbase.h"
#include "hhwireincommand.h"
#include "hhdelaycommand.h"
#include "hhsequencemgr.h"
#include "tinyxml/tinyxml.h"
#include <iostream>

HHXmlReader::HHXmlReader()
{
}

HHXmlReader::~HHXmlReader()
{
}

bool HHXmlReader::parse(const string &filename, TiXmlDocument *pDom)
{
    if (!pDom)
    {
        return false;
    }
    XBase base;
    string filePath = base.getApplicationDirPath();
#ifdef _WIN32
    filePath += "\\";
#endif
    filePath += filename;
    bool loadOk = pDom->LoadFile(filePath.c_str());
    if (!loadOk)
    {
        cout << "Can't load: " << pDom->ErrorDesc() << filePath;
    }
    return true;
}

bool HHXmlReader::importCommands(std::vector<HHCommandBase *> &commandList, TiXmlDocument *pDom)
{ 
    cout << endl << "********** HHXmlReader::importCommands Begin **********" << endl;
    TiXmlElement *pRootEle = pDom->RootElement();
    if (string(pRootEle->Value()) != "commands")
    {
        cout << "Can't find commands in xml." << endl;
        return false;
    }
    for (TiXmlElement *pEle = pRootEle->FirstChildElement();
         NULL != pEle; pEle = pEle->NextSiblingElement())
    {
        TiXmlAttribute *pAttr = pEle->FirstAttribute();
        std::string commandName = pAttr->Value();
        cout << pAttr->Name() << ": " << pAttr->Value() << endl;

        for (TiXmlElement* pChildEle = pEle->FirstChildElement();
             NULL != pChildEle;
             pChildEle = pChildEle->NextSiblingElement())
        {
            std::string subCommandName = pChildEle->Value();
            if ("wirein" == subCommandName)
            {
                HHWireinCommand* pCmd = new HHWireinCommand(commandName);
                TiXmlNode* pNode = pChildEle->FirstChild();
                while (NULL != pNode)
                {
                    //address: 0x00;
                    //value:   0x01;
                    //mask:    0x01 
                    string tagName = pNode->Value();
                    uint32_t value;
                    getNumber(pNode->FirstChild()->Value(), &value);
                    //cout << "------- " << pNode->Value() << " " << pNode->FirstChild()->Value() << " " << value << endl;
                    if ("address" == tagName)
                    {
                        pCmd->setAddress(value);
                    }
                    else if ("value" == tagName)
                    {
                        pCmd->setValue(value);
                    }
                    else if (tagName == "mask")
                    {
                        pCmd->setMask(value);
                    }
                    else
                    {
                        cout << "********** command unknow tagName **********" << tagName << endl;
                    }
                    pNode = pNode->NextSiblingElement();
                }
                commandList.push_back(pCmd);
            }
            else if ("wait" == subCommandName)
            {
                HHDelayCommand* pCmd = new HHDelayCommand(commandName);
                TiXmlNode* pNode = pChildEle->FirstChild();
                while (NULL != pNode)
                {
                    string tagName = pNode->Value();
                    uint32_t value;
                    bool bOk = getNumber(pNode->FirstChild()->Value(), &value);
                    //cout << "------- " << pNode->Value() << " " << pNode->FirstChild()->Value() << " " << value << endl;
                    if (!bOk)
                    {
                        //--- invalid value ---
                        pCmd->valid(false);
                        pCmd->error("Invalid param value for " + tagName);
                    }
                    if ("duration" == tagName)
                    {
                        pCmd->setDuration(value);
                    }
                    else
                    {
                        cout << "Unknown tageName:" << tagName;
                    }
                    pNode = pNode->NextSiblingElement();
                }
                commandList.push_back(pCmd);
            }
        }
    }
    cout << "********** HHXmlReader::importCommands End **********" << endl << endl;
    return true;
}

bool HHXmlReader::importSequences(HHSequenceMgr *pSeqMgr, std::vector<HHSequence *> &sequenceList, TiXmlDocument *pDom)
{
    cout << endl << "********** HHXmlReader::importSequences Begin **********" << endl;
    TiXmlElement *pRootEle = pDom->RootElement();
    if (string(pRootEle->Value()) != "sequences")
    {
        cout << "Can't find sequences in xml." << endl;
        return false;
    }
    for (TiXmlElement *pEle = pRootEle->FirstChildElement();
         NULL != pEle; pEle = pEle->NextSiblingElement())
    {
        HHSequence* pSeq = NULL;
        std::string seqName;
        TiXmlAttribute *pAttr = pEle->FirstAttribute();
        while (NULL != pAttr)
        {
            cout << pAttr->Name() << ": " << pAttr->Value() << "; ";
            string key = pAttr->Name();
            string value = pAttr->Value();
            if ("name" == key)
            {
                seqName = value;
                pSeq = new HHSequence(seqName);
            }
            else if ("show" == key)
            {
                bool bShow = (value != "no");
                pSeq->setShow(bShow);
            }
            else if ("advanced" == key)
            {
                bool bAdvanced = (value == "yes");
                pSeq->setAdvanced(bAdvanced);
            }
            else if ("next" == key)
            {
                pSeq->setNext(value);
            }
            pAttr = pAttr->Next();
        }
        cout << endl;
        for (TiXmlElement* pChildEle = pEle->FirstChildElement();
             NULL != pChildEle;
             pChildEle = pChildEle->NextSiblingElement())
        {
            std::string commandName = pChildEle->Value();
            if ("command" == commandName || "system" == commandName)
            {
                string keyName = pChildEle->FirstAttribute()->Name();
                string value = pChildEle->FirstAttribute()->Value();
                //cout << "------- " "keyName = " << keyName << "; value = " << value << endl;
                HHCommandBase* pCmd = NULL;
                if ("command" == commandName)
                {
                    pCmd = pSeqMgr->getCommandByName(value);
                }
                if (pCmd)
                {
                    pSeq->addCommand(pCmd);
                }
                else
                {
                    cout << "Command in sequence not found: " << value << endl;
                }
            }
            else
            {
                cout << "Unknown tageName (only command/system tag allowed): " << commandName << endl;
            }
        }
        sequenceList.push_back(pSeq);
    }
    cout << "********** HHXmlReader::importSequences End **********" << endl << endl;;
    return true;
}

bool HHXmlReader::importSliders(HHSequenceMgr *pSeqMgr, std::vector<HHSequence *> &sliderList, TiXmlDocument *pDom)
{
    cout << endl;
    cout << "********** HHXmlReader::importSliders Begin **********" << endl;
    TiXmlElement *pRootEle = pDom->RootElement();
    if (string(pRootEle->Value()) != "sliders")
    {
        cout << "Can't find sliders in xml." << endl;
        return false;
    }
    for (TiXmlElement *pEle = pRootEle->FirstChildElement();
         NULL != pEle; pEle = pEle->NextSiblingElement())
    {
        TiXmlAttribute *pAttr = pEle->FirstAttribute();
        string strSliderName;
        string strMin;
        string strMax;
        string strStep;
        string strInitial;
        string strShow;
        string strAdvanced;
        while (NULL != pAttr)
        {
            cout << pAttr->Name() << ": " << pAttr->Value() <<  "; ";
            string key = pAttr->Name();
            string value = pAttr->Value();
            if ("name" == key)
            {
                strSliderName = value;
            }
            else if ("min" == key)
            {
                strMin = value;
            }
            else if ("max" == key)
            {
                strMax = value;
            }
            else if ("step" == key)
            {
                strStep = value;
            }
            else if ("initial" == key)
            {
                strInitial = value;
            }
            else if ("show" == key)
            {
                strShow = value;
            }
            else if ("advanced" == key)
            {
                strAdvanced = value;
            }
            pAttr = pAttr->Next();
        }
        cout << endl;
        uint32_t min, max, step, initial;
        if (!getNumber(strMin, &min) || !getNumber(strMax, &max) || !getNumber(strInitial, &initial))
        {
            cout << "Invalid slider min/max/initial value for slider: " << strSliderName << endl;
            continue;
        }
        if (!getNumber(strStep, &step))
        {
            step = 10;
        }
        HHSequenceSlider* pSeq = new HHSequenceSlider(strSliderName, min, max, step);
        pSeq->setValue(initial);

        bool bShow = (strShow != "no");
        pSeq->setShow(bShow);

        bool bAdvanced = (strAdvanced == "yes");
        pSeq->setAdvanced(bAdvanced);

        for (TiXmlElement* pChildEle = pEle->FirstChildElement();
             NULL != pChildEle;
             pChildEle = pChildEle->NextSiblingElement())
        {
            std::string commandName = pChildEle->Value();
            TiXmlAttribute *pAttr = pChildEle->FirstAttribute();
            map<string, string> mapElement;
            while (NULL != pAttr)
            {
                mapElement[pAttr->Name()] = pAttr->Value();
                //cout << "------- " << pAttr->Name() << ": " << pAttr->Value() << endl;
                pAttr = pAttr->Next();
            }
            if ("command" == commandName || "system" == commandName)
            {
                string cmdName = mapElement["name"];
                HHCommandBase* pCmd = NULL;
                if (commandName == "command")
                {
                    pCmd = pSeqMgr->getCommandByName(cmdName);
                }
                if ((string::npos != cmdName.find("#value#")) && pCmd)
                    pCmd->needsArg(true);

                bool bHasFixedValue = (string::npos != cmdName.find("#fixed value#"));
                if (bHasFixedValue && pCmd)
                {
                    pCmd = pCmd->clone();
                }
                if (pCmd)
                {
                    if (pCmd->needsArg() || bHasFixedValue)
                    {
                        string arg = mapElement["value"];
                        uint32_t value;
                        bool bOk = getNumber(arg, &value);

                        if (bOk)
                        {
                            pCmd->setValue(value);
                        }
                        else
                        {
                            cout << "Invalid slider initial value: " << arg << endl;
                        }
                    }
                    pSeq->addCommand(pCmd);
                }
                else
                {
                    cout << "Command in sequence not found: " << cmdName << endl;
                }
            }
            else
            {
                cout << "Unknown tageName (only command or system tag allowed): " << commandName << endl;
            }
        }
        sliderList.push_back(pSeq);
    }
    cout << "********** HHXmlReader::importSliders End **********" << endl << endl;
    return true;
}

bool HHXmlReader::getNumber(const string &text, uint32_t *pNumber)
{
    if (string::npos != text.find("0x") || string::npos != text.find("0X"))
    {
        *pNumber = strtoul(text.c_str(), NULL, 16);
    }
    else
    {
        *pNumber = strtoul(text.c_str(), NULL, 10);
    }
    return true;
}




