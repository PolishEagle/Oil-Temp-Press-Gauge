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

void setup()
{
    Serial.end();
    pinMode(TEMP_LED_EN, OUTPUT);
    pinMode(TEMP_DRIVER_EN, OUTPUT);
    pinMode(PRESS_LED_EN, OUTPUT);
    pinMode(PRESS_LED_EN, OUTPUT);
    
    digitalWrite(TEMP_DRIVER_EN, LOW);
    digitalWrite(PRES_DRIVER_EN, LOW);
    
    digitalWrite(TEMP_LED_EN, HIGH);
    //digitalWrite(PRESS_LED_EN, HIGH);
    SPI.begin();
}

void loop()
{
    delay(3000);
}

