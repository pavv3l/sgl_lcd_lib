#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "sgl_st8779vw.h"
#include "time.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments

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

void init_buttons_1_14();
void init_buttons_1_3();
void init_spi();

bool timer_callback(repeating_timer_t *rt);

void core1_entry();

int main()
{
    counter = 0;

    stdio_init_all();

    init_spi();
    init_buttons_1_3();

    gpio_init(LCD_BL);
    gpio_set_dir(LCD_BL, GPIO_OUT);
    gpio_put(LCD_BL, 1);

    sgl::st8779vw::SGL_ST8779VW lcd(240, 240, spi1, LCD_CS, LCD_DC, LCD_RST);
    lcd.init(sgl::st8779vw::ScanDir::VERTICAL);
    uint16_t col = RED;
    //repeating_timer_t timer;
    //add_repeating_timer_ms(500,timer_callback, NULL, &timer );
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    lcd.fillScreen(MAGENTA);
    lcd.drawScreen();

    //multicore_launch_core1(core1_entry);

    while(true)
    {
        lcd.fillScreen(BLUE);
        gpio_put(25, 1);
        lcd.drawTriangle(1,1, 20, 30, 50,20, col, sgl::Fill::solid);
        lcd.drawCircle(150,150,100,col,sgl::Fill::hole);
        lcd.drawRectangle(200,50,120,120,col,sgl::Fill::solid);
        lcd.drawScreen();
        col += 6243;
        gpio_put(25, 0);
        sleep_ms(2000);
    }

    return 0;
}

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

void init_spi()
{
    spi_init(spi1, 200*1000);
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

bool timer_callback(repeating_timer_t *rt)
{
    ;
}

void core1_entry()
{
    ;
}