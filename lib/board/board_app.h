#pragma once

#include <Ticker.h>

#include "board.h"
#define Fonts (res->u8g2_fonts)
#define Epd (res->epd)

class BoardResource;

class BoardApp {
   protected:
    void flush(GxEPD2_BW<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT>* epd) {
        static int count = 0;
        count            = (count + 1) % 5;
        if (!count) {
            epd->display(false);
        } else {
            epd->display(true);
            epd->hibernate();
        }
    }
    void log_info(const char* str, ...) {
        va_list args;
        char buffer[256];
        va_start(args, str);

        vsniprintf(buffer, sizeof(buffer), str, args);

        Serial.printf("[%s] %s", get_app_name(), buffer);

        va_end(args);
    }

   public:
    virtual const char* get_app_name() const = 0;
    virtual void update();
    virtual void draw(BoardResource* res) = 0;
    void switched(BoardResource* res) {
        log_info("switch to %s", get_app_name());
    }
    virtual void init() = 0;
};