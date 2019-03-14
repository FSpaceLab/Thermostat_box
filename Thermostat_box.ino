#include "Configuration.h"
#include "Thermostat.h"
#include "Display.h"
#include "MyKeypad.h"

// Object for get data from thermistor
Thermistor thermistor(THERMISTOR_PIN, B, SERIAL_R, THERMISTOR_R, NOMINAL_T, COEF_THERMISTOR);

// Object for manage thermostat. Setting temperature in box
Thermostat thermostat(HEATER_PIN, COOLER_PIN, COOLER_FAN_COLD_PIN, COOLER_FAN_HEAT_PIN,
                      COOLING_INTERVAL, HEATING_INTERVAL);

// Object for manage display
Display display;


/********** BUFERS **************/

// States
bool THERMOSTAT_STATE = ON;

byte SET_T = 60;


// Pages
bool set_t_menu = false;


/********************************/

void setup()
{
    Serial.begin(9600);
    thermostat.set_thermistor(thermistor);
}

void loop()
{
    char key = get_key();

    if (set_t_menu) {
        display.draw_set_t(0, THERMOSTAT_STATE, 15);

        if (key == "e")
            set_t_menu = false;

    }
    else {
        display.draw_main_page(13.3, SET_T);
    }


    if (key == 'E' )
        set_t_menu = true;


//    display.draw_main_page(thermistor.get_t(), SET_T);
}
