//
// Created by B. Korzhak on 01.03.2019.
//

#ifndef TS_CONFIGURATION_H
#define TS_CONFIGURATION_H


/*************** PIN'S CONFIGURATION ****************/
// THERMISTORS
#define THERMISTOR_HOTBED_PIN A0
#define THERMISTOR_PIN A1
// #define DHTPIN A1

// THERMOSTAT
#define COOLER_FAN_INSIDE 6
#define COOLER_FAN_COLD_PIN 5
#define COOLER_FAN_HEAT_PIN 5
#define COOLER_PIN A10
#define HEATER_PIN A9

// DISPLAY
#define SCK_DISPLAY 13
#define MOSI_DISPLAY 11
#define CS_DISPLAY 10

// KEYPAD
#define KEYPAD_ROW {30, 32, 34, 36, 38}
#define KEYPAD_COLS {46, 44, 42, 40}

// LIGHT
#define PIN_UV 7
#define PIN_R 2
#define PIN_G 3
#define PIN_B 4

/***************************************************/

/************ THERMISTORS CONFIGURATION ************/
// COEFFICIENTS
#define B 3950 // B-coefficient
#define SERIAL_R 10000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 10000 // номинальное сопротивления термистора, 100 кОм
#define THERMISTOR_HOTBED_R 100000 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 18 // номинальная температура (при которой TR = 50 кОм)
#define COEF_THERMISTOR 267

// DHT
#define DHTTYPE 22
#define ON_DHT true;
/**************************************************/


/************ THERMOSTAT CONFIGURATION ************/
#define COOLING_INTERVAL 5000
#define HEATING_INTERVAL 2000

#define MAX_TEMP 60
#define MIN_TEMP 5

#define MAX_TEMP_HOTBED 100

#define TOLERANCE_TEMPERATURE 1
#define TOLERANCE_HEATING 0.05
#define TOLERANCE_COOLING 0.03

#define TEMPERATURE_CORRECTION 1.35   // Degree by Celsius
/**************************************************/


/*************** LIGHT CONFIGURATION **************/
#define RGB_UV_STATE 3
#define RGB_STATE 2
#define UV_STATE 1
#define OFF 0
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
#define LIGHT_UV_ADDR 14
/**************************************************/


#endif //TS_CONFIGURATION_H
