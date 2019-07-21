#ifndef OILTEMPERATURE_H
#define OILTEMPERATURE_H

#include <Arduino.h>

#define TEMPERATURE_SENSOR_PORT A5

class OilTemperatureSensor
{
    public:
        int GetTemperature();
    
    private:
        int GetSensorResistance();
};

#endif

