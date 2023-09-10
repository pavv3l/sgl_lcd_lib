#ifndef __SGL_DRAW_PIXEL_MOCK__
#define __SGL_DRAW_PIXEL_MOCK__

#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using namespace ::testing;
using namespace ::sgl;

class DrawPixelMock
{
public:
    MOCK_METHOD(void, drawPixelMock, (uint16_t x, uint16_t y, const uint16_t color, Mode mode));
};

#endif // __SGL_DRAW_PIXEL_MOCK__