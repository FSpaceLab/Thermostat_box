#include "Configuration.h"
#include "Thermostat.h"
#include "Display.h"
#include "MyKeypad.h"
#include "SD_EEPROM.h"

// Object for get data from thermistor
Thermistor thermistor(THERMISTOR_PIN, B, SERIAL_R, THERMISTOR_R, NOMINAL_T, COEF_THERMISTOR);

// Object for manage thermostat. Setting temperature in box
Thermostat thermostat(HEATER_PIN, COOLER_PIN, COOLER_FAN_COLD_PIN, COOLER_FAN_HEAT_PIN,
                      COOLING_INTERVAL, HEATING_INTERVAL);

// Object for manage display
Display display;

// Object for get and write box parameters to EEPROM
SD_EEPROM saved_data;


/********** BUFFERS **************/
// States
bool THERMOSTAT_STATE = OFF;
bool TEMP_THERMOSTAT_STATE = OFF;   // TEMPORARY state

bool CO2_STATE = OFF;
bool TEMP_CO2_STATE = OFF;

bool LIGHT_STATE = OFF;
bool TEMP_LIGHT_STATE = OFF;

// Initialize box parameters
byte SET_T = 0;
byte TEMP_SET_T = 0;

int SET_CO2 = 0;
int TEMP_SET_CO2 = 0;

byte SET_LIGHT_R = 0;
byte TEMP_SET_LIGHT_R = 0;

byte SET_LIGHT_G = 0;
byte TEMP_SET_LIGHT_G = 0;

byte SET_LIGHT_B = 0;
byte TEMP_SET_LIGHT_B = 0;


// Pages
bool set_t_menu = false;
bool set_light_menu = false;
bool set_co2_menu = false;


/********************************/

void setup()
{
    Serial.begin(9600);
    thermostat.set_thermistor(thermistor);

    /******** RESTORE DATA FROM EEPROM ********/
    // Temperature restore
    THERMOSTAT_STATE = saved_data.read(TEMP_STATE_ADDR);
    TEMP_THERMOSTAT_STATE = THERMOSTAT_STATE;

    SET_T = saved_data.read(TEMP_SET_ADDR);
    TEMP_SET_T = SET_T;

    // CO2 restore
    CO2_STATE = saved_data.read(CO2_STATE_ADDR);
    TEMP_CO2_STATE = CO2_STATE;

    SET_CO2 = saved_data.read(CO2_SET_ADDR);
    TEMP_SET_CO2 = SET_CO2;

    // Light restore
    LIGHT_STATE = saved_data.read(LIGHT_STATE_ADDR);
    TEMP_LIGHT_STATE = LIGHT_STATE;

    SET_LIGHT_R = saved_data.read(LIGHT_R_ADDR);
    TEMP_SET_LIGHT_R = SET_LIGHT_R;

    SET_LIGHT_G = saved_data.read(LIGHT_G_ADDR);
    TEMP_SET_LIGHT_G = SET_LIGHT_G;

    SET_LIGHT_B = saved_data.read(LIGHT_B_ADDR);
    TEMP_SET_LIGHT_B = SET_LIGHT_B;
    /******************************************/
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
        display.draw_main_page(thermistor.get_t(), THERMOSTAT_STATE, SET_T, thermostat.current_state);
    }

    // TEMPERATURE MENU
    if (key == 'E') {
        if (!set_t_menu)
            set_t_menu = true;

        // SAVING DATA
        else {
            THERMOSTAT_STATE = TEMP_THERMOSTAT_STATE;
            saved_data.write(TEMP_STATE_ADDR, THERMOSTAT_STATE);

            SET_T = TEMP_SET_T;
            saved_data.write(TEMP_SET_ADDR, SET_T);

            display.cur_pos_set_t = 0;
            set_t_menu = false;
        }
    }

    // LIGHT MENU
    else if (key == 'f') {
        if (!set_light_menu)
            set_light_menu = true;

        // SAVING DATA
        else {
            LIGHT_STATE = TEMP_LIGHT_STATE;
            saved_data.write(LIGHT_STATE_ADDR, LIGHT_STATE);

            SET_LIGHT_R = TEMP_SET_LIGHT_R;
            saved_data.write(LIGHT_R_ADDR, SET_LIGHT_R);

            SET_LIGHT_G = TEMP_SET_LIGHT_G;
            saved_data.write(LIGHT_G_ADDR, SET_LIGHT_G);

            SET_LIGHT_B = TEMP_SET_LIGHT_B;
            saved_data.write(LIGHT_B_ADDR, SET_LIGHT_B);

            display.cur_pos_set_t = 0;
            set_light_menu = false;
        }
    }

    // CO2 MENU
    else if (key == 'F') {
        if (!set_co2_menu)
            set_co2_menu = true;
        else {
            CO2_STATE = TEMP_CO2_STATE;
            saved_data.write(CO2_STATE_ADDR, CO2_STATE);

            SET_CO2 = TEMP_SET_CO2;
            saved_data.write(CO2_SET_ADDR, SET_CO2);

            display.cur_pos_set_t = 0;
            set_co2_menu = false;
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
        display.update_current_position(MOVE_CURSOR_UP);

    else if (key == 'd')
        display.update_current_position(MOVE_CURSOR_DOWN);

    Serial.print("key=");
    Serial.println(key);

    Serial.print("temp=");
    Serial.print(thermistor.get_t());
    Serial.print("; ");

    Serial.print("co2=");
    Serial.print(0);
    Serial.print("; ");

    Serial.print("on=");
    Serial.print(THERMOSTAT_STATE);
    Serial.print("; ");

    Serial.print("current_state=");
    Serial.println(thermostat.current_state);
}
