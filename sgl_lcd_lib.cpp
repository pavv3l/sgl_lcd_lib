#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
//#include "sgl_st8779vw.h"
#include "sgl_ili9341.h"
#include "Arial12x12.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
/*
#define LCD_DIN     11
#define LCD_CLK     10
#define LCD_CS      9 
#define LCD_DC      8 
#define LCD_RST     12
#define LCD_BL      13
#define LCD_A       15
#define LCD_B       17
#define LCD_X       19
#define LCD_Y       21
#define LCD_UP      2
#define LCD_LEFT    16
#define LCD_RIGHT   20
#define LCD_CTRL    3

unsigned long counter;
bool led = false;
*/
//void init_buttons_1_14();
//void init_buttons_1_3();


#define LCD_DIN     11
#define LCD_CLK     10
#define LCD_DC      8 
#define LCD_CS      9 
#define LCD_RST     12

#define LCD_WIDTH 240
#define LCD_HEIGHT 320

static void sgl_send_data8_(const uint8_t* data, const uint size)
{
    spi_write_blocking(spi1, data, size);
}
static void sgl_send_data16(const uint16_t* data, const uint size)
{
    ;
}
static void sgl_send_command8(const uint8_t* data, const uint size)
{
    spi_write_blocking(spi1, data, size);
}
static void sgl_send_byte(const uint8_t data)
{
    spi_write_blocking(spi1, &data, 1);
}
static void sgl_gpio_write(const uint gpio_pin, const bool value)
{
    gpio_put(gpio_pin, value);
}
static void sgl_delay_ms(const uint delay_ms)
{
    sleep_ms(delay_ms);
}


void init_spi();


void core1_entry();

int main()
{
    stdio_init_all();

    init_spi();

    SGL_hal_interface lcdInterface
    {
        .sendData8 = sgl_send_data8_,
        .sendData16 = sgl_send_data16,
        .sendCommand8 = sgl_send_command8,
        .sendByte = sgl_send_byte,
        .gpioWrite = sgl_gpio_write,
        .delayMs = sgl_delay_ms
    };

    gpio_init(LCD_CS);
    gpio_set_dir(LCD_CS, GPIO_OUT);
    gpio_put(LCD_CS, 0);
    gpio_init(LCD_DC);
    gpio_set_dir(LCD_DC, GPIO_OUT);
    gpio_put(LCD_DC, 0);
    gpio_init(LCD_RST);
    gpio_set_dir(LCD_RST, GPIO_OUT);
    gpio_put(LCD_RST, 0);

    Arial12x12Font font12;

    sgl::ili9341::SGLILI9341 lcd(LCD_WIDTH, LCD_HEIGHT, &lcdInterface, LCD_DC, LCD_CS, LCD_RST);
    lcd.setFont(&font12);
    font12.color = ILI9341_DARKGREY;
    lcd.init();
    uint16_t color = ILI9341_WHITE;
    u_int32_t xx = 10;
    lcd.fill_screen(ILI9341_WHITE);
    while(true)
    {
        lcd.drawString("HELLO WORLD", 10, xx);
        sleep_ms(5000);
        color += 0x0011;
        xx += 50;
        if(xx > 310)
        {
            xx = 0;
        }

    }

    return 0;
}

/*
void init_buttons_1_14()
{
    gpio_init(LCD_A);
    gpio_init(LCD_B);
    gpio_set_dir(LCD_A, GPIO_IN);
    gpio_set_dir(LCD_B, GPIO_IN);
    gpio_pull_up(LCD_A);
    gpio_pull_up(LCD_B);
}
void init_buttons_1_3()
{
    gpio_init(LCD_A);
    gpio_init(LCD_B);
    gpio_init(LCD_X);
    gpio_init(LCD_Y);
    gpio_set_dir(LCD_A, GPIO_IN);
    gpio_set_dir(LCD_B, GPIO_IN);
    gpio_set_dir(LCD_X, GPIO_IN);
    gpio_set_dir(LCD_Y, GPIO_IN);
    gpio_pull_up(LCD_A);
    gpio_pull_up(LCD_B);
    gpio_pull_up(LCD_X);
    gpio_pull_up(LCD_Y);
}
*/

void init_spi()
{
    spi_init(spi1, 10*1000000);
    gpio_set_function(LCD_CLK, GPIO_FUNC_SPI);
    gpio_set_function(LCD_DIN, GPIO_FUNC_SPI);

    gpio_init(LCD_CS);
    gpio_set_dir(LCD_CS, GPIO_OUT);
    gpio_put(LCD_CS, 1);

    gpio_init(LCD_DC);
    gpio_set_dir(LCD_DC, GPIO_OUT);
    gpio_put(LCD_DC, 0);

    gpio_init(LCD_RST);
    gpio_set_dir(LCD_RST, GPIO_OUT);
    gpio_put(LCD_RST, 0);
}