#include "OilPressureSensor.h"

int OilPressureSensor::GetPressure()
{
    float sensorVoltage = GetSensorVoltage();    
    int pressure = (int)((37.5 * sensorVoltage) - 18.75);

    if (pressure < 0)
        return 0;
    else if (pressure > 150)
        return 150;

    return pressure;
}

float OilPressureSensor::GetSensorVoltage()
{
    int pressureAdc = analogRead(PRESSURE_SENSOR_PORT);
    return pressureAdc * (5.0 / 1023.0);
}


