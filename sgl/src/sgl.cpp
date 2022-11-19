#include "sgl.h"

// you shuld use it only if you have enough memory
#define USE_FRAME_BUFFER
// framerate should be adjusted to the display size and the communication speed with the mcu
#define FRAMERATE 25

#define CHECK_LINE_PARAMETRS


namespace sgl
{

void SGL::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t color, const Mode mode)
{
#ifdef CHECK_LINE_PARAMETRS
    if(x0 >= _width)
        x0 = _width - 1;
    if(x1 >= _width)
        x1 = _width - 1;
    if(y0 >= _height)
        y0 = _height - 1;
    if(y1 >= _height)
        y1 = _height - 1;
#endif

    uint16_t dx = abs(x0 - x1);
    uint16_t dy = abs(y0 - y1);

    // signs of x and y axes
    int8_t x_mult = (x0 > x1) ? -1 : 1;
    int8_t y_mult = (y0 > y1) ? -1 : 1;

    if(dx == 0)
    {
        drawVerticalLine(x0, y0, (y1 - y0 + y_mult), color, mode);
    }
    if(dy == 0)
    {
        drawHorizontalLine(x0, y0, (x1 - x0 + x_mult), color, mode);
    }

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
    if(dx == dy)
    {
        drawPixel(x0, y0, color, mode);
    }
}

void SGL::drawHorizontalLine(uint16_t x0, uint16_t y0, int16_t len, const uint16_t color, const Mode mode)
{
    if(len > 0)
    {
        for(int16_t i = 0; i < len; ++i)
        {
            drawPixel(x0 + i, y0, color, mode);
        }
    }
    else if(len < 0)
    {
        for(int16_t i = 0; i > len; --i)
        {
            drawPixel(x0 + i, y0, color, mode);
        }
    }
    else
    {
        //do nothing
    }
}

void SGL::drawVerticalLine(uint16_t x0, uint16_t y0, int16_t len, const uint16_t color, const Mode mode)
{
    if(len > 0)
    {
        for(int16_t i = 0; i < len; ++i)
        {
            drawPixel(x0, y0 + 1, color, mode);
        }
    }
    else if(len < 0)
    {
        for(int16_t i = 0; i > len; --i)
        {
            drawPixel(x0, y0 + 1, color, mode);
        }
    }
    else
    {
        //do nothing
    }
}

void SGL::drawRectangle(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, const uint16_t color, const Fill fill, const Mode mode)
{
    uint16_t x1 = x0 + width;
    uint16_t y1 = y0 + height;

    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;

    if(dx == 0)
    {
        drawVerticalLine(x0, y0, (y1 - y0 + 1), color, mode);
        return;
    }
    else if(dy == 0)
    {
        drawHorizontalLine(x0, y0, (x1 - x0 + 1), color, mode);
        return;
    }

    if(fill == Fill::solid)
    {
        if(dx > dy) // slightly better efficiency
        {
            //horizontal
            int16_t len = x1 - x0 + 1;
            for(uint16_t i = x0; i <= x1; ++i)
            {
                drawHorizontalLine(i, y0, len, color,mode);
            }
        }
        else
        {   
            //vertical
            int16_t len = y1 - y0 + 1;
            drawVerticalLine(x0, y0, len, color, mode);
        }
    }
    else
    {
        int16_t lenX = x1 - x0 + 1;
        int16_t lenY = y1 - y0 + 1;
        drawHorizontalLine(x0, y0, lenX, color, mode);
        drawHorizontalLine(x0, y1, lenX, color, mode);
        drawVerticalLine(x0, y0, lenY, color, mode);
        drawVerticalLine(x1, y0, lenY, color, mode);
    }
}

void SGL::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t x2, const uint16_t y2, const uint16_t color, const Fill fill, const Mode mode)
{
    ;
}
        
void SGL::drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, const uint16_t color, const Fill fill, const Mode mode)
{
    ;
}
            

}