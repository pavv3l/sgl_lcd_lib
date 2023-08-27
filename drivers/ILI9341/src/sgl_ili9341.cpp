#include "sgl_ili9341.h"

namespace sgl
{
namespace ili9341
{


SGLILI9341::SGLILI9341(uint16_t w, uint16_t h, SGL_hal_interface* deviceInterface, PinName DC, PinName CE, PinName RST)
    : SGL(w, h, deviceInterface), dev(deviceInterface), DC_(DC), CE_(CE), RST_(RST)
{
    if(dev != nullptr)
    {
        dev->gpioWrite(DC_, 1);
        dev->gpioWrite(CE_, 0);
        dev->gpioWrite(RST_, 1);
    }
}

void SGLILI9341::init()
{
    reset();
}
/*
void SGLILI9341::send_data(uint16_t data)
{
    dev->gpioWrite(DC_, 1); // stan na high dla przesylania danych
    dev->sendData8(data >> 8);
    dev->sendData8(data&0xff);
}
*/
void SGLILI9341::send_data16(uint16_t data)
{
    
    dev->gpioWrite(DC_, 1);
    //ce.write(0);
    dev->sendByte(data >> 8);
    dev->sendByte(data & 0xFF);
    //ce.write(1);
}

void SGLILI9341::send_command(uint8_t cmd)
{
    dev->gpioWrite(DC_, 0); // ustalamy na low w //celu przeslania komendy
    //ce.write(0);
    dev->sendByte(cmd);
    //ce.write(1);
}

void SGLILI9341::send_command_parameter(uint8_t param)
{
    dev->gpioWrite(DC_, 1);
    //ce.write(0);
    dev->sendByte(param);
    //ce.write(1);
}

void SGLILI9341::drawPixel(uint16_t x, uint16_t y, uint16_t color, Mode mode)
{
    if (x >= width_ || y >= height_)
    {
        return;
    }
    set_active_window(x, y, x, y);

    send_command(ILI9341_RAMWR);
    send_data16(color);
}

void SGLILI9341::set_active_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    send_command(ILI9341_CASET); // column address set
    send_data16(x0);
    send_data16(x1);

    send_command(ILI9341_PASET);
    send_data16(y0);
    send_data16(y1);

