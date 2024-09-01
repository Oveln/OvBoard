#include "board_webserver.h"

#include "home_page.h"
namespace board_webserver {
ESP8266WebServer server(80);
void home() { server.send(200, "text/html", homepage); }
void wifi_setting() {
    String ssid = server.arg("ssid"), password = server.arg("password");
    Serial.printf("ssid: %s\npassword: %s", ssid.c_str(), password.c_str());
    if (ssid.length() > 0 && ssid.length() < 32 && password.length() >= 0 &&
        password.length() < 32) {
        strcpy(Config.ssid, ssid.c_str());
        strcpy(Config.password, password.c_str());
        Config.commit();
        server.send(200, "text/plain", "设置成功，设备将会重启");
        Serial.println("ESP Will Reset...");
        ESP.reset();
    } else {
        server.send(200, "text/plain", "ssid or password ERROR!!");
    }
}
void init() {
    server.on("/", home);
    server.on("/wifi_setting", HTTP_POST, wifi_setting);
    server.begin();
}

}  // namespace board_webserver
