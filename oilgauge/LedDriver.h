#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <SPI.h>

class LedDriver
{
    private:
        byte _driverAddress;
        int _driverChipSelect;
        byte _negativeValue = 0x40;
        byte _segmentValue[10] = {
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

        void SetDefaultLedCurrent(byte level = 0);
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
        void SetBrightness(byte level);
        void OhNoz();
};

#endif