    send_command(ILI9341_RAMWR);
}

void SGLILI9341::fill_screen(uint16_t color)
{
    for(int i = 0; i < 240; ++i)
    {
        for(int j = 0; j < 320; ++j)
        {
            drawPixel(i, j, color);
        }
    }
}

void SGLILI9341::fill_screen2(uint16_t color)
{
    set_active_window(0, 0, 239, 319);
    for(int i = 0; i < 240*320; ++i)
    {
        send_data16(color);
    }
}
/*
void SGLILI9341::draw_horizontal_line(uint16_t x, uint16_t y, int16_t len, uint16_t color, SGL::Mode mode)
{
    if(len == 0) return;
    if(x >= _width)
        x = _width - 1;
    if(y >= _height)
        y = _height - 1;
    int16_t x1 = x + len;
    if(x1 >= _width) x1 = _width - 1;
    if(x1 < 0) x1 = 0;
    if(x1 < x)
    {
        SWAPUINT16(x, x1);
        set_active_window(x, y, x1, y);
        len--;
        dev->gpioWrite(DC_, 1);
        while(len++)
            dev->sendData8(color);
    }
    else
    {
        set_active_window(x, y, x1, y);
        len++;
        dev->gpioWrite(DC_, 1);
        while(len--)
            dev->sendData8(color);
    }
}
*/
/*
void SGLILI9341::draw_vertical_line(uint16_t x, uint16_t y, int16_t len, uint16_t color, SGL::Mode mode)
{
    if(len == 0) return;
    if(x >= _width) x = _width - 1;
    if(y >= _height) y = _height - 1;
    int16_t y1 = y + len;
    if(y1 >= _height) y1 = _height - 1;
    if(y1 < 0) y1 = 0;
    if(y1 < y)
    {
        SWAPUINT16(y, y1);
        set_active_window(x, y, x, y1);
        len--;
        dev->gpioWrite(DC_, 1);
        while(len++)
            dev->sendData8(color);
    }
    else
    {
        set_active_window(x, y, x, y1);
        len++;
        dev->gpioWrite(DC_, 1);
        while(len--)
            dev->sendData8(color);
    }
}
*/

void SGLILI9341::setRotation(uint8_t rot)
{
    ;
}

void SGLILI9341::invertDisplay(bool invert)
{
    send_command(invert ? ILI9341_INVON : ILI9341_INVOFF);
}

void SGLILI9341::scrollTo(uint16_t h)
{
    send_command(ILI9341_VSCRSADD);
    send_data16(h);
}

void SGLILI9341::setScrollMargins(uint16_t top, uint16_t bottom)
{
    ;
}

void SGLILI9341::reset()
{
    dev->gpioWrite(DC_, 1);
    dev->gpioWrite(RST_, 0);
    dev->delayMs(1);
    dev->gpioWrite(RST_, 1); // end hardware reset
    dev->delayMs(5);
    send_command(0x01); // SW reset
    dev->delayMs(5);
    send_command(0x28); // display off
    /* Start Initial Sequen//ce ----------------------------------------------------*/
    send_command(0xCF);
    send_command_parameter(0x00);
    send_command_parameter(0x83);
    send_command_parameter(0x30);

    send_command(0xED);
    send_command_parameter(0x64);
    send_command_parameter(0x03);
    send_command_parameter(0x12);
    send_command_parameter(0x81);

    send_command(0xE8);
    send_command_parameter(0x85);
    send_command_parameter(0x01);
    send_command_parameter(0x79);

    send_command(0xCB);
    send_command_parameter(0x39);
    send_command_parameter(0x2C);
    send_command_parameter(0x00);
    send_command_parameter(0x34);
    send_command_parameter(0x02);

    send_command(0xF7);
    send_command_parameter(0x20);

    send_command(0xEA);
    send_command_parameter(0x00);
    send_command_parameter(0x00);


    send_command(0xC0); // POWER_CONTROL_1
    send_command_parameter(0x26);

    send_command(0xC1); // POWER_CONTROL_2
    send_command_parameter(0x11);

    send_command(0xC5); // VCOM_CONTROL_1
    send_command_parameter(0x35);
    send_command_parameter(0x3E);

    send_command(0xC7); // VCOM_CONTROL_2
    send_command_parameter(0xBE);

    send_command(0x36); // MEMORY_AC//ceSS_CONTROL
    send_command_parameter(0x48);

    send_command(0x3A); // COLMOD_PIXEL_FORMAT_SET
    send_command_parameter(0x55);    // 16 bit pixel

    send_command(0xB1); // Frame Rate
    send_command_parameter(0x00);
    send_command_parameter(0x1B);

    send_command(0xF2); // Gamma Function Disable
    send_command_parameter(0x08);

    send_command(0x26);
    send_command_parameter(0x01); // gamma set for curve 01/2/04/08

    send_command(0xE0); // positive gamma correction
    send_command_parameter(0x1F);
    send_command_parameter(0x1A);
    send_command_parameter(0x18);
    send_command_parameter(0x0A);
    send_command_parameter(0x0F);
    send_command_parameter(0x06);
    send_command_parameter(0x45);
    send_command_parameter(0x87);
    send_command_parameter(0x32);
    send_command_parameter(0x0A);
    send_command_parameter(0x07);
    send_command_parameter(0x02);
    send_command_parameter(0x07);
    send_command_parameter(0x05);
    send_command_parameter(0x00);

    send_command(0xE1); // negativ gamma correction
    send_command_parameter(0x00);
    send_command_parameter(0x25);
    send_command_parameter(0x27);
    send_command_parameter(0x05);
    send_command_parameter(0x10);
    send_command_parameter(0x09);
    send_command_parameter(0x3A);
    send_command_parameter(0x78);
    send_command_parameter(0x4D);
    send_command_parameter(0x05);
    send_command_parameter(0x18);
    send_command_parameter(0x0D);
    send_command_parameter(0x38);
    send_command_parameter(0x3A);
    send_command_parameter(0x1F);

    send_command(0xB7); // entry mode
    send_command_parameter(0x07);

    send_command(0xB6); // display function control
    send_command_parameter(0x0A);
    send_command_parameter(0x82);
    send_command_parameter(0x27);
    send_command_parameter(0x00);

    send_command(0x11); // sleep out

    dev->delayMs(100);

    send_command(0x29); // display on

    dev->delayMs(100);
}

void SGLILI9341::reset2()
{
    dev->gpioWrite(RST_, 1);
    dev->delayMs(1);
    dev->gpioWrite(RST_, 0);
    dev->delayMs(1);
    dev->gpioWrite(RST_, 1);

    send_command(0xC0);
    send_command_parameter(0x19);
    send_command_parameter(0x1a);
    
    send_command(0xC1);
    send_command_parameter(0x45);
    send_command_parameter(0x00);

    send_command(0xC2);
    send_command_parameter(0x33);

    send_command(0xC5);
    send_command_parameter(0x00);
    send_command_parameter(0x28);
    
    send_command(0xB1);
    send_command_parameter(0xA0);
    send_command_parameter(0x11);

    send_command(0xB4);
    send_command_parameter(0x02);

//
//			lcdWriteReg(0xB6);                  //  Display Control Function      
//			lcdWriteData(0x00);
//			lcdWriteDataContinue(0x42);
//			lcdWriteDataContinue(0x3B);
//
//			lcdWriteReg(0xE0);                  //  Positive Gamma control
//			lcdWriteData(0x1F);
//			lcdWriteDataContinue(0x25);
//			lcdWriteDataContinue(0x22);
//			lcdWriteDataContinue(0x0B);
//			lcdWriteDataContinue(0x06);
//			lcdWriteDataContinue(0x0A);
//			lcdWriteDataContinue(0x4E);
//			lcdWriteDataContinue(0xC6);
//			lcdWriteDataContinue(0x39);
//			lcdWriteDataContinue(0x00);
//			lcdWriteDataContinue(0x00);
//			lcdWriteDataContinue(0x00);
//			lcdWriteDataContinue(0x00);
//			lcdWriteDataContinue(0x00);
//			lcdWriteDataContinue(0x00);
//
//			lcdWriteReg(0XE1);                  //  Negative Gamma control
//			lcdWriteData(0x1F);
//			lcdWriteDataContinue(0x3F);
//			lcdWriteDataContinue(0x3F);
//			lcdWriteDataContinue(0x0F);
//			lcdWriteDataContinue(0x1F);
//			lcdWriteDataContinue(0x0F);
//			lcdWriteDataContinue(0x46);
//			lcdWriteDataContinue(0x49);
//			lcdWriteDataContinue(0x31);
//			lcdWriteDataContinue(0x05);
//			lcdWriteDataContinue(0x09);
//			lcdWriteDataContinue(0x03);
//			lcdWriteDataContinue(0x1C);
//			lcdWriteDataContinue(0x1A);
//			lcdWriteDataContinue(0x00);
//
//			//  From original driver, but register numbers don't make any sense.
//			if (0)
//			{
//				lcdWriteReg(0XF1);
//				lcdWriteData(0x36);
//				lcdWriteDataContinue(0x04);
//				lcdWriteDataContinue(0x00);
//				lcdWriteDataContinue(0x3C);
//				lcdWriteDataContinue(0x0F);
//				lcdWriteDataContinue(0x0F);
//				lcdWriteDataContinue(0xA4);
//				lcdWriteDataContinue(0x02);
//
//				lcdWriteReg(0XF2);
//				lcdWriteData(0x18);
//				lcdWriteDataContinue(0xA3);
//				lcdWriteDataContinue(0x12);
//				lcdWriteDataContinue(0x02);
//				lcdWriteDataContinue(0x32);
//				lcdWriteDataContinue(0x12);
//				lcdWriteDataContinue(0xFF);
//				lcdWriteDataContinue(0x32);
//				lcdWriteDataContinue(0x00);
//
//				lcdWriteReg(0XF4);
//				lcdWriteData(0x40);
//				lcdWriteDataContinue(0x00);
//				lcdWriteDataContinue(0x08);
//				lcdWriteDataContinue(0x91);
//				lcdWriteDataContinue(0x04);
//
//				lcdWriteReg(0XF8);
//				lcdWriteData(0x21);
//				lcdWriteDataContinue(0x04);
//			}
//
//			lcdWriteCommand(0x3A, 0x55);
//
//			//  Set initial rotation to match AFX defaults - tall / narrow
//			lcdWriteCommand(0xB6, 0x00, 0x22);
//			lcdWriteCommand(0x36, 0x08);
//
//			lcdWriteReg(0x11); // Sleep out
//
//			//  Fill screen to black
//			writeFillRect2(0, 0, LCD_WIDTH, LCD_HEIGHT, 0x0000);
//
//			lcdWriteReg(0x29);  // Turn on display
//		}
//		endWrite();
//	}
//
}

void SGLILI9341::drawBitmap16(uint16_t* bitmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    if(x >= width_)
        x = width_ - 1;
    if(y >= height_)
        y = height_ - 1;
    if((x + width) >= width_)
        width = width_ - x - 1;
    if((y + height) >= height_)
        height = height_ - y - 1;

    //dev->sendData816(bitmap, width*height);
    // OR better
    dev->sendData8((unsigned char*)bitmap, sizeof(*bitmap)* width* height);
}

void SGLILI9341::drawScreen()
{
    set_active_window(0, 0, 239, 319);
    for(uint i = 0; i < bufferSize; ++i)
    {
        send_data16(buffer_[i]);
    }
}

} // namespace ili9341
} // namespace sgl
