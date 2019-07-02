  //
// Created by navch on 11.04.2019.
//

#include "Light.h"

Light::Light(byte pin_UV, byte pin_R, byte pin_G, byte pin_B) {
    _pin_UV = pin_UV;
    _pin_R = pin_R;
    _pin_G = pin_G;
    _pin_B = pin_B;

    pinMode(_pin_UV, OUTPUT);
    pinMode(_pin_R, OUTPUT);
    pinMode(_pin_G, OUTPUT);
    pinMode(_pin_B, OUTPUT);
}

void Light::on(bool state, byte level_R, byte level_G, byte level_B) {
    if (state) {
        current_state = 1;
        analogWrite(_pin_UV, HIGH);
    } else {
        current_state = 2;
        analogWrite(_pin_R, level_R);
        analogWrite(_pin_G, level_G);
        analogWrite(_pin_B, level_B);
    }



}

void Light::off() {
    current_state = 0;
    analogWrite(_pin_UV, LOW);
    analogWrite(_pin_R, LOW);
    analogWrite(_pin_G, LOW);
    analogWrite(_pin_B, LOW);
}
