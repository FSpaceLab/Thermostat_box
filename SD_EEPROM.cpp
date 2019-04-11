//
// Created by navch on 11.04.2019.
//
#include "EEPROM.h"
#include "SD_EEPROM.h"


void SD_EEPROM::write(byte addr, int num) {
    byte raw[2];
    (int&)raw = num;
    for(byte i = 0; i < 2; i++) EEPROM.write(addr+i, raw[i]);
}

int SD_EEPROM::read(byte addr) {
    byte raw[2];
    for(byte i = 0; i < 2; i++) raw[i] = EEPROM.read(addr+i);
    int &num = (int&)raw;
    return num;
}