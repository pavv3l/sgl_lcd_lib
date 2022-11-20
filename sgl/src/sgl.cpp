#include "sgl.h"

// you shuld use it only if you have enough memory
#define USE_FRAME_BUFFER
// framerate should be adjusted to the display size and the communication speed with the mcu
#define FRAMERATE 25

#define CHECK_LINE_PARAMETRS
#define CHECK_PIXEL_PAPARATERS


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
#ifdef CHECK_LINE_PARAMETRS
    if((x0 + len) > _width )
    {
        len = _width - x0;
    }
    else if((x0 + len) < 0)
    {
        len = -x0;
    }
#endif

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
#ifdef CHECK_LINE_PARAMETRS
    if((y0 + len) > _height )
    {
        len = _width - y0;
    }
    else if((y0 + len) < 0)
    {
        len = -y0;
    }
#endif

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

    // the drawLine function checks the argunents
    /*
    if(x0 >= _width)
        x0 = _width - 1;
    if(x1 >= _width)
        x1 = _width -1;
    if(x2 >= _width)
        x2 = _width -1;
    if(y0 >= _height)
        y0 = _height - 1;
    if(y1 >= _height)
        y1 = _height - 1;
    if(y2 >= _height)
        y2 = _height - 1;
    */

    // if transparent, just draw outline
    if(fill == Fill::hole)
    {
        drawLine(x0, y0, x1, y1, color, mode);
        drawLine(x1, y1, x2, y2, color, mode);
        drawLine(x2, y2, x0, y0, color, mode);
    }
    else
    {
        // not implemented yet, draw outline only
        drawLine(x0, y0, x1, y1, color, mode);
        drawLine(x1, y1, x2, y2, color, mode);
        drawLine(x2, y2, x0, y0, color, mode);
    }
}
        
void SGL::drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, const uint16_t color, const Fill fill, const Mode mode)
{
    if(radius <= 0)
        return;
    // from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm

    int16_t x = radius;
    int16_t y = 0;
    int16_t radiusError = 1 -x;

    while (x >= y)
    {

        // if transparent, just draw outline
        if (fill == Fill::hole)
        {
            drawPixel( x + x0,  y + y0, color, mode);
            drawPixel(-x + x0,  y + y0, color, mode);
            drawPixel( y + x0,  x + y0, color, mode);
            drawPixel(-y + x0,  x + y0, color, mode);
            drawPixel(-y + x0, -x + y0, color, mode);
            drawPixel( y + x0, -x + y0, color, mode);
            drawPixel( x + x0, -y + y0, color, mode);
            drawPixel(-x + x0, -y + y0, color, mode);
        }
        else
        { // drawing filled circle, so draw lines between points at same y value
            drawLine(x + x0,  y + y0, -x + x0,  y + y0, color, mode);
            drawLine(y + x0,  x + y0, -y + x0,  x + y0, color, mode);
            drawLine(y + x0, -x + y0, -y + x0, -x + y0, color, mode);
            drawLine(x + x0, -y + y0, -x + x0, -y + y0, color, mode);
        }

        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}
            

}