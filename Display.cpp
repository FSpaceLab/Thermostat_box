#include "Arduino.h"
#include "Display.h"
#include "U8glib.h"


U8GLIB_ST7920_128X64_4X u8g(SCK_DISPLAY, MOSI_DISPLAY, CS_DISPLAY);


Display::Display()
{
    u8g.setColorIndex(1);
}


void Display::draw_main_page(float temp, int set_temp) {
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
