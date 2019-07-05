//
// Created by navch on 01.03.2019.
//

#include "Arduino.h"
#include "Thermostat.h"


Thermostat::Thermostat(byte heater_pin, byte cooler_pin,
                       byte cooler_fan_cold_pin, byte cooler_fan_heat_pin,
                       byte inside_fan_cooler,
                       long cooling_interval, long heating_interval) {
    pinMode(cooler_fan_cold_pin, OUTPUT);
    pinMode(cooler_fan_heat_pin, OUTPUT);
    pinMode(inside_fan_cooler, OUTPUT);
    pinMode(cooler_pin, OUTPUT);
    pinMode(heater_pin, OUTPUT);

    _heater_pin = heater_pin;
    _cooler_pin = cooler_pin;
    _cooler_fan_cold_pin = cooler_fan_cold_pin;
    _cooler_fan_heat_pin = cooler_fan_heat_pin;
    _inside_fan_cooler = inside_fan_cooler;

    byte current_state = 0, last_state = 0;

    _cooling_interval = cooling_interval;
    _heating_interval = heating_interval;
    _previous_millis = 0;
}


void Thermostat::set_thermistor(Thermistor thermistor) {
    _thermistor = &thermistor;
}

void Thermostat::set_thermistor(DHT dht) {
    _dht = &dht;
    _setted_dht = 1;
}

void Thermostat::set_hotbed_thermistor(Thermistor thermistor) {
    _hotbed_thermistor = &thermistor;
}


void Thermostat::_cooling(bool state) {
    unsigned long current_millis = millis();

    // Мінімальний час роботи охолоджувача = cooling_interval
    if (current_millis - _previous_millis >= _cooling_interval) {
        _previous_millis = current_millis;

        // Перевірка та встановлення станів
        if (state && current_state != COOLING_STATE ) {
            current_state = COOLING_STATE;

            digitalWrite(_cooler_fan_cold_pin, HIGH);
            digitalWrite(_cooler_fan_heat_pin, HIGH);
            digitalWrite(_inside_fan_cooler, HIGH);
            digitalWrite(_cooler_pin, HIGH);
        }
        else if (!state && current_state == COOLING_STATE){
            current_state = OFF_STATE;

            digitalWrite(_cooler_fan_cold_pin, LOW);
            digitalWrite(_cooler_fan_heat_pin, LOW);
            digitalWrite(_inside_fan_cooler, LOW);
            digitalWrite(_cooler_pin, LOW);
        }
    }
}


void Thermostat::_heating(bool state) {
    unsigned long current_millis = millis();

    // Мінімальний час роботи нагрівача = heating_interval
    if (current_millis - _previous_millis >= _heating_interval ) {
        _previous_millis = current_millis;

        // Перевірка та встановлення станів
        if (state && current_state != HEATING_STATE) {
            current_state = HEATING_STATE;

            digitalWrite(_heater_pin, HIGH);
            digitalWrite(_inside_fan_cooler, HIGH);
        }
        else if (!state && current_state == HEATING_STATE){
            current_state = OFF_STATE;

            digitalWrite(_heater_pin, LOW);
            digitalWrite(_inside_fan_cooler, LOW);
        }

        float __t = _hotbed_thermistor->get_t();
//        Serial.println(__t);
        // Захист від перегріву hotbed`а
        if (__t > MAX_TEMP_HOTBED) {
            current_state = OFF_STATE;
            digitalWrite(_heater_pin, LOW);
        }
    }
}


void Thermostat::off_box() {
    _cooling(OFF);
    _heating(OFF);
}

void Thermostat::set_t(int temperature) {
    if (_setted_dht)
        current_t = _dht->readTemperature();
    else
        current_t = floor(_thermistor->get_t() + 0.5);

    float _t = _hotbed_thermistor->get_t();


    if (current_t < temperature ) {   // Ввімкнення нагріву
        if (current_state == COOLING_STATE)
            _cooling(OFF);

        // Розрахунок вимкнення нагріву через інерційність нагрівального елем.
        if ( ((_t - temperature) >= current_t) &&
             (current_t - current_t * TOLERANCE_HEATING) )
            _heating(OFF);
        else
            _heating(ON);
    }

    else if (current_t > temperature) {   // Ввімкнення охолодження
        if (current_state != HEATING_STATE)
            _heating(OFF);

        if (!((temperature - current_t) >= TOLERANCE_TEMPERATURE &&
               last_state == HEATING_STATE))
            _cooling(ON);
    }

    // Вимкнення нагріву/охолодження
    else {
        if (current_state != OFF_STATE) {
            _cooling(OFF);
            _heating(OFF);
        }
    }

    last_state = current_state;
}
