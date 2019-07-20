#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <SPI.h>

class LedDriver
{
    private:
        byte _driverAddress;
        int _driverChipSelect;

        void SetDefaultLedCurrent();
        void SetDefaultLedOnOff();
        void SetDefaultLedOutputPriority();
        void SetDefaultLedFadeFunction();
        void SetDefaultLedCompulsionValue();
        void SetDefaultLedPwmDuty();
        void Setup();
        void SendData(byte data[], int arraySize);

    public:
        void InitializeDriver(byte address, int driverChipSelect);
        void DisplayNumber(int number);
};

#endif
