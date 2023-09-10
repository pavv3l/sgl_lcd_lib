#ifndef __SGL_ILI9341_H__
#define __SGL_ILI9341_H__

#include "sgl.h"
#include "ili9341_defs.h"

using PinName = uint;

namespace sgl
{
namespace ili9341
{

class SGLILI9341: public SGL
{
    public:
    SGLILI9341(uint16_t w, uint16_t h, SGL_hal_interface* deviceInterface, PinName DC, PinName CE, PinName RST);
    void init();
    void send_data(uint8_t data);
    void send_data16(uint16_t data);
    void send_command(uint8_t cmd);
    void send_command_parameter(uint8_t param);
    void drawPixel(uint16_t x, uint16_t y, uint16_t color = ILI9341_WHITE, Mode mode = Mode::pixelAND);
    void drawScreen();
    void set_active_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void fill_screen(uint16_t color = WHITE);
    void fill_screen2(uint16_t color = WHITE); // much faster than "fill_screen"
    // len is like x0 = x; x1 = x + len
    //void draw_horizontal_line(uint16_t x, uint16_t y, int16_t len, uint16_t color = ILI9341_WHITE, Mode mode = SGL::Mode::pixel_copy) override;
    //void draw_vertical_line(uint16_t x, uint16_t y, int16_t len, uint16_t color = ILI9341_WHITE, Mode mode = SGL::Mode::pixel_copy) override;
    void drawHorizontalLine2(uint16_t x, uint16_t y, int16_t len, uint16_t color = ILI9341_WHITE, Mode mode = Mode::pixelAND);
    void drawVerticalLine2(uint16_t x, uint16_t y, int16_t len, uint16_t color = ILI9341_WHITE, Mode mode = Mode::pixelAND);
    void reset();
    void reset2();
    void setRotation(uint8_t rot);
    void invertDisplay(bool invert);
    void scrollTo(uint16_t h);
    void setScrollMargins(uint16_t top, uint16_t bottom);
    void drawBitmap16(uint16_t* bitmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
//protected:
    bool wrapText = true; // zawijaj tekst

    PinName DC_;
    PinName CE_;
    PinName RST_;

    uint8_t contrast;
    uint8_t bias;

    SGL_hal_interface* dev = nullptr;
};

}

}

#endif