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
bool THERMOSTAT_STATE = OFF;
bool TEMP_THERMOSTAT_STATE = THERMOSTAT_STATE;

byte SET_T = 60;
byte TEMP_SET_T = 20;


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

    if (THERMOSTAT_STATE)
        thermostat.set_t(SET_T);
    else
        thermostat.off_box();


    char key = get_key();

    if (set_t_menu) {
        display.draw_set_t(TEMP_THERMOSTAT_STATE, TEMP_SET_T);
    }
    else {
        display.draw_main_page(13.3, THERMOSTAT_STATE, SET_T, thermostat.current_state);
    }


    if (key == 'E') {
        if (!set_t_menu)
            set_t_menu = true;
        else {
            THERMOSTAT_STATE = TEMP_THERMOSTAT_STATE;
            SET_T = TEMP_SET_T;
            display.cur_pos_set_t = 0;
            set_t_menu = false;
        }
    }

    else if (key == 'e') {
        TEMP_THERMOSTAT_STATE = THERMOSTAT_STATE;
        TEMP_SET_T = SET_T;
        display.cur_pos_set_t = 0;
        set_t_menu = false;

    }

    else if (key == '<' || key == '>') {
        if (display.cur_pos_set_t == 0)
            TEMP_THERMOSTAT_STATE = !TEMP_THERMOSTAT_STATE;

        else if (display.cur_pos_set_t == 1) {
            if (key == '<') {
                TEMP_SET_T--;
            } else
                TEMP_SET_T++;
        }
    }

    else if (key == 'u')
        display.update_current_position(0);

    else if (key == 'd')
        display.update_current_position(1);

}
