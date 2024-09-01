#pragma once

#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>

#include "board_app.h"

class BoardResource {
   public:
    GxEPD2_BW<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT> epd;
    U8G2_FOR_ADAFRUIT_GFX u8g2_fonts;
    BoardResource();
};

class Board {
   private:
    BoardResource res;
    BoardApp* now_app = nullptr;

   public:
    Board();
    void init();
    BoardApp* get_app();
    void switch_app(BoardApp*);
    void draw();
};

extern Board board;