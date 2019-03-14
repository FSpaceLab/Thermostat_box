#include "Arduino.h"
#include "Display.h"
#include "U8glib.h"


U8GLIB_ST7920_128X64_4X u8g(SCK_DISPLAY, MOSI_DISPLAY, CS_DISPLAY);


Display::Display()
{
    u8g.setColorIndex(1);
}


void Display::draw_main_page(float temp, int set_temp) {
    String text = current_t_text + temp + degrees_by_C;

    const uint8_t len_text = text.length() + 1;

    char char_text[len_text];
    text.toCharArray(char_text, len_text);

    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_6x12);
        u8g.drawStr(5, 10, char_text);
        u8g.drawLine(5, 13, 123, 13);
    } while( u8g.nextPage() );

}


void Display::draw_set_t(byte moving, bool state, byte temperature) {
    // byte moving - move the cursor, 1 - down, 2 - up, 0 - current position

    if (state) {
        len_text = on_state.length() + 1;
        char_text_state = new char[len_text];


        temp_text += temperature;
        len_temp_text = temp_text.length() + 1;

        temp_text.toCharArray(char_temp_text, len_temp_text);
        on_state.toCharArray(char_text_state, len_text);
    }
    else {
        len_text = off_state.length()+1;
        char_text = new char[len_text];

        off_state.toCharArray(char_text_state, off_state.length()+1);
    }



    // DRAWING PAGE
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_6x12);
        u8g.drawBox(up_side_y_selection, up_side_x_selection, width_selection, height_selection);


        if (cur_pos_set_t == 0) {
            u8g.setColorIndex(0);
        }

        u8g.drawStr( 0, 20, "<");
        u8g.drawStr( 55, 20, char_text_state);
        u8g.drawStr( 123, 20, ">");
        u8g.setColorIndex(1);

        if (state) {
            u8g.drawStr( 0, 20, "<");
            u8g.drawStr( 55, 20, char_temp_text);
            u8g.drawStr( 123, 20, ">");
        }

    } while( u8g.nextPage() );

}
