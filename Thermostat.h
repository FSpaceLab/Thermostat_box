//
// Created by B. Korzhak on 01.03.2019.
//

#ifndef TS_THERMOSTAT_H
#define TS_THERMOSTAT_H

#include "Arduino.h"
#include "Thermistor.h"
#include "DHT.h"
#include "Configuration.h"


#define ON 1
#define OFF 0
#define OFF_STATE 0
#define HEATING_STATE 1
#define COOLING_STATE 2


class Thermostat {
    public:
        Thermostat(byte heater_pin, byte cooler_pin, byte cooler_fan_cold_pin,
                   byte cooler_fan_heat_pin, byte inside_fan_cooler,
                   long cooling_interval=60000, long heating_interval=15000);

        void set_t(int temperature);

        void set_thermistor(Thermistor thermistor);
        void set_thermistor(DHT dht);

        void set_hotbed_thermistor(Thermistor thermistor);
        void off_box();

        float current_t = 0;

        byte current_state, last_state;

    private:
        byte _heater_pin, _cooler_pin, _cooler_fan_cold_pin,
             _cooler_fan_heat_pin, _inside_fan_cooler;

        // STATE may be 0 (Off), 1 (heating), 2 (cooling)
        byte _current_state;

        void _cooling(bool state = OFF);
        void _heating(bool state = OFF);

        long _cooling_interval, _heating_interval;
        unsigned long _previous_millis;
        Thermistor *_thermistor;
        Thermistor *_hotbed_thermistor;
        DHT *_dht;
        bool _setted_dht = 0;

};


#endif //TS_THERMOSTAT_H
