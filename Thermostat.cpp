//
// Created by navch on 01.03.2019.
//

#include "Arduino.h"
#include "Thermostat.h"


Thermostat::Thermostat(byte heater_pin, byte cooler_pin, byte cooler_fan_cold_pin, byte cooler_fan_heat_pin, long cooling_interval) {
    pinMode(cooler_fan_cold_pin, OUTPUT);
    pinMode(cooler_fan_heat_pin, OUTPUT);
    pinMode(cooler_pin, OUTPUT);
    pinMode(heater_pin, OUTPUT);

    _heater_pin = heater_pin;
    _cooler_pin = cooler_pin;
    _cooler_fan_cold_pin = cooler_fan_cold_pin;
    _cooler_fan_heat_pin = cooler_fan_heat_pin;

    byte _common_state = 0;

    _cooling_interval = cooling_interval;
    _previous_millis = 0;
}


void Thermostat::_cooling(bool state) {
    unsigned long current_millis = millis();

    if (current_millis - _previous_millis >= _cooling_interval) {

        _previous_millis = current_millis;

        if (state && _common_state != COOLING_STATE ) {
            _common_state = COOLING_STATE;

            digitalWrite(_cooler_fan_cold_pin, HIGH);
            digitalWrite(_cooler_fan_heat_pin, HIGH);
            digitalWrite(_cooler_pin, HIGH);
        }
        else if (!state && _common_state == COOLING_STATE){
            _common_state = OFF_STATE;

            digitalWrite(_cooler_fan_cold_pin, LOW);
            digitalWrite(_cooler_fan_heat_pin, LOW);
            digitalWrite(_cooler_pin, LOW);
        }
    }
}

void Thermostat::_heating(bool state) {
    //TODO
}


void Thermostat::set_t(int temperature, Thermistor thermistor) {
    float current_t = thermistor.get_t();

    if (current_t > temperature) {
        Serial.println("COOLING BLOCK ON");
        _cooling(ON);
    }

//    else if (current_t < temperature) {
//        // TODO: heating
//    }

    else {
        Serial.println("COOLING BLOCK OFF");
        _cooling(OFF);
    }
}
