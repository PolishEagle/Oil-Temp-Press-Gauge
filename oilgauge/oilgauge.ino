#include <SPI.h>
#include "LedDriver.h"
#include "OilPressureSensor.h"
#include "OilTemperatureSensor.h"

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
OilTemperatureSensor _oilTemperatureSensor;
OilPressureSensor _oilPressureSensor;

void setup()
{
    Serial.end();
    pinMode(TEMP_LED_EN, OUTPUT);
    pinMode(TEMP_DRIVER_EN, OUTPUT);
    pinMode(PRESS_LED_EN, OUTPUT);
    pinMode(PRES_DRIVER_EN, OUTPUT);
    
    digitalWrite(TEMP_DRIVER_EN, LOW);
    digitalWrite(PRES_DRIVER_EN, LOW);
    SPI.begin();

    _oilTempLedDriver.InitializeDriver(
        0x00,
        TEMP_DRIVER_EN);

    _oilPressLedDriver.InitializeDriver(
        0x02,
        PRES_DRIVER_EN);

    // 0x18 is the max output (24mA)
    _oilTempLedDriver.SetBrightness(0x01);
    _oilPressLedDriver.SetBrightness(0x01);
}

void loop()
{
    _oilTempLedDriver.DisplayNumber(
        _oilTemperatureSensor.GetTemperature());
    _oilPressLedDriver.DisplayNumber(
        _oilPressureSensor.GetPressure());

    delay(500);
}

