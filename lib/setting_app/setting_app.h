#pragma once
#include <ESP8266WiFi.h>
#include <board.h>
#include <config.h>

class SettingApp : public BoardApp {
   private:
    static constexpr const char* AP_SSID     = "OvBoard";
    static constexpr const char* AP_PASSWORD = "";
    static const ulong CONNECT_TIMEOUT       = 10 * 1000;  // millis
    wl_status_t status;
    bool is_disconnected = false;
    ulong timestamp;

   public:
    const char* get_app_name() const override { return "WiFiApp"; }
    SettingApp(/* args */);
    void init() override;
    void update();
    void draw(BoardResource*);
    wl_status_t get_status();
    bool get_is_disconnected();
};

extern SettingApp setting_app;