#include "Configuration.h"
#include "Thermostat.h"



Thermistor thermistor(THERMISTOR_PIN, B, SERIAL_R, THERMISTOR_R, NOMINAL_T, COEF_THERMISTOR);

Thermostat thermostat(HEATER_PIN, COOLER_PIN, COOLER_FAN_COLD_PIN, COOLER_FAN_HEAT_PIN, COOLING_INTERVAL);

void setup()
{
    Serial.begin(9600);
//    thermostat.set_thermistor(thermistor);
}

void loop()
{
    thermostat.set_t(12, thermistor);
    Serial.println("");
    delay(1000);
}
