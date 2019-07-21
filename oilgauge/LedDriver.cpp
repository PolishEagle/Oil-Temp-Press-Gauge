#include "LedDriver.h"

void LedDriver::InitializeDriver(
    byte address,
    int driverChipSelect)
{
    // Need to bit shift the address over 1 since 0 isn't used
    _driverAddress = 0x80 | address;
    _driverChipSelect = driverChipSelect;

    Setup();
}

void LedDriver::DisplayNumber(int number)
{
    byte segmentValue[] = {
        0x3F,
        0x06,
        0x5B,
        0x4F,
        0x66,
        0x6D,
        0x7D,
        0x07,
        0x7F,
        0x6F
    };

    byte digits[] = { 0x0, 0x0, 0x0 };

    for (int i = 0; i < 3; i++)
    {
        digits[i] = number % 10;
        number /= 10;
    }

    byte digit2 = digits[2] == 0 ? 0x00 : segmentValue[digits[2]];
    byte digit1 = digits[2] == 0 && digits[1] == 0 ? 0x00 : segmentValue[digits[1]];
    byte digit0 = segmentValue[digits[0]];
    
    byte data[] = { _driverAddress, 0x12, digit2, digit1, digit0 };
    SendData(data, 5);
}

void LedDriver::SetBrightness(byte level)
{
    SetDefaultLedCurrent(level);
}

void LedDriver::Setup()
{
    SetDefaultLedCurrent();
    SetDefaultLedOnOff();
    SetDefaultLedOutputPriority();
    SetDefaultLedCompulsionValue();
    SetDefaultLedFadeFunction();
    SetDefaultLedPwmDuty();
}

void LedDriver::SetDefaultLedCurrent(byte level = 0)
{
    bool isMaster = _driverAddress & 0x1F == 0;

    // Set LED current for all
    byte data[] = { _driverAddress, 0x00, isMaster ? 0x00 : 0x02, 0x0,
        level,  // RLED 4:0 current value
        level,  // GLED 4:0 current value
        level,  // BLED 4:0 current value
    };
    SendData(data, 7);
}

void LedDriver::SetDefaultLedOnOff()
{
    byte data[] = { _driverAddress, 0x05, 0x00, 0x00, 0x00, 0x00 };
    SendData(data, 6);
}

void LedDriver::SetDefaultLedOutputPriority()
{
    // Set output priority to compulsion ON/OFF
    byte data[] = { _driverAddress, 0x09, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };
    SendData(data, 8);
}

void LedDriver::SetDefaultLedCompulsionValue()
{
    // Set output priority to compulsion ON/OFF
    byte data[] = { _driverAddress, 0x12, 0x00, 0x00, 0x00 };
    SendData(data, 5);
}

void LedDriver::SetDefaultLedFadeFunction()
{
    // Set LED fade function
    byte data[] = { _driverAddress, 0x0F, 0x00, 0x00, 0x00 };
    SendData(data, 5);
}

void LedDriver::SetDefaultLedPwmDuty()
{
    byte data[] = { _driverAddress, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    SendData(data, 26);
}

void LedDriver::SendData(byte data[], int arraySize)
{
    int numBytes = sizeof(data) / sizeof(data[0]);
    
    SPISettings spiSettings(5000000, MSBFIRST, SPI_MODE0);
    SPI.beginTransaction(spiSettings);
    digitalWrite(_driverChipSelect, HIGH);
    SPI.transfer(data, arraySize);
    digitalWrite(_driverChipSelect, LOW);
    SPI.endTransaction();
}

