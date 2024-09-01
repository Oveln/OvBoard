#include "board.h"

#include "Fonts/FreeMonoBold9pt7b.h"

Board board;

BoardResource::BoardResource() : epd(GxEPD2_290_T5D(2, 4, 5, 16)) {}

Board::Board() : res() {}

BoardApp* Board::get_app() { return now_app; }

void Board::init() {
    // epd.init(9600, false, 200, false);
    res.epd.init();

    res.u8g2_fonts.begin(res.epd);
    res.u8g2_fonts.setForegroundColor(GxEPD_BLACK);
    res.u8g2_fonts.setBackgroundColor(GxEPD_WHITE);
    // res.u8g2_fonts.setFont(u8g2_font_wqy12_t_chinese3);
    res.epd.setTextColor(GxEPD_BLACK);

    res.epd.setFullWindow();
    res.epd.setRotation(3);
    res.epd.firstPage();
}

void Board::draw() {
    if (now_app != nullptr) now_app->draw(&res);
}

void Board::switch_app(BoardApp* mode) {
    now_app = mode;
    now_app->switched(&res);
}