#include "config.h"

OvBoardConfig Config;

OvBoardConfig::OvBoardConfig() {}

void OvBoardConfig::reset() {
    magic = 2333;
    strcpy(password, "shanano1");
    strcpy(ssid, "CMCC-OvelnRoom");
    commit();
}

void OvBoardConfig::init() {
    Serial.printf("Config Size: %d\n", sizeof(OvBoardConfig));
    Serial.printf("Config Load Start\n");
    EEPROM.begin(sizeof(Config));
    byte* ptr = (byte*)(this);
    for (int i = 0; i < sizeof(OvBoardConfig); i++) {
        *ptr = EEPROM.read(i);
        ptr++;
    }
    EEPROM.end();
    print();
    if (this->magic != 2333) {
        Serial.printf("Config Load Failed...\n");
        reset();
    } else {
        Serial.printf("Config Load Success\n");
    }
}

void OvBoardConfig::commit() {
    Serial.printf("Config Commit...\n");
    print();
    EEPROM.begin(sizeof(Config));
    byte* ptr = (byte*)this;
    for (int i = 0; i < sizeof(OvBoardConfig); i++) {
        EEPROM.write(i, *ptr);
        ptr++;
    }
    EEPROM.end();
    Serial.printf("Config Commit Success!\n");
}

void OvBoardConfig::print() {
    Serial.printf(
        R"(-----------------------------------
[Magic]   : %d
[SSID]    : %s
[Password]: %s
-----------------------------------
)",
        magic, ssid, password);
}