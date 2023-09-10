#ifndef __SGL_HAL_MOCK__
#define __SGL_HAL_MOCK__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "sgl_hal.h"

class SglHalMock
{
public:
    MOCK_METHOD(void, sgl_send_data8_mock, (const uint8_t* data, const uint size));
    MOCK_METHOD(void, sgl_send_data16_mock, (const uint16_t* data, const uint size));
    MOCK_METHOD(void, sgl_send_command8_mock, (const uint8_t* data, const uint size));
    MOCK_METHOD(void, sgl_send_byte_mock, (const uint8_t data));
    MOCK_METHOD(void, sgl_gpio_write_mock, (const uint gpio_pin, const bool value));
    MOCK_METHOD(void, sgl_delay_ms_mock, (const uint delay_ms));
};

#endif // __SGL_HAL_MOCK__