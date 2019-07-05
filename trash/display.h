//
// Created by navch on 28.02.2019.
//


#ifndef THERMISTOR_DISPLAY_H
#define THERMISTOR_DISPLAY_H

#include "Arduino.h"
#include "U8glib.h"

U8GLIB_ST7920_128X64_4X u8g(13, 11, 10);

String current_t_text = "t: ";
String set_t_text = " | set t: ";


byte SET_T = 60;


void draw_main_page(float temp, int set_temp) {
    String text = current_t_text + int(temp) + set_t_text + set_temp;

    const uint8_t len_text = text.length() + 1;

    char char_text[len_text];
    text.toCharArray(char_text, len_text);

    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_6x12);
        u8g.drawStr( 0, 10, char_text);
    } while( u8g.nextPage() );

}

#endif //THERMISTOR_DISPLAY_H
