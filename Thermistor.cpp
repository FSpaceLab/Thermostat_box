//
// Created by navch on 01.03.2019.
//

#include "Arduino.h"
#include "Thermistor.h"


Thermistor::Thermistor(int pin, int b, int serial_r, unsigned long thermistor_r,
                             int nominal_t, float coef_thermistor)
{
    _pin = pin;

    pinMode(_pin, INPUT);

    // constants
    _b = b;
    _serial_r = serial_r;
    _thermistor_r = thermistor_r;
    _nominal_t=nominal_t;
    _coef_thermistor = coef_thermistor;
}

float Thermistor::get_t() {
    int t = analogRead(_pin);
    
    // R (Om) from thermistor_
    float tr = _serial_r / (1023.0 / t - 1);
    
    // Themperature calculation (in *C)       
    return (1.0 / (log(tr / _thermistor_r) / _b + 1.0 / (_nominal_t + 273.15))) - _coef_thermistor;
}
