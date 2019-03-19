//
// Created by B. Korzhak on 01.03.2019.
//

#ifndef TS_KEYPAD_H
#define TS_KEYPAD_H

#include "Arduino.h"
#include "Keypad.h"
#include "Configuration.h"

const byte ROWS = 5; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = KEYPAD_MATRIX;

byte rowPins[ROWS] = KEYPAD_ROW; //connect to the row pinouts of the keypad
byte colPins[COLS] = KEYPAD_COLS; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char get_key() {
    return customKeypad.getKey();
}

#endif //TS_KEYPAD_H
