//
// Created by navch on 28.02.2019.
//


#ifndef THERMISTOR_DISPLAY_H
#define THERMISTOR_DISPLAY_H

#include "Arduino.h"
#include "U8glib.h"


U8GLIB_ST7920_128X64_4X u8g(13, 11, 10);



void draw_main_page(float temperature) {
    u8g.firstPage();
    do {

        String text = temperature_text + int(temperature); //

        const uint8_t len_text = text.length() + 1;

        char char_text[len_text];
        text.toCharArray(char_text, len_text);

        u8g.setFont(u8g_font_6x12);
        u8g.drawStr(10, 10, char_text);

    } while (u8g.nextPage());
}

//class Display {
//    public:
//        Display(byte sck_pin=13, byte mosi_pin=11, byte cs_pin=10);
//        void draw_main_page(float temperature);
//
//    private:
//        byte _sck_pin, _mosi_pin, _cs_pin;
//        String TEMPERATURE_TEXT = "Temperature: ";
//        U8GLIB_ST7920_128X64_4X u8g;
//
//};

#endif //THERMISTOR_DISPLAY_H
