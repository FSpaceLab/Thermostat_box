#include "DHT.h"
#include "Keypad.h"
#include "display/display.h"

#define DHTTYPE DHT11

#define B 3950 // B-коэффициент
#define SERIAL_R 10000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 49900 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 18 // номинальная температура (при которой TR = 50 кОм)
#define COEF_THERMISTOR 269

// ALL PINS
#define THERMISTOR_PIN A0
#define DHTPIN 2
#define COOLER_COLD_PIN 4
#define COOLER_HEAT_PIN 3
#define PELTIER_PIN 6
#define HEAT_BED_PIN 7


const byte ROWS = 5; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
        {'f', 'F', '#', '*'},
        {'1', '2', '3', 'u'},
        {'4', '5', '6', 'd'},
        {'7', '8', '9', 'e'},
        {'<', '0', '>', 'E'}
};
byte rowPins[ROWS] = {30, 32, 34, 36, 38}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {46, 44, 42, 40}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);





DHT dht(DHTPIN, DHTTYPE);

unsigned long cooling_previous_millis = 0;
const long cooling_interval = 60000; 

int temp_i = 0;
const byte temp_data_size = 5;
float temp_data[temp_data_size];




float get_temp_from_thermistor() {
    int t = analogRead( THERMISTOR_PIN );
    // R (Om) from thermistor_
    float tr = SERIAL_R / (1023.0 / t - 1);
    // Themperature calculation (in *C)
    return (1.0 / (log(tr / THERMISTOR_R) / B + 1.0 / (NOMINAL_T + 273.15))) - COEF_THERMISTOR;
}


float get_temp_from_dht() {
    return dht.readTemperature();
}


void cooling(float temp, float current_temp) {
    unsigned long current_millis = millis();

    if (current_millis - cooling_previous_millis >= cooling_interval) {
        cooling_previous_millis = current_millis;
        Serial.println("tut");
        if (temp < get_temp_from_thermistor()) {
            digitalWrite(COOLER_COLD_PIN, HIGH);
            digitalWrite(COOLER_HEAT_PIN, HIGH);
            digitalWrite(PELTIER_PIN, HIGH);
        } else {
            digitalWrite(COOLER_COLD_PIN, LOW);
            digitalWrite(COOLER_HEAT_PIN, LOW);
            digitalWrite(PELTIER_PIN, LOW);
        }
    }
}


void heating(int temp, float current_temp) {
    unsigned long current_millis = millis();


    if (current_millis - cooling_previous_millis >= cooling_interval) {
        cooling_previous_millis = current_millis;
        
        if (temp > current_temp) {
            digitalWrite(HEAT_BED_PIN, HIGH);
        } else {
            digitalWrite(HEAT_BED_PIN, LOW);
        }
    }
}


float avg_temp() {   
    if (temp_i == temp_data_size) temp_i = 0;
    
    temp_data[temp_i++] = get_temp_from_thermistor();
    float avg = 0;
    for (int i = 0; i < temp_data_size; i++) avg += temp_data[i];
    
    return avg / temp_data_size;  
}


void setup() {
    Serial.begin( 9600 );

    u8g.setColorIndex(1);

    pinMode(THERMISTOR_PIN, INPUT);
    pinMode(DHTPIN, INPUT);

    pinMode(COOLER_COLD_PIN, OUTPUT);
    pinMode(COOLER_HEAT_PIN, OUTPUT);
    pinMode(PELTIER_PIN, OUTPUT);
    pinMode(HEAT_BED_PIN, OUTPUT);
}


void loop() {
//    float temp = avg_temp();
//    cooling(10, temp);
//    heating(20, temp);
//    Serial.print(get_temp_from_dht());
//    Serial.print(F("   "));
//    draw_main_page(temp);
//    Serial.println(temp);


    char customKey = customKeypad.getKey();

    if (customKey){
        draw_main_page(int(customKey));
        Serial.println(customKey);
    }

    delay(100);
}
