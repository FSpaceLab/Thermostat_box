//
// Created by B. Korzhak on 01.03.2019.
//

#ifndef TS_CONFIGURATION_H
#define TS_CONFIGURATION_H


/*************** PIN'S CONFIGURATION ****************/
// THERMISTORS
#define THERMISTOR_PIN A0

// THERMOSTAT
#define COOLER_FAN_COLD_PIN 4
#define COOLER_FAN_HEAT_PIN 3
#define COOLER_PIN 6
#define HEATER_PIN 7

// DISPLAY
#define SCK_DISPLAY 13
#define MOSI_DISPLAY 11
#define CS_DISPLAY 10

// KEYPAD
#define KEYPAD_ROW {30, 32, 34, 36, 38}
#define KEYPAD_COLS {46, 44, 42, 40}

/***************************************************/



/************ THERMISTORS CONFIGURATION ************/
// COEFFICIENTS
#define B 3950 // B-coefficient
#define SERIAL_R 10000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 49900 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 18 // номинальная температура (при которой TR = 50 кОм)
#define COEF_THERMISTOR 269
/**************************************************/


/************ THERMOSTAT CONFIGURATION ************/
#define COOLING_INTERVAL 5000
#define HEATING_INTERVAL 5000

#define MAX_TEMP 60
#define MIN_TEMP 5
/**************************************************/


/************** DISPLAY CONFIGURATION *************/
#define MOVE_CURSOR_UP 0
#define MOVE_CURSOR_DOWN 1
/**************************************************/


/************** KEYPAD CONFIGURATION **************/
#define KEYPAD_MATRIX {{'f', 'F', '#', '*'},{'1', '2', '3', 'u'},{'4', '5', '6', 'd'},{'7', '8', '9', 'e'},{'<', '0', '>', 'E'}}
/**************************************************/


/************** EEPROM CONFIGURATION **************/
#define TEMP_STATE_ADDR 0
#define TEMP_SET_ADDR 2
#define CO2_STATE_ADDR 3
#define CO2_SET_ADDR 5
#define LIGHT_STATE_ADDR 6
#define LIGHT_R_ADDR 8
#define LIGHT_G_ADDR 10
#define LIGHT_B_ADDR 12
/**************************************************/


#endif //TS_CONFIGURATION_H
