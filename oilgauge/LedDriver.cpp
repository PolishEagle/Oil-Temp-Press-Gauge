#include "LedDriver.h"

void LedDriver::InitializeDriver(
    byte address,
    int driverChipSelect)
{
    // Need to bit shift the address over 1 since 0 isn't used
    _driverAddress = 0x80 | (address << 1);
    _driverChipSelect = driverChipSelect;

    Setup();
}

void LedDriver::OhNoz()
{
    byte digit2, digit1, digit0;
    if (((_driverAddress >> 1) & 0x1) == 0x0)
    {
        digit2 = 0x7c;
        digit1 = 0x50;
        digit0 = 0x5c;
    }
    else
    {
        digit2 = 0x5e;
        digit1 = 0x79;
        digit0 = 0x5e;
    }
    
    byte data[] = { _driverAddress, 0x12, digit2, digit1, digit0 };
    SendData(data, 5);
}

void LedDriver::DisplayNumber(int number)
{
    byte digits[] = { 0x0, 0x0, 0x0 };
    bool isNegative = false;
    
    if (number < 0)
    {
        isNegative = true;
        number *= -1;
    }

    for (int i = 0; i < 3; i++)
    {
        digits[i] = number % 10;
        number /= 10;
    }
    
    byte digit2 = digits[2] == 0 ? 0x00 : _segmentValue[digits[2]];
    byte digit1 = digits[2] == 0 && digits[1] == 0 ? 0x00 : _segmentValue[digits[1]];
    byte digit0 = _segmentValue[digits[0]];

    if (isNegative)
    {
        if (digits[2] == 0 && digits[1] != 0)
        {
            digit2 = _negativeValue;
        }
        else if (digits[2] == 0 && digits[1] == 0 && digits[0] != 0)
        {
            digit1 = _negativeValue;
        }
    }
    
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

    // LED's can only take an absolute max of 25mA
    // So we'll limit them to 24mA max.
    if (level > 0x18)
    {
        level = 0x18;
    }

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
