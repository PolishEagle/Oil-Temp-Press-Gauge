#include <SPI.h>

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
    pinMode(TEMP_LED_EN, OUTPUT);
    pinMode(TEMP_DRIVER_EN, OUTPUT);
    pinMode(PRESS_LED_EN, OUTPUT);
    pinMode(PRESS_LED_EN, OUTPUT);
    
    digitalWrite(TEMP_DRIVER_EN, LOW);
    digitalWrite(PRES_DRIVER_EN, LOW);

    delay(1000);

    digitalWrite(TEMP_LED_EN, HIGH);
    digitalWrite(TEMP_DRIVER_EN, HIGH);

    // take the chip select low to select the device:
    digitalWrite(PRES_DRIVER_EN, LOW);
    
    SPI.transfer(0x82);
    SPI.transfer(0x05);
    SPI.transfer(0x00);
    
    // take the chip select high to de-select:
    digitalWrite(PRES_DRIVER_EN, HIGH);



    delay(100);

    // take the chip select low to select the device:
    digitalWrite(PRES_DRIVER_EN, LOW);
    
    SPI.transfer(0x82);
    SPI.transfer(0x06);
    SPI.transfer(0x00);
    
    // take the chip select high to de-select:
    digitalWrite(PRES_DRIVER_EN, HIGH);



    delay(100);

    // take the chip select low to select the device:
    digitalWrite(PRES_DRIVER_EN, LOW);
    
    SPI.transfer(0x82);
    SPI.transfer(0x07);
    SPI.transfer(0x00);
    
    // take the chip select high to de-select:
    digitalWrite(PRES_DRIVER_EN, HIGH);



    delay(100);

    // take the chip select low to select the device:
    digitalWrite(PRES_DRIVER_EN, LOW);
    
    SPI.transfer(0x82);
    SPI.transfer(0x08);
    SPI.transfer(0x00);
    
    // take the chip select high to de-select:
    digitalWrite(PRES_DRIVER_EN, HIGH);
}

void loop()
{
}
