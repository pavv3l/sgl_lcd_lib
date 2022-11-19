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

#define WHITE 0xFFFF
#define BLACK 0x0000

#define UINT16TMAX(a, b) ((a < b) ? b : a)
#define UINT16TMIN(a, b) ((b < a) ? b : a)

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
        virtual void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) = 0;
        //virtual void drawPixel(const Coord& coord, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) = 0;
        
        virtual void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        // line with length 0 == nothing, line with length 1 == one pixel
        //virtual void drawLine(const Coord& coord0, const Coord& coord1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
    protected:
        // for faster drawing you should override these functions (horizonatal and vertical line)
        virtual void drawHorizontalLine(uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        //virtual void drawHorizontalLine(const Coord& coord0, const Coord& coord1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        
        virtual void drawVerticalLine(uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
        //virtual void drawVerticalLine(const Coord& coord0, const Coord& coord1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND);
    public:
        virtual void drawRectangle(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height,
            const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        //virtual void drawRectangle(const Coord& coord0, const Coord& coord1,
        //    const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        
        virtual void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
            uint16_t x2, uint16_t y2, const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        //virtual void drawTriangle(const Coord& coord0, const Coord& coord1, const Coord& coord2,
        //    const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        
        virtual void drawCircle(uint16_t x0, uint16_t y0, uint16_t radius,
            const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);
        //virtual void drawCircle(const Coord& coord, const uint16_t radius,
        //    const uint16_t color = WHITE, const Fill fill = Fill::hole, const Mode mode = Mode::pixelAND);

    protected:
        uint16_t _width;
        uint16_t _height;
    };

}


#endif