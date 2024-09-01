#pragma once

#include <Arduino.h>
#include <EEPROM.h>

class OvBoardConfig {
   public:
    OvBoardConfig();
    int magic;  // it must be 2333
    char password[32];
    char ssid[32];
    void init();
    void commit();
    void reset();
    void print();
};

extern OvBoardConfig Config;