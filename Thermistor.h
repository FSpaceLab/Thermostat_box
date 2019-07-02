//
// Created by B. Korzhak on 01.03.2019.
//

// B 3950 // B-коэффициент
// SERIAL_R 10000 // сопротивление последовательного резистора, 102 кОм
// THERMISTOR_R 49900 // номинальное сопротивления термистора, 100 кОм
// NOMINAL_T 18 // номинальная температура (при которой TR = 50 кОм)
// COEF_THERMISTOR 269

#ifndef TS_THERMISTOR_H
#define TS_THERMISTOR_H

#include "Arduino.h"

class Thermistor {
    public:
        Thermistor(int pin, int b=3950, int serial_r=10000, unsigned long thermistor_r=49900,
                             int nominal_t=18, float coef_thermistor = 269);
        float get_t();

    private:
        float _mediana(float data);

        byte _pin;
        int _b, _serial_r, _nominal_t;
        unsigned long _thermistor_r;
        float _coef_thermistor;
};


#endif //TS_THERMISTOR_H
