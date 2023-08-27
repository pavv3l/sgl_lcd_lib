#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include<vector>
#include <vector>
#include <memory>
#include <string.h>

using namespace sgl;
using testing::_;

class SGL_TEST: public SGL
{
public:
    SGL_TEST(uint16_t x_, uint16_t y_) : SGL(x_, y_)
    {
        int_buffer = (uint16_t*)malloc(sizeof(uint16_t) * width_ * height_);
        memset(int_buffer, 0, sizeof(uint16_t) * width_ * height_);
    }
    uint16_t* int_buffer;
};


class SGL_MOCK: public SGL
{
public:
    SGL_MOCK(uint16_t x_, uint16_t y_) : SGL(x_, y_) {}
    MOCK_METHOD(void, drawPixel,(uint16_t x, uint16_t y, const uint16_t color, const Mode mode), (override));
    MOCK_METHOD(void, drawScreen, (), (override));
};

TEST(DRAWLINE, DRAWLINE_1)
{
    SGL_MOCK sglMock(10, 10);
    //EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    EXPECT_CALL(sglMock, drawPixel(0, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(1, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(2, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(3, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(4, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(5, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(6, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(7, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(8, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(9, 0, _, _));
    sglMock.drawLine(0, 0, 9, 0);
}

TEST(DRAWLINE, DRAWLINE_2)
{
    SGL_MOCK sglMock(10, 10);
    //EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    EXPECT_CALL(sglMock, drawPixel(9, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(8, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(7, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(6, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(5, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(4, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(3, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(2, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(1, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(0, 0, _, _));
    sglMock.drawLine(9, 0, 0, 0);
}

TEST(DRAWLINE, DRAWLINE_3)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawLine(9, 0, 0, 0);
}

TEST(DRAWLINE, DRAWLINE_4)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawLine(0, 0, 9, 9);
}

TEST(DRAWLINE, DRAWLINE2_1)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawLine2(0, 0, 9, 9);
}

TEST(DRAWLINE, drawHorizontalLine_1)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawHorizontalLine(0, 0, 9);
}

TEST(DRAWLINE, drawHorizontalLine_2)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawHorizontalLine(9, 0, -9);
}

TEST(DRAWLINE, drawHorizontalLine_3)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawHorizontalLine(9, 0, -11);
}

TEST(DRAWLINE, drawVerticalLine_1)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawVerticalLine(0, 0, 9);
}

TEST(DRAWLINE, drawVerticalLine_2)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawVerticalLine(0, 9, -9);
}

TEST(DRAWLINE, drawVerticalLine_3)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(_, _, _, _)).Times(10);
    sglMock.drawVerticalLine(0, 9, -10);
}

TEST(DRAWLINE, drawVerticalLine_4)
{
    SGL_MOCK sglMock(10, 10);
    EXPECT_CALL(sglMock, drawPixel(0, 0, _, _));
    EXPECT_CALL(sglMock, drawPixel(0, 1, _, _));
    EXPECT_CALL(sglMock, drawPixel(0, 2, _, _));
    EXPECT_CALL(sglMock, drawPixel(0, 3, _, _));
    EXPECT_CALL(sglMock, drawPixel(0, 4, _, _));
    EXPECT_CALL(sglMock, drawPixel(0, 5, _, _));
    sglMock.drawVerticalLine(0, 0, 5);
}

// #### RECTANGLE #### //

TEST(DRAWRECTANGLE, drawRectangle_1)
{
    ;
}


// #### TRIANGLE #### //

TEST(DRAWTRIANGLW, drawTriangle_1)
{
    ;
}

// #### CIRCLE #### //

TEST(DRAWCIRCLE, drawCircle_1)
{
    ;
}