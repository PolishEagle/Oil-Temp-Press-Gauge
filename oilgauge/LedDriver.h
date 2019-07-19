#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <SPI.h>

class LedDriver
{
    private:
        byte _driverAddress;
        int _driverChipSelect;

        void SendData(byte data[]);

    public:
        InitializeDriver(byte address, int driverChipSelect);
        void Setup();
};

#endif
