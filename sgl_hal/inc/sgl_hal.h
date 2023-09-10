#ifndef __SGL_HAL_H__
#define __SGL_HAL_H__

#include <cstdint>

//using uint = uint32_t;

typedef void (*sgl_send_data8_fptr_t) (const uint8_t* data, const uint size);
typedef void (*sgl_send_data16_fptr_t) (const uint16_t* data, const uint size);
typedef void (*sgl_send_command8_fptr_t) (const uint8_t* data, const uint size);
typedef void (*sgl_send_byte_fptr_t) (const uint8_t data);
typedef void (*sgl_gpio_write_fptr_t) (const uint gpio_pin, const bool value);
typedef void (*sgl_delay_ms_fptr_t) (const uint delay_ms);

struct SGL_hal_interface
{
      sgl_send_data8_fptr_t sendData8 = nullptr;
      sgl_send_data16_fptr_t sendData16 = nullptr;
      sgl_send_command8_fptr_t sendCommand8 = nullptr;
      sgl_send_byte_fptr_t sendByte = nullptr;
      sgl_gpio_write_fptr_t gpioWrite = nullptr;
      sgl_delay_ms_fptr_t delayMs = nullptr;
};

#endif // __SGL_HAL_H__