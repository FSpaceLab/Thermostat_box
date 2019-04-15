//
// Created by navch on 11.04.2019.
//

#ifndef THERMOSTAT_BOX_LIGHT_H
#define THERMOSTAT_BOX_LIGHT_H

#include "Arduino.h"

class Light {
    public:
        Light(byte pin_R, byte pin_G, byte pin_B);
        void on(byte level_R, byte level_G, byte level_B);
        void off();
        bool current_state = false;

    private:
        byte _pin_R, _pin_G, _pin_B;

};


#endif //THERMOSTAT_BOX_LIGHT_H
