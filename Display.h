//
// Created by B. Korzhak on 28.02.2019.
//


#ifndef THERMISTOR_DISPLAY_H
#define THERMISTOR_DISPLAY_H

#include "Arduino.h"
#include "Configuration.h"


class Display {
    public:
        Display();
        void draw_main_page(float temp, int set_temp);

    private:
        String current_t_text = "t: ";
        String set_t_text = " | set t: ";
};


#endif //THERMISTOR_DISPLAY_H
