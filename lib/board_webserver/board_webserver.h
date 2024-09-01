#pragma once

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <config.h>
namespace board_webserver {
extern ESP8266WebServer server;
void home();
void wifi_setting();
void init();

}  // namespace board_webserver
