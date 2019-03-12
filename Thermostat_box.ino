#include "Configuration.h"
#include "Thermostat.h"
#include "Display.h"

// Object for get data from thermistor
Thermistor thermistor(THERMISTOR_PIN, B, SERIAL_R, THERMISTOR_R, NOMINAL_T, COEF_THERMISTOR);

// Object for manage thermostat. Setting temperature in box
Thermostat thermostat(HEATER_PIN, COOLER_PIN, COOLER_FAN_COLD_PIN, COOLER_FAN_HEAT_PIN,
                      COOLING_INTERVAL, HEATING_INTERVAL);

Display disp;

byte SET_T = 60;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    thermostat.set_t(SET_T, thermistor);
    disp.draw_main_page(thermistor.get_t(), SET_T);
}
