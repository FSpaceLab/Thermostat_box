//
// Created by navch on 11.04.2019.
// SAVE DATA TO EEPROM
//

#ifndef THERMOSTAT_BOX_SD_EEPROM_H
#define THERMOSTAT_BOX_SD_EEPROM_H

#include "Arduino.h"

class SD_EEPROM {
    public:
        void write(byte addr, int num);
        int read(byte addr);
};


#endif //THERMOSTAT_BOX_SD_EEPROM_H
