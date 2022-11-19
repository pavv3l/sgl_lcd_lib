#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace sgl;

class SGL_TEST: public SGL
{
public:
    void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND)
    {
        ;
    }

    uint16_t buffer[10][10];
};

class SGL_MOCK: public SGL
{
public:
    void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND)
    {
        ;
    }       
    MOCK_METHOD(void, drawLine, (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
            const uint16_t color, const Mode mode), (override));
/*
protected:
    MOCK_METHOD(void, drawHorizontalLine, (uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) (override));
        
    MOCK_METHOD(void, drawVerticalLine, (uint16_t x0, uint16_t y0, int16_t len,
            const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) (override));
*/
public:
    MOCK_METHOD(void, drawRectangle, (uint16_t x0, uint16_t y0, uint16_t width, uint16_t height,
            const uint16_t color, const Fill fill , const Mode mode), (override));
        
    MOCK_METHOD(void, drawTriangle, (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
            const uint16_t x2, const uint16_t y2, const uint16_t color, const Fill fill, const Mode mode), (override));
        
    MOCK_METHOD(void, drawCircle, (uint16_t x0, uint16_t y0, const uint16_t radius,
            const uint16_t color, const Fill fill, const Mode mode), (override));
};