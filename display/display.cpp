#include "U8glib.h"

U8GLIB_ST7920_128X64_4X u8g(13, 11, 10);    // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
String temperature_text = "Temperature: ";



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
