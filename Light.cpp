  //
// Created by navch on 11.04.2019.
//

#include "Light.h"

Light::Light(byte pin_R, byte pin_G, byte pin_B) {
    _pin_R = pin_R;
    _pin_G = pin_G;
    _pin_B = pin_B;

    pinMode(_pin_R, OUTPUT);
    pinMode(_pin_G, OUTPUT);
    pinMode(_pin_B, OUTPUT);
}

void Light::on(byte level_R, byte level_G, byte level_B) {
    current_state = true;

    digitalWrite(_pin_R, level_R);
    digitalWrite(_pin_G, level_G);
    digitalWrite(_pin_B, level_B);
}

void Light::off() {
    current_state = false;

    digitalWrite(_pin_R, LOW);
    digitalWrite(_pin_G, LOW);
    digitalWrite(_pin_B, LOW);
}
