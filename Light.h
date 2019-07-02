//
// Created by navch on 11.04.2019.
//

#ifndef THERMOSTAT_BOX_LIGHT_H
#define THERMOSTAT_BOX_LIGHT_H

#include "Arduino.h"

class Light {
    public:
        Light(byte pin_UV, byte pin_R, byte pin_G, byte pin_B);
        void on(bool state, byte level_R=0, byte level_G=0, byte level_B=0);
        void off();
        byte current_state = 0;

    private:
        byte _pin_R, _pin_G, _pin_B;

};


#endif //THERMOSTAT_BOX_LIGHT_H
