#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include<vector>

using namespace sgl;

class SGL_TEST: public SGL
{
public:
    void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND)
    {
        switch (mode)
        {
        case Mode::pixelAND:
            buffer.at(x).at(x) =  color;
            break;
        default:
            break;
        }
    }
    std::vector<std::vector<uint16_t>> buffer // Frame 10 x 10
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };
    
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
            uint16_t x2, uint16_t y2, const uint16_t color, const Fill fill, const Mode mode), (override));
        
    MOCK_METHOD(void, drawCircle, (uint16_t x0, uint16_t y0, uint16_t radius,
            const uint16_t color, const Fill fill, const Mode mode), (override));
};

TEST(DRAW_PIXEL, SGLTESTS_DRAW)
{
    SGL_TEST sglUT;
    sglUT.drawPixel(0,0);
    EXPECT_EQ(sglUT.buffer[0][0],WHITE);
}