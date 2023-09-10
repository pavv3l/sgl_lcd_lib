#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "sglDrawPixelMock.h"
#include "sglHalMock.h"
#include<vector>
#include <vector>
#include <memory>
#include <string.h>

using namespace sgl;
using namespace ::testing;

class SGL_TEST_F: public Test, SGL
{
    public:SGL_TEST_F(): SGL(height, width, &sgl_hal) {}

protected:
    void SetUp() override
    {
        ;
    }
    void TearDown() override
    {
        ;
    }
    DrawPixelMock drawpix;
    SGL sgl;
    SGL_hal_interface sgl_hal;
    const uint16_t height = 200;
    const uint16_t width = 100;


public:
    void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, Mode mode = Mode::pixelAND)
    {
        drawpix.drawPixelMock(x, y, color, mode);
    }
};

TEST(dummy1, dummy2)
{
    EXPECT_TRUE(1);
}