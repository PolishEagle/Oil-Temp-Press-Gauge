#include "OilTemperatureSensor.h"
#include <math.h>

// Bias resistor recommended for MS where most people use the 
int biasResistor = 2490;
int inputVoltage = 5;

float A = 1.443217771e-3;
float B = 2.358868166e-4;
float C = 1.031746197e-7;

int OilTemperatureSensor::GetTemperature()
{
    int resistance = GetSensorResistance();

    // Steinhart-Hart equation
    float temperatureKelvin = 1 / (A + B*log(resistance) + C*pow(log(resistance), 3));
  
    return (int)(temperatureKelvin - 273.15);
}

int OilTemperatureSensor::GetSensorResistance()
{
    // Get the voltage from the port
    int sensorValue = analogRead(TEMPERATURE_SENSOR_PORT);
    float sensorVoltage = sensorValue * (5.0 / 1023.0);

    // Calculate the resistance from the reworked voltage divider eq.
    return sensorVoltage * biasResistor / (inputVoltage - sensorVoltage);
}


