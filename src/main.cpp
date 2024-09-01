#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiAP.h>
#include <board.h>
#include <board_webserver.h>
#include <config.h>
#include <setting_app.h>
#include <time_app.h>

BoardApp* apps[] = {&time_app};

void setup() {
    Serial.begin(9600);
    Serial.println();

    Config.init();
    board.init();
    setting_app.init();
    board_webserver::init();
    for (auto app : apps) app->init();

    board.switch_app(&setting_app);
    while (setting_app.get_status() != WL_CONNECTED) {
        board_webserver::server.handleClient();
        setting_app.update();
        board.draw();
    }
    delay(1000);

    board.switch_app(apps[0]);
    Serial.println("Inited");
}

void loop() {
    board_webserver::server.handleClient();
    if (setting_app.get_is_disconnected()) {
        board.switch_app(&setting_app);
        setting_app.update();
    } else {
        for (auto app : apps) app->update();
    }
    board.draw();
}