#include "sgl.h"

// you shuld use it only if you have enough memory
#define USE_FRAME_BUFFER
// framerate should be adjusted to the display size and the communication speed with the mcu
#define FRAMERATE 25

void SGL::drawLine(onst uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint16_t color = WHITE, const Mode mode = Mode::pixelAnd)
{
    if(x0 >= _width)
        x0 = _width - 1;
    if(x1 >= _width)
        x1 = _width - 1;
    if(y0 >= _height)
        y0 = _height - 1;
    if(y1 >= _height)
        y1 = _height - 1;

    uint16_t dx = std::abs(x0 - x1);
    uint16_t dy = std::abs(y0 - y1);

    if(dx == 0)
    {
        drawHorizontalLine(coord0, coord1, color, mode);
    }
    if(dy == 0)
    {
        drawVerticalLine(coord0, coord1, color, mode);
    }

    // signs of x and y axes
    int8_t x_mult = (x0 > x1) ? -1 : 1;
    int8_t y_mult = (y0 > y1) ? -1 : 1;

    // positive slope
    if(dy < dx)
    {
        int16_t d = (2 * dy) - dx;
        uint16_t y = 0;
        for(uint16_t x = 0; x <= dx; ++x)
        {
            drawPixel(x0 + (x * x_mult), y0 + (y * y_mult), color, mode);
            if(d > 0)
            {
                ++y;
                d -= dx;
            }
            d += dy;
        }
    }
    else // negative slope
    {
        int16_t d = (2 * dx) - dy;
        uint16_t x = 0;
        for(uint16_t y = 0; y <= dy; ++y)
        {
            drawPixel(x0 + (x * x_mult), y0 + (y * y_mult), color, mode);
            if(d > 0)
            {
                ++x;
                d -= dy;
            }
            d += dx;
        }
    }
}