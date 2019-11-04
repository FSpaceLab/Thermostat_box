
#include "Configuration.h"
#include "Thermostat.h"
#include "Display.h"
#include "MyKeypad.h"
#include "SD_EEPROM.h"
#include "Light.h"
#include "DHT.h"


// DHT dht(DHTPIN, DHTTYPE);

// Object for get data from thermistor
Thermistor thermistor(THERMISTOR_PIN, B, SERIAL_R, THERMISTOR_R, NOMINAL_T, COEF_THERMISTOR);
Thermistor thermistor_hotbed(THERMISTOR_HOTBED_PIN, B, SERIAL_R, THERMISTOR_HOTBED_R, NOMINAL_T, COEF_THERMISTOR);
//Thermistor thermistor(DHT_PIN, DHTTYPE);

// Object for manage thermostat. Setting temperature in box
Thermostat thermostat(HEATER_PIN, COOLER_PIN, COOLER_FAN_COLD_PIN,
                      COOLER_FAN_HEAT_PIN, COOLER_FAN_INSIDE,
                      COOLING_INTERVAL, HEATING_INTERVAL);

// Object for manage display
Display display;

// Object for get and write box parameters to EEPROM
SD_EEPROM saved_data;

// Object for manage light
Light light(PIN_UV, PIN_R, PIN_G, PIN_B);


/********** BUFFERS **************/
// States
bool THERMOSTAT_STATE = OFF;
bool TEMP_THERMOSTAT_STATE = OFF;   // TEMPORARY state

bool CO2_STATE = OFF;
bool TEMP_CO2_STATE = OFF;

byte LIGHT_STATE = OFF;
byte TEMP_LIGHT_STATE = OFF;

// Initialize box parameters
byte SET_T = 0;
byte TEMP_SET_T = 0;

int SET_CO2 = 0;
int TEMP_SET_CO2 = 0;

byte SET_LIGHT_UV = 0;
byte TEMP_SET_LIGHT_UV = 0;

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

int keypad_value = 0;

unsigned long previous_millis = 0;
int serial_interval = 5000;


/********************************/

void setup()
{
    Serial.begin(9600);
    thermostat.set_thermistor(thermistor);
    thermostat.set_hotbed_thermistor(thermistor_hotbed);

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

    SET_LIGHT_UV = saved_data.read(LIGHT_UV_ADDR);
    TEMP_SET_LIGHT_UV = SET_LIGHT_UV;

    SET_LIGHT_R = saved_data.read(LIGHT_R_ADDR);
    TEMP_SET_LIGHT_R = SET_LIGHT_R;

    SET_LIGHT_G = saved_data.read(LIGHT_G_ADDR);
    TEMP_SET_LIGHT_G = SET_LIGHT_G;

    SET_LIGHT_B = saved_data.read(LIGHT_B_ADDR);
    TEMP_SET_LIGHT_B = SET_LIGHT_B;

    /******************************************/
}

