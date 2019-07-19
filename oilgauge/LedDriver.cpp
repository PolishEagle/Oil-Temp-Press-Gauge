#include "LedDriver.h"

SPISettings _spiSettings(4000000, MSBFIRST, SPI_MODE0);

LedDriver::InitializeDriver(
    byte address,
    int driverChipSelect)
{
    _driverAddress = 0x80 | address;
    _driverChipSelect = driverChipSelect;

    Setup();
}

void LedDriver::Setup()
{
    bool isMaster = _driverAddress & 0x1F == 0;
    byte data[] = { _driverAddress, 0x00, isMaster ? 0x00 : 0x02, 0x0,
        0x0,  // RLED 4:0 current value
        0x0,  // GLED 4:0 current value
        0x0,  // BLED 4:0 current value
    };
    SendData(data);
}

void LedDriver::SendData(byte data[])
{
    int numBytes = sizeof(data) / sizeof(data[0]);
  
    SPI.beginTransaction(_spiSettings);
    digitalWrite(_driverChipSelect, HIGH);
    SPI.transfer(data, numBytes);
    digitalWrite(_driverChipSelect, LOW);
    SPI.endTransaction();
}

