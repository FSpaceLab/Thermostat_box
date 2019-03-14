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
        void draw_main_page(float temp, int set_temp);
        void draw_set_t(byte moving, bool state, byte temperature);

        // attributes
        byte cur_pos_set_t = 0;

    private:

        // texts for display
        String current_t_text = "cur. t: ";
        String degrees_by_C = " C";

        String set_t_text = " | set t: ";

        String off_state = "Off";
        String on_state = "On";

        String temp_text = " ";
        char *char_temp_text;

        int len_text;
        char *char_text;

        byte up_side_x_selection = 8;
        byte up_side_y_selection = 0;

        byte height_selection = 16;
        byte width_selection = 128;

};


#endif //THERMISTOR_DISPLAY_H
