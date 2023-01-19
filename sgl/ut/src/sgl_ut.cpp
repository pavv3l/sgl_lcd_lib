#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include<vector>
#include <vector>
#include <memory>

using namespace sgl;
using testing::_;

class SGL_TEST: public SGL
{
public:
    SGL_TEST(uint16_t x_, uint16_t y_) : SGL(x_, y_) {}
    void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND)
    {
    }
};


class SGL_MOCK: public SGL
{
public:
    SGL_MOCK(uint16_t x_, uint16_t y_) : SGL(x_, y_) {}
    MOCK_METHOD(void, drawPixel,(uint16_t x, uint16_t y, const uint16_t color, const Mode mode), (override));
    MOCK_METHOD(void, drawScreen, (), (override));
    //MOCK_METHOD(void, drawHorizontalLine, (uint16_t x0, uint16_t y0, int16_t len, const uint16_t color, const Mode mode), (override));
    //MOCK_METHOD(void, drawVerticalLine, (uint16_t x0, uint16_t y0, int16_t len, const uint16_t color, const Mode mode), (override));
    //MOCK_METHOD(void, drawRectangle, (uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, const uint16_t color, const Fill fill, const Mode mode), (override));
    //MOCK_METHOD(void, drawTriangle, (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t color, const Fill fill, const Mode mode), (override));
    //MOCK_METHOD(void, drawCircle, (uint16_t x0, uint16_t y0, uint16_t radius, const uint16_t color, const Fill fill, const Mode mode), (override));
};

TEST(DRAW, DRAWLINE_1)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(9);
    sglMock.drawLine(0, 0, 9, 0);
}

TEST(DRAW, DRAWLINE_2)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(9);
    sglMock.drawLine(9, 0, 0, 0);
}

TEST(DRAW, drawHorizontalLine_1)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(9);
    sglMock.drawHorizontalLine(0, 0, 9);
}

TEST(DRAW, drawHorizontalLine_2)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(9);
    sglMock.drawHorizontalLine(9, 0, -9);
}