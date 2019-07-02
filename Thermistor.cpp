//
// Created by navch on 01.03.2019.
//

#include "Arduino.h"
#include "Thermistor.h"


float _dataset[3] = {0, 0, 0};
byte _index = 0;


Thermistor::Thermistor(int pin, int b, int serial_r, unsigned long thermistor_r,
                             int nominal_t, float coef_thermistor)
{
    // If thermistor connected;
    _pin = pin;

    pinMode(_pin, INPUT);

    // constants
    _b = b;
    _serial_r = serial_r;
    _thermistor_r = thermistor_r;
    _nominal_t=nominal_t;
    _coef_thermistor = coef_thermistor;
}


float Thermistor::_mediana(float data) {
    if (_index <= 2)
        _index++;
    else
        _index = 0;

    _dataset[_index] = data;

    if ((_dataset[0] > _dataset[1] && _dataset[0] < _dataset[2]) ||
        (_dataset[0] < _dataset[1] && _dataset[0] > _dataset[2]))
        return _dataset[0];
    else if ((_dataset[1] > _dataset[0] && _dataset[1] < _dataset[2]) ||
             (_dataset[1] < _dataset[0] && _dataset[1] > _dataset[2]))
        return _dataset[1];
    else
        return _dataset[2];
}


float Thermistor::get_t() {
    int t = analogRead(_pin);

    // R (Om) from thermistor_
    float tr = _serial_r / (1023.0 / t - 1);

    // Themperature calculation (in *C)
    float data = (1.0 / (log(tr / _thermistor_r) / _b + 1.0 / (_nominal_t + 273.15))) - _coef_thermistor;
    return _mediana(data);
}


