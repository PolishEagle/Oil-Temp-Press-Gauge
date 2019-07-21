#include <SPI.h>
#include "LedDriver.h"

// PD4 - temp LED enable
// PD2 - temp LED driver enable
// PD3 - pressure LED enable
// PD1 - pressure LED driver enable
#define TEMP_LED_EN 4
#define TEMP_DRIVER_EN 0
#define PRESS_LED_EN 1
#define PRES_DRIVER_EN 2

LedDriver _oilTempLedDriver;
LedDriver _oilPressLedDriver;

void setup()
{
    Serial.end();
    pinMode(TEMP_LED_EN, OUTPUT);
    pinMode(TEMP_DRIVER_EN, OUTPUT);
    pinMode(PRESS_LED_EN, OUTPUT);
    pinMode(PRES_DRIVER_EN, OUTPUT);
    
    digitalWrite(TEMP_DRIVER_EN, LOW);
    digitalWrite(PRES_DRIVER_EN, LOW);
    
    digitalWrite(TEMP_LED_EN, HIGH);
    digitalWrite(PRESS_LED_EN, HIGH);
    SPI.begin();

    _oilTempLedDriver.InitializeDriver(
        0x00,
        TEMP_DRIVER_EN);

    _oilPressLedDriver.InitializeDriver(
        0x02,
        PRES_DRIVER_EN);

    _oilTempLedDriver.SetBrightness(0x0B);
    _oilPressLedDriver.SetBrightness(0x0B);
}

void loop()
{
    for (int i = 0; i < 189; i++)
    {
        _oilTempLedDriver.DisplayNumber(i);
        _oilPressLedDriver.DisplayNumber(i);
        delay(150);
    }
}

