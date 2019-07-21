#ifndef OILPRESSURE_H
#define OILPRESSURE_H

#include <Arduino.h>

#define PRESSURE_SENSOR_PORT A4

class OilPressureSensor
{
    public:
        int GetPressure();

    private:
        float GetSensorVoltage();
};

#endif

