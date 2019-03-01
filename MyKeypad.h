//
// Created by navch on 01.03.2019.
//

#ifndef TS_KEYPAD_H
#define TS_KEYPAD_H

#include "Arduino.h"
#include "Keypad.h"

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

char get_key() {
    return customKeypad.getKey();
}

#endif //TS_KEYPAD_H
