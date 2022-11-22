#include "sgl_st8779vw.h"

namespace sgl
{
namespace st8779vw
{

void SGL_ST8779VW::drawPixel(uint16_t x, uint16_t y, const uint16_t color, const Mode mode)
{
    ;
}

void SGL_ST8779VW::init(ScanDir dir)
{
    reset();
    setPosition(dir);
    initReg();
}

void SGL_ST8779VW::setPosition(ScanDir dir)
{
    if(dir == ScanDir::Horizontal)
    {
        sendCommand8(ST77XX_MADCTL)
        sendData8(0X70);
    }
    else
    {
        std::swap(width_, height_);
        sendCommand8(ST77XX_MADCTL)
        sendData8(0X00);
    }
}

void SGL_ST8779VW::initReg()
{
    sendCommand8(0x3A);
    sendData8(0x05);

    sendCommand8(0xB2);
    sendData8(0x0C);
    sendData8(0x0C);
    sendData8(0x00);
    sendData8(0x33);
    sendData8(0x33);

    sendCommand8(0xB7);  //Gate Control
    sendData8(0x35);

    sendCommand8(0xBB);  //VCOM Setting
    sendData8(0x19);

    sendCommand8(0xC0); //LCM Control     
    sendData8(0x2C);

    sendCommand8(0xC2);  //VDV and VRH Command Enable
    sendData8(0x01);
    sendCommand8(0xC3);  //VRH Set
    sendData8(0x12);
    sendCommand8(0xC4);  //VDV Set
    sendData8(0x20);

    sendCommand8(0xC6);  //Frame Rate Control in Normal Mode
    sendData8(0x0F);
    
    sendCommand8(0xD0);  // Power Control 1
    sendData8(0xA4);
    sendData8(0xA1);

    sendCommand8(0xE0);  //Positive Voltage Gamma Control
    sendData8(0xD0);
    sendData8(0x04);
    sendData8(0x0D);
    sendData8(0x11);
    sendData8(0x13);
    sendData8(0x2B);
    sendData8(0x3F);
    sendData8(0x54);
    sendData8(0x4C);
    sendData8(0x18);
    sendData8(0x0D);
    sendData8(0x0B);
    sendData8(0x1F);
    sendData8(0x23);

    sendCommand8(0xE1);  //Negative Voltage Gamma Control
    sendData8(0xD0);
    sendData8(0x04);
    sendData8(0x0C);
    sendData8(0x11);
    sendData8(0x13);
    sendData8(0x2C);
    sendData8(0x3F);
    sendData8(0x44);
    sendData8(0x51);
    sendData8(0x2F);
    sendData8(0x1F);
    sendData8(0x1F);
    sendData8(0x20);
    sendData8(0x23);

    sendCommand8(0x21);  //Display Inversion On

    sendCommand8(0x11);  //Sleep Out

    sendCommand8(0x29);  //Display On
}

void SGL_ST8779VW::reset()
{
    gpio_put(RST_, 1);
    sleep_ms(100);
    gpio_put(RST_, 0);
    sleep_ms(100);
    gpio_put(RST_, 1);
    sleep_ms(100);
}

void SGL_ST8779VW::sendCommand8(uint8_t command)
{
    gpio_put(DC_, 0);
    gpio_put(CS_, 0);
    spi_write_blocking(spi_, &command, 1);
    gpio_put(CS_, 1);
}

void SGL_ST8779VW::sendData8(uint8_t data)
{
    gpio_put(DC_, 1);
    gpio_put(CS_, 0);
    spi_write_blocking(spi_, &data, 1);
    pio_put(CS_, 1);
}
void SGL_ST8779VW::sendData16(uint16_t data)
{
    gpio_put(DC_, 1);
    gpio_put(CS_, 0);
    spi_write_blocking(spi_, &((data >> 8) & 0xFF), 1);
    spi_write_blocking(spi_, &(data & 0xFF), 1);
    pio_put(CS_, 1);
}

}
}