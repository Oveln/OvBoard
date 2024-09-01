#pragma once

#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <board.h>

class TimeApp : public BoardApp {
   private:
    static constexpr const char* WHEATHER_UID  = "PcQIB4R8ZhFQwe6w_";
    static constexpr const char* WHEATHER_KEY  = "SNYO0NhwZLxOGekJ5";
    static constexpr const char* WHEATHER_CITY = "Quzhou";
    static constexpr const char* WHEATHER_API =
        "http://api.seniverse.com/v3/weather/now.json";
    static const ulong WHEATHER_INTERVAL = 5 * 60 * 1000;  // sec

    String weather_info;
    WiFiUDP ntpUDP;
    NTPClient ntp_client;
    WiFiClient wifi_client;
    bool draw_time(BoardResource*);
    bool draw_wheather(BoardResource*);

   public:
    const char* get_app_name() const override { return "TimeApp"; }
    TimeApp();
    void init() override;
    void update();
    void draw(BoardResource*) override;
};

extern TimeApp time_app;