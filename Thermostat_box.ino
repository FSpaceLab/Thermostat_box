#include "Configuration.h"
#include "Thermostat.h"
//#include "Display.h"
#include "U8glib.h"

// Object for get data from thermistor
Thermistor thermistor(THERMISTOR_PIN, B, SERIAL_R, THERMISTOR_R, NOMINAL_T, COEF_THERMISTOR);

// Object for manage thermostat. Setting temperature in box
Thermostat thermostat(HEATER_PIN, COOLER_PIN, COOLER_FAN_COLD_PIN, COOLER_FAN_HEAT_PIN,
                      COOLING_INTERVAL, HEATING_INTERVAL);

U8GLIB_ST7920_128X64_4X u8g(13, 11, 10);

String current_t_text = "t: ";
String set_t_text = " | set t: ";


byte SET_T = 33;


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


void setup()
{
    Serial.begin(9600);
    u8g.setColorIndex(1);
}

void loop()
{
    thermostat.set_t(SET_T, thermistor);
    draw_main_page(thermistor.get_t(), SET_T);
}
