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

#define MAX_PRESSURE_VALUES 32
#define MAX_TEMPERATURE_VALUES 128

int _temperatureMovingAverage;
int _pressureMovingAverage;
long _totalPressureValues;
long _totalTemperatureValues;
unsigned long _displayTime;

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
        0x01,
        PRES_DRIVER_EN);

    _displayTime = millis();

    // 0x18 is the max output (24mA)
    _oilTempLedDriver.SetBrightness(0x01);
    _oilPressLedDriver.SetBrightness(0x01);

    _temperatureMovingAverage = _oilTemperatureSensor.GetTemperature();
    _pressureMovingAverage = _oilPressureSensor.GetPressure();
    _totalPressureValues = 1;
    _totalTemperatureValues = 1;
}

void FlashDisplayAsRequired(int oilPressure)
{ 
    if (oilPressure <= 15 && (millis() - _displayTime) > 400 && oilPressure > 0)
    {
        _oilTempLedDriver.SetBrightness(0x16);
        _oilPressLedDriver.SetBrightness(0x16);

        _displayTime = millis();
        return;
    }
    else if (oilPressure <= 15 && (millis() - _displayTime) < 200 && oilPressure > 0)
    {
        return;
    }
      
    // Reset the LED brightness
    _oilTempLedDriver.SetBrightness(0x01);
    _oilPressLedDriver.SetBrightness(0x01);
}

void loop()
{
    _totalPressureValues += 1;
    _totalTemperatureValues += 1;
    int currentPressure = _oilPressureSensor.GetPressure();
    int currentTemp = _oilTemperatureSensor.GetTemperature();

    // average = average + (value - average) / min(counter, FACTOR)
    _temperatureMovingAverage = _temperatureMovingAverage + 
          ((currentTemp - _temperatureMovingAverage) / min(_totalTemperatureValues, MAX_TEMPERATURE_VALUES));

    _pressureMovingAverage = _pressureMovingAverage + 
          ((currentPressure - _pressureMovingAverage) / min(_totalPressureValues, MAX_PRESSURE_VALUES));
  
    _oilTempLedDriver.DisplayNumber(_temperatureMovingAverage);
    _oilPressLedDriver.DisplayNumber(_pressureMovingAverage);

    FlashDisplayAsRequired(currentPressure);
    
    delay(100);
}
