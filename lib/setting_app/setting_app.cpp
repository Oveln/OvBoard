#include "setting_app.h"

#include <board_webserver.h>

SettingApp setting_app;

SettingApp::SettingApp() {}

void SettingApp::init() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(Config.ssid, Config.password);
    timestamp = millis();
}

void SettingApp::update() {
    switch (status) {
        case WL_CONNECTED: {
            status = WiFi.status();
            if (status != WL_CONNECTED) {
                timestamp = millis();
            }
            break;
        }
        default: {
            status = WiFi.status();
            // open AP WiFi
            if (millis() - timestamp >= CONNECT_TIMEOUT && !is_disconnected) {
                log_info("Open WiFi AP\n");
                WiFi.mode(WIFI_AP_STA);
                WiFi.softAP(AP_SSID, AP_PASSWORD);
                log_info("APIP: %s\n", WiFi.softAPIP().toString().c_str());
                log_info("AP_SSID: %s\n", AP_SSID);
                log_info("AP_PASSWORD: %s\n", AP_PASSWORD);
                is_disconnected = true;
                status          = WL_CONNECT_FAILED;
            }
            break;
        }
    }
}

void SettingApp::draw(BoardResource* res) {
    static wl_status_t _status = WL_NO_SHIELD;
    const String connecting("正在连接...");
    const String connected("连接成功");
    const String connect_failed("无连接");
    if (status == _status) return;
    _status = status;
    Epd.fillScreen(GxEPD_WHITE);
    Fonts.setFont(u8g2_font_wqy16_t_gb2312);
    if (is_disconnected) {
        int h = Epd.height() / 2, wh = Fonts.getFontAscent(), row_spacing = 5;
        Fonts.setCursor(Epd.width() / 2 - Fonts.getUTF8Width("无连接") / 2,
                        h - wh - row_spacing);
        Fonts.print("无连接");
        Fonts.setCursor(Epd.width() / 2 - (Fonts.getUTF8Width("请连接") +
                                           Fonts.getUTF8Width(AP_SSID)) /
                                              2,
                        h);
        Fonts.print("请连接"), Fonts.print(AP_SSID);
        Fonts.setCursor(
            Epd.width() / 2 -
                (Fonts.getUTF8Width("访问") +
                 Fonts.getUTF8Width(WiFi.softAPIP().toString().c_str()) +
                 Fonts.getUTF8Width("进行设置")) /
                    2,
            h + wh + row_spacing);
        Fonts.print("访问"), Fonts.print(WiFi.softAPIP().toString()),
            Fonts.print("进行设置");
        Fonts.setCursor(
            Epd.width() / 2 - (Fonts.getUTF8Width("或按下RESET键重启")) / 2,
            h + (wh + row_spacing) * 2);
        Fonts.print("或按下RESET键重启");
    } else {
        switch (status) {
            case WL_CONNECTED: {
                Fonts.setCursor(
                    Epd.width() / 2 - Fonts.getUTF8Width(connected.c_str()) / 2,
                    Epd.height() / 2 - Fonts.getFontAscent() / 2);
                Fonts.print(connected);
                log_info("IP: %s\n", WiFi.localIP().toString().c_str());
                break;
            }
            default: {
                Fonts.setCursor(Epd.width() / 2 -
                                    Fonts.getUTF8Width(connecting.c_str()) / 2,
                                Epd.height() / 2 - Fonts.getFontAscent() / 2);
                Fonts.print(connecting);
                break;
            }
        }
    }
    flush(&Epd);
}

wl_status_t SettingApp::get_status() { return status; }

bool SettingApp::get_is_disconnected() { return is_disconnected; }