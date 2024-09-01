#include "time_app.h"

#include <ArduinoJson.h>

#define HTTP_TIMEOUT 5000

TimeApp time_app;

TimeApp::TimeApp() : ntp_client(ntpUDP, "pool.ntp.org", 60 * 60 * 8) {}

void TimeApp::init() {
    ntp_client.begin();
    wifi_client.setTimeout(HTTP_TIMEOUT);
}

// x: Width() - 200 ~ Width()
bool TimeApp::draw_time(BoardResource* res) {
    static char _time[6];
    static char time[6];
    static char _day[32];
    static char day[32];

    // int day = ntp_client.getDay();
    auto epoch_time = ntp_client.getEpochTime();
    auto timeinfo   = gmtime((time_t*)&epoch_time);
    int hour        = timeinfo->tm_hour;
    int minutes     = timeinfo->tm_min;
    sprintf(day, "%d年%02d月%02d日", timeinfo->tm_year + 1900,
            timeinfo->tm_mon + 1, timeinfo->tm_mday);
    sprintf(time, "%02d:%02d", hour, minutes);
    if (strcmp(time, _time)) {
        strcpy(_time, time);
        log_info("Time Update! Now Time is %s\n", time);
        Fonts.setFont(u8g2_font_inr49_mn);
        int cx = Epd.width() - Fonts.getUTF8Width(time),
            cy = Epd.height() / 2 + Fonts.getFontAscent() / 2;
        // log_info("Time Width: %d Time Height: %d\n",
        // Fonts.getUTF8Width(time), Fonts.getFontAscent());
        Fonts.setCursor(cx, cy);
        Fonts.print(time);

        strcpy(_day, day);
        log_info("Day Update! Now Day is %s\n", day);
        Fonts.setFont(u8g2_font_wqy16_t_gb2312);
        cx = cx + (200 - Fonts.getUTF8Width(day)) / 2,
        cy = Epd.height() / 2 + (49 + Fonts.getFontAscent()) / 2 + 15;
        Fonts.setCursor(cx, cy);
        Fonts.print(day);
        return true;
    }

    return false;
}

bool TimeApp::draw_wheather(BoardResource* res) {
    Fonts.setFont(u8g2_font_wqy16_t_gb2312);
    static String _weather_info;
    if (weather_info != _weather_info) {
        _weather_info = weather_info;
        Fonts.setCursor(0,
                        Epd.height() / 2 - 2 - (Fonts.getFontAscent() * 3) / 2);
        Fonts.row_spacing = 2;
        Fonts.print(weather_info);
        Fonts.row_spacing = 0;
        return true;
    }
    return false;
}

void TimeApp::update() {
    ntp_client.update();
    static ulong _millis = 0;
    if (millis() - _millis >= WHEATHER_INTERVAL) {
        _millis = millis();

        char url[255];
        sprintf(url, "%s?key=%s&location=%s&language=zh-Hans&unit=c",
                WHEATHER_API, WHEATHER_KEY, WHEATHER_CITY);
        log_info("Weather URL: %s\n", url);

        HTTPClient http_client;
        http_client.begin(wifi_client, url);

        int code = http_client.GET();
        log_info("Weather URL Get Code: %d\n", code);
        if (code == HTTP_CODE_OK) {
            JsonDocument result;
            auto error = deserializeJson(result, http_client.getString());
            if (error) {
                log_info("DeserializeJson Error, Json String: %s",
                         http_client.getString().c_str());
                weather_info = String("解析天气信息失败");
            }
            const String city    = result["results"][0]["location"]["name"];
            const String weather = result["results"][0]["now"]["text"];
            int temp             = result["results"][0]["now"]["temperature"];
            weather_info = String("城市:" + city + "\n温度:" + temp +
                                  "°C\n天气:" + weather);
            log_info("Weather Info: %s", weather_info.c_str());
        } else {
            log_info("Weather Get Error\n");
        }

        log_info("Wheather Update! Now EpochTime is %ld\n", _millis);
    }
}

void TimeApp::draw(BoardResource* res) {
    bool flush_flag = false;

    flush_flag |= draw_time(res);
    flush_flag |= draw_wheather(res);

    if (flush_flag) {
        flush(&res->epd);
    }
}