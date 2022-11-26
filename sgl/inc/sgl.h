#ifndef __SGL_H__
#define __SGL_H__

#include <stdint.h>
#include <stdlib.h>
#include <utility>
//#include <cstdint> // c++ version of stdint.h

// macros definitions for color converting
// 16 bit color 65k clors (frame buffer 240x320 = 153,6kB)
#define RGB565(r,g,b) ((((uint16_t)r & 0x00F8) << 8) | (((uint16_t)g & 0x00FC) << 3) | (((uint16_t)b & 0x00F8) >> 3))
// 12 bit color 4k colors (frame buffer 240x320 = 115,2kB)
#define RGB444(r,g,b) (((uint16_t)r & 0x00F0 << 8) | ((uint16_t)g & && 0x00F0 << 4) | ((uint16_t)b & && 0x00F0 >> 4))

// define 16bit(RGB565) colors
#define WHITE          0xFFFF
#define BLACK          0x0000
#define BLUE           0x001F
#define BRED           0XF81F
#define GRED           0XFFE0
#define GBLUE          0X07FF
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define BROWN          0XBC40
#define BRRED          0XFC07
#define GRAY           0X8430

#define UINT16TMAX(a, b) ((a < b) ? b : a)
#define UINT16TMIN(a, b) ((b < a) ? b : a)
#define SWAP(T, a, b) {T tmp = a; a = b; b = tmp;}

// for futher implementation
// DOT_PIXEL
//enum class DOT_PIXEL
//{
//    DOT1x1 = 0x01,
//    DOT2x2 = 0x02,
//    DOT3x3 = 0x03,
//    DOT4x4 = 0x04,
//    DOT5x5 = 0x05,
//    DOT6x6 = 0x06,
//    DOT7x7 = 0x07,
//    DOT8x8 = 0x08
//}

namespace sgl
{
    enum class Mode: uint8_t
    {
        pixelAND    = 0x0, // for ordinary drawing
        pixelOR     = 0x1, // mostly for BW displays
        pixelXOR    = 0x2,// mostly for BW displays
        pixelCLR    = 0x3 // for clear pixels
    };

    enum class Fill: uint8_t
    {
        solid   = 0x0, // color BLACK for BW displays
        hole    = 0x01 // color WHITE for BW displays
    };

    //struct Coord
    //{
    //    Coord(uint16_t xx, uint16_t yy) : x(xx), y(yy) {}

    //      uint16_t x = 0;
    //    uint16_t y = 0;
    //};


    class SGL
    {
    public:
        SGL(uint16_t x, uint16_t y): width_(x), height_(y) {}
        virtual ~SGL() {}

        virtual void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) = 0;
        
        virtual void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);

        virtual void drawHorizontalLine(uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        
        virtual void drawVerticalLine(uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);

        virtual void drawRectangle(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height,
            const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        
        virtual void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
            uint16_t x2, uint16_t y2, const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        
        virtual void drawCircle(uint16_t x0, uint16_t y0, uint16_t radius,
            const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);

    protected:
    /*
        void drawFastPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        void drawFastHorizontalLine(uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        void drawFastVerticalLine(uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
    */
        uint8_t buffer_[240*135*2] = {0};
        uint16_t width_;
        uint16_t height_;
        uint16_t x_start_ = 0; // x offset
        uint16_t y_start_ = 0; // y offset
    };

}


#endif