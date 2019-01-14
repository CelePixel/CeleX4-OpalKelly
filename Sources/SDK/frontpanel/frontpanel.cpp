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

#include "frontpanel.h"

FrontPanel* FrontPanel::spFrontPanel = NULL;

void FrontPanel::initializeFPGA(const string &bitfileName)
{
    cout << "Begin initialize FPGA." << endl;
    if (!myxem->IsOpen())
    {
        if (okCFrontPanel::NoError != myxem->OpenBySerial())
        {
            cout << "FrontPanel Device not found..." << endl;
            return;
        }
    }
    std::string modelString = myxem->GetBoardModelString(myxem->GetBoardModel()); //first device model type
    cout << "Device type: " << modelString << endl;

    // Configure the PLL appropriately
    myxem->LoadDefaultPLLConfiguration();

    cout << "Device serial number: " << myxem->GetSerialNumber() << endl;
    cout << "Device ID string: " << myxem->GetDeviceID() << endl;

    if (okCFrontPanel::NoError != myxem->OpenBySerial(myxem->GetSerialNumber()))
    {
        cout << "Can't open Serial." << endl;
        return;
    }
    else
    {
        cout << "Serial opens successfully." << endl;
    }

    XBase base;
    std::string bitfilePath = base.getApplicationDirPath(); //+ "/" + bitfileName;
#ifdef _WIN32
    bitfilePath += "\\";
#endif
    bitfilePath += bitfileName;
    if (!base.isFileExists(bitfilePath))
    {
        return;
    }
    if (okCFrontPanel::NoError != myxem->ConfigureFPGA(bitfilePath))
    {
        cout << "Fail to load *.bit file!" << endl;
        return;
    }
    mReady = true;
    cout << "FPGA Ready." << endl;

    //operation_init_sensor_config();
    //operation_reset_dereset_ALL();
}

void FrontPanel::uninitializeFPGA()
{
    myxem->ResetFPGA();
    myxem->Close();
}

bool FrontPanel::wireIn(uint32_t address, uint32_t value, uint32_t mask)
{
    if (okCFrontPanel::NoError != myxem->SetWireInValue(address, value, mask))
    {
		cout << "------------------ WireIn error ------------------" << endl;
        return false;
    }
    myxem->UpdateWireIns();
    return true;
}

void FrontPanel::wireOut(uint32_t address, uint32_t mask, uint32_t *pValue)
{
    myxem->UpdateWireOuts();
    *pValue = (myxem->GetWireOutValue(address)) & mask;
}

long FrontPanel::blockPipeOut(uint32_t address, int blockSize, long length, unsigned char *data)
{
    //format is addr: blockSize: byte number: buffer
    long dataLen = myxem->ReadFromBlockPipeOut(address, blockSize, length, data);
    return dataLen;
}