void loop() {

    while (Serial.available() > 0) {

        // look for the next valid integer in the incoming serial stream:
        THERMOSTAT_STATE = Serial.parseInt();
        TEMP_THERMOSTAT_STATE = THERMOSTAT_STATE;
        saved_data.write(TEMP_STATE_ADDR, THERMOSTAT_STATE);

        SET_T = Serial.parseInt();
        TEMP_SET_T = SET_T;
        saved_data.write(TEMP_SET_ADDR, SET_T);

        CO2_STATE = Serial.parseInt();
        TEMP_CO2_STATE = CO2_STATE;
        saved_data.write(CO2_STATE_ADDR, CO2_STATE);

        SET_CO2 = Serial.parseInt();
        TEMP_SET_CO2 = SET_CO2;
        saved_data.write(CO2_SET_ADDR, SET_CO2);

        LIGHT_STATE = Serial.parseInt();
        TEMP_LIGHT_STATE = LIGHT_STATE;
        saved_data.write(LIGHT_STATE_ADDR, LIGHT_STATE);

        SET_LIGHT_UV = Serial.parseInt();
        TEMP_SET_LIGHT_UV = SET_LIGHT_UV;
        saved_data.write(LIGHT_UV_ADDR, SET_LIGHT_UV);

        SET_LIGHT_R = Serial.parseInt();
        TEMP_SET_LIGHT_R = SET_LIGHT_R;
        saved_data.write(LIGHT_R_ADDR, SET_LIGHT_R);

        SET_LIGHT_G = Serial.parseInt();
        TEMP_SET_LIGHT_G = SET_LIGHT_G;
        saved_data.write(LIGHT_G_ADDR, SET_LIGHT_G);

        SET_LIGHT_B = Serial.parseInt();
        TEMP_SET_LIGHT_B = SET_LIGHT_B;
        saved_data.write(LIGHT_B_ADDR, SET_LIGHT_B);

        int pass = Serial.parseInt();
    }


    // Modules manage
    if (THERMOSTAT_STATE)
        thermostat.set_t(SET_T);

    else
        thermostat.off_box();

    if (LIGHT_STATE)
        light.on(LIGHT_STATE, SET_LIGHT_UV, SET_LIGHT_R, SET_LIGHT_G, SET_LIGHT_B);
    else
        light.off();


    /******** Working with keypad and display ********/
    if (set_t_menu)
        display.draw_set_t(TEMP_THERMOSTAT_STATE, TEMP_SET_T);

    else if (set_light_menu)
        display.draw_set_light(TEMP_LIGHT_STATE, TEMP_SET_LIGHT_UV, TEMP_SET_LIGHT_R, TEMP_SET_LIGHT_G, TEMP_SET_LIGHT_B);

    else
       display.draw_main_page(thermistor.get_t() + TEMPERATURE_CORRECTION, THERMOSTAT_STATE, SET_T, thermostat.current_state);


    char key = get_key();

    // MAX LEN MENU-array
    byte max_len = 0;
    if (set_t_menu)
        max_len = display.max_len_t;
    else if (set_light_menu)
        max_len = display.max_len_light;
    else if (set_co2_menu)
        max_len = display.max_len_co2;

    // TEMPERATURE MENU
    if (key == 'E' && !set_light_menu && !set_co2_menu) {
        if (!set_t_menu)
            set_t_menu = true;

        // SAVING DATA
        else {
            keypad_value = 0;

            THERMOSTAT_STATE = TEMP_THERMOSTAT_STATE;
            saved_data.write(TEMP_STATE_ADDR, THERMOSTAT_STATE);

            SET_T = TEMP_SET_T;
            saved_data.write(TEMP_SET_ADDR, SET_T);

            display.cur_pos_set_t = 0;
            set_t_menu = false;
        }
    }

    // LIGHT MENU
    else if (key == 'f' && !set_t_menu && !set_co2_menu) {
        if (!set_light_menu)
            set_light_menu = true;

        // SAVING DATA
        else {
            keypad_value = 0;

            LIGHT_STATE = TEMP_LIGHT_STATE;
            saved_data.write(LIGHT_STATE_ADDR, LIGHT_STATE);

            SET_LIGHT_UV = TEMP_SET_LIGHT_UV;
            saved_data.write(LIGHT_UV_ADDR, SET_LIGHT_UV);

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
            keypad_value = 0;

            CO2_STATE = TEMP_CO2_STATE;
            saved_data.write(CO2_STATE_ADDR, CO2_STATE);

            SET_CO2 = TEMP_SET_CO2;
            saved_data.write(CO2_SET_ADDR, SET_CO2);

            display.cur_pos_set_t = 0;
            set_co2_menu = false;
        }
    }

    // Exit without save data
    else if (key == 'e') {
        keypad_value = 0;

        TEMP_THERMOSTAT_STATE = THERMOSTAT_STATE;
        TEMP_SET_T = SET_T;

        TEMP_CO2_STATE = CO2_STATE;
        TEMP_SET_CO2 = SET_CO2;

        TEMP_LIGHT_STATE = LIGHT_STATE;
        TEMP_SET_LIGHT_UV = SET_LIGHT_UV;
        TEMP_SET_LIGHT_R = SET_LIGHT_R;
        TEMP_SET_LIGHT_G = SET_LIGHT_G;
        TEMP_SET_LIGHT_B = SET_LIGHT_B;

        display.cur_pos_set_t = 0;
        set_t_menu = false;
        set_co2_menu = false;
        set_light_menu = false;

    }

    else if (key == '<' || key == '>') {
        if (display.cur_pos_set_t == 0) {
            if (set_t_menu)
                TEMP_THERMOSTAT_STATE = !TEMP_THERMOSTAT_STATE;

            // choice of type of lighting
            else if (set_light_menu) {
                if (TEMP_LIGHT_STATE == RGB_UV_STATE && key == '>')
                    TEMP_LIGHT_STATE = OFF;

                else if (TEMP_LIGHT_STATE == OFF && key == '<')
                    TEMP_LIGHT_STATE = RGB_STATE;

                else if (key == '>')
                    TEMP_LIGHT_STATE++;
                else
                    TEMP_LIGHT_STATE--;
            }
        }

        else if (display.cur_pos_set_t >= 1 && display.cur_pos_set_t <= 4) {
            if (key == '<') {
                if (set_t_menu)
                    TEMP_SET_T--;

                else if (set_light_menu && display.cur_pos_set_t == 1)
                    TEMP_SET_LIGHT_UV--;
                else if (set_light_menu && display.cur_pos_set_t == 2)
                    TEMP_SET_LIGHT_R--;
                else if (set_light_menu && display.cur_pos_set_t == 3)
                    TEMP_SET_LIGHT_G--;
                else if (set_light_menu && display.cur_pos_set_t == 4)
                    TEMP_SET_LIGHT_B--;

            } else {
                if (set_t_menu)
                    TEMP_SET_T++;

                else if (set_light_menu && display.cur_pos_set_t == 1)
                    TEMP_SET_LIGHT_UV++;
                else if (set_light_menu && display.cur_pos_set_t == 2)
                    TEMP_SET_LIGHT_R++;
                else if (set_light_menu && display.cur_pos_set_t == 3)
                    TEMP_SET_LIGHT_G++;
                else if (set_light_menu && display.cur_pos_set_t == 4)
                    TEMP_SET_LIGHT_B++;
            }
        }
    }

    else if (key == 'u') {
        keypad_value = 0;
        display.update_current_position(MOVE_CURSOR_UP, max_len);
    }

    else if (key == 'd') {
        keypad_value = 0;
        display.update_current_position(MOVE_CURSOR_DOWN, max_len);
    }

    else if (key >= '0' && key <= '9') {
        if (display.cur_pos_set_t >= 1 && display.cur_pos_set_t <= 4) {

            if (display.cursor > 2) {
                display.cursor = 0;
                keypad_value = 0;
            }

            keypad_value = keypad_value * 10 + key - '0';

            if (keypad_value > (set_t_menu ? 60 : 255))
                keypad_value = 0 * 10 + key - '0';

            if (set_t_menu)
                TEMP_SET_T = keypad_value;


            else if (set_light_menu) {
                if (display.cur_pos_set_t == 1)
                    TEMP_SET_LIGHT_UV = keypad_value;
                else if (display.cur_pos_set_t == 2)
                    TEMP_SET_LIGHT_R = keypad_value;
                else if (display.cur_pos_set_t == 3)
                    TEMP_SET_LIGHT_G = keypad_value;
                else if (display.cur_pos_set_t == 4)
                    TEMP_SET_LIGHT_B = keypad_value;
            }

        }
    }



    /******** Send data to server ********/

    unsigned long current_millis = millis();

    // Мінімальний час роботи нагрівача = heating_interval
    if (current_millis - previous_millis >= serial_interval ) {

        previous_millis = current_millis;

        Serial.print(THERMOSTAT_STATE);
        Serial.print("; ");

        Serial.print(thermostat.current_state);
        Serial.print("; ");

        // Themperature
        Serial.print(thermistor.get_t() + TEMPERATURE_CORRECTION);
        Serial.print("; ");

        Serial.print(SET_T);
        Serial.print("; ");

        // CO2
        Serial.print(0);
        Serial.print("; ");

        Serial.print(0);
        Serial.print("; ");

        // Light
        Serial.print(LIGHT_STATE);
        Serial.print("; ");

        Serial.print(SET_LIGHT_UV);
        Serial.print("; ");

        Serial.print(SET_LIGHT_R);
        Serial.print("; ");

        Serial.print(SET_LIGHT_G);
        Serial.print("; ");

        Serial.print(SET_LIGHT_B);
        Serial.println("; ");
    }
}
