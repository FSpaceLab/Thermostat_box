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
        void draw_set_light(byte state, byte _UV, byte _R, byte _G, byte _B);
        void draw_set_co2(bool state, byte co2);
        void update_current_position(bool update, byte max_len);
        // attributes
        byte cur_pos_set_t = 0;
        byte max_len_t = 2;
        byte max_len_light = 5;
        byte max_len_co2 = 2;
        byte cursor = 0;

    private:

        // texts for display
        String current_t_text = "cur. t: ";
        String degrees_by_C = " C";

        String set_t_text = "set t: ";

        const char *cooling_state = "cooling";
        const char *heating_state = "heating";

        const char *off_state = "Off";
        const char *on_state = "On";
        const char *rgb_state = "RGB On";
        const char *uv_state = "UV On";
        const char *rgb_uv_state = "Both light On";

        const char *blank_text = "";
        const char *uv_text = "UV:";
        const char *r_text = "R:";
        const char *g_text = "G:";
        const char *b_text = "B:";

        const char *l_arrow = "<";
        const char *r_arrow = ">";

        byte full_width = 128;
        byte full_heigth = 64;

        byte text_x = 13;
        byte arrow_l_x = 3;
        byte arrow_r_x = 120;
};


#endif //THERMISTOR_DISPLAY_H
