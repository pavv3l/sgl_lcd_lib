#ifndef __SGL_H__
#define __SGL_H__

#inlcude <stdint.h>
#include <utility>
//#include <cstdint> // c++ version of stdint.h

// macros definitions for color converting
// 16 bit color 65k clors (frame buffer 240x320 = 153,6kB)
#define RGB565(r,g,b) ((((uint16_t)r & 0x00F8) << 8) | (((uint16_t)g & 0x00FC) << 3) | (((uint16_t)b & 0x00F8) >> 3))
// 12 bit color 4k colors (frame buffer 240x320 = 115,2kB)
#define RGB444(r,g,b) (((uint16_t)r & 0x00F0 << 8) | ((uint16_t)g & && 0x00F0 << 4) | ((uint16_t)b & && 0x00F0 >> 4))

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
    }

    //struct Coord
    //{
    //    Coord(uint16_t xx, uint16_t yy) : x(xx), y(yy) {}

    //      uint16_t x = 0;
    //    uint16_t y = 0;
    //};


    class SGL
    {
    public:
        virtual void drawPixel(const uint16_t x, const uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd) = 0;
        //virtual void drawPixel(const Coord& coord, const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd) = 0;
        
        virtual void drawLine(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd);
        // line with length 0 == nothing, line with length 1 == one pixel
        //virtual void drawLine(const Coord& coord0, const Coord& coord1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd);
        
        // for faster drawing you should override these functions (horizonatal and vertical line)
        virtual void drawHorizontalLine(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd)
        //virtual void drawHorizontalLine(const Coord& coord0, const Coord& coord1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd);
        
        virtual void drawVerticalLine(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd)
        //virtual void drawVerticalLine(const Coord& coord0, const Coord& coord1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd);

        virtual void drawRectangle(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1,
            const uint16_t color = WHITE, const Fill fill = Fill:hole, const Mode mode = Mode::pixelAnd);
        //virtual void drawRectangle(const Coord& coord0, const Coord& coord1,
        //    const uint16_t color = WHITE, const Fill fill = Fill:hole, const Mode mode = Mode::pixelAnd);
        
        virtual void drawTriangle(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1,
            const uint16_t x2, const uint16_t y2, const uint16_t color = WHITE, const Fill fill = Fill:hole, const Mode mode = Mode::pixelAnd);
        //virtual void drawTriangle(const Coord& coord0, const Coord& coord1, const Coord& coord2,
        //    const uint16_t color = WHITE, const Fill fill = Fill:hole, const Mode mode = Mode::pixelAnd);
        
        virtual void drawCircle(const uint16_t x0, const uint16_t y0, const uint16_t radius,
            const uint16_t color = WHITE, const Fill fill = Fill:hole, const Mode mode = Mode::pixelAnd);
        //virtual void drawCircle(const Coord& coord, const uint16_t radius,
        //    const uint16_t color = WHITE, const Fill fill = Fill:hole, const Mode mode = Mode::pixelAnd);

    protected:
        uint16_t _width;
        uint16_t _height;
    };

}


#endif