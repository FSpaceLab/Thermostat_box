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

        // methods
        void draw_main_page(float temp, bool state, int set_temp, byte process);
        void draw_set_t(bool state, byte temperature);
        void update_current_position(bool update);
        // attributes
        byte cur_pos_set_t = 0;
        byte max_len = 2;

    private:

        // texts for display
        String current_t_text = "cur. t: ";
        String degrees_by_C = " C";

        String set_t_text = "set t: ";

        const char * cooling_state = "cooling";
        const char * heating_state = "heating";

        const char *off_state = "Off";
        const char *on_state = "On";

        const char *l_arrow = "<";
        const char *r_arrow = ">";

        byte full_width = 128;
        byte full_heigth = 64;

        byte arrow_l_x = 3;
        byte arrow_r_x = 120;
};


#endif //THERMISTOR_DISPLAY_H
