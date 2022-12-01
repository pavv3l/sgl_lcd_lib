#include "sgl_st8779vw.h"

namespace sgl
{
namespace st8779vw
{

void SGL_ST8779VW::drawPixel(uint16_t x, uint16_t y, const uint16_t color, const Mode mode)
{
    buffer_[y * 240 + x] = color;
}

void SGL_ST8779VW::init(ScanDir dir)
{
    reset();
    setPosition(dir);
    initReg();
    fillScreen(WHITE);
}

void SGL_ST8779VW::setPosition(ScanDir dir)
{
    uint8_t madctl = 0;
    sendCommand8(ST77XX_MADCTL);
    switch(dir)
    {
        case(ScanDir::VERTICAL):
            madctl = ST77XX_MADCTL_MX;
            x_start_ = 0;
            y_start_ = 0;
            break;
        case(ScanDir::VERTICAL_REVERSED):
            madctl = ST77XX_MADCTL_MY;
            x_start_ = 0;
            y_start_ = 80;
            break;
        case(ScanDir::HORIZONTAL):
            madctl = ST77XX_MADCTL_MV;
            x_start_ = 0;
            y_start_ = 0;
            break;
        case(ScanDir::HORIZONTAL_REVERSED):
            break;
        case(ScanDir::VERTICAL_MIRROR_X):
            break;
        case(ScanDir::VERTICAL_REVERSED_MIRROR_X):
            madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY;
            x_start_ = 0;
            y_start_ = 80;
            break;
        case(ScanDir::HORIZONTAL_X_MIRROR_Y):
            break;
        case(ScanDir::VERTICAL_MIRROR_X_Y):
            break;
        default:
            break;
    }
    sendData8(madctl);
    //sendData8(0X0000); // dul przy klawiszach/ gora yoistick, (0,0) top left, odsw gora -> dol
    
    //madctl = ST77XX_MADCTL_MV; // lewa strona przy yoysticku, prawa przy klawiszach, odsw dół - góra (0,0) lewa dol
    //y_start_ = 0;
    //x_start_ = 0;

    //madctl = ST77XX_MADCTL_MX; // dol przy yoysticku, gora klawisze | (0,0) dol lewy | odswiezanie dol - gora
    //y_start_ = 80;
    //x_start_ = 80;

    //madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV; // dol przy yoysticku, gora klawisze | (0,0) dol prawy | odswiezanie dol - gora
    //y_start_ = 80;
    //x_start_ = 80;

    //madctl = ST77XX_MADCTL_MY  | ST77XX_MADCTL_MV; // dol przy yoysticku, gora klawisze | (0,0) dol prawy | odswiezanie dol - gora
    //y_start_ = 80;
    //x_start_ = 80;

    //madctl = ST77XX_MADCTL_MY; // dol przy yoysticku, gora klawisze | (0,0) dol prawy | odswiezanie dol - gora
    //y_start_ = 80;
    //x_start_ = 80;
  /*
    if(dir == ScanDir::Horizontal)
    {
        //x_start_=40;
        //y_start_=53;
        x_start_ = 00;
        sendCommand8(ST77XX_MADCTL);
        sendData8(0X70);
    }
    else
    {
        //x_start_=52; y_start_=40;
        //std::swap(width_, height_);
        sendCommand8(ST77XX_MADCTL);
        sendData8(0X00);
    }
    */
}

void SGL_ST8779VW::initReg()
{
    sendCommand8(ST77XX_COLMOD);
    sendData8(0x05);// for 16 bit, 65k colors RGB 565
    // 0x03 // for 12 bit, 4k color RGB 444
    // 0x06 // for 18 bit, 262 color RGB 666

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
    gpio_put(CS_, 1);
}
void SGL_ST8779VW::sendData16(uint16_t data)
{
    gpio_put(DC_, 1);
    gpio_put(CS_, 0);
    
    uint8_t data1, data2;
    data1 = (data >> 8) & 0xFF;
    data2 = data & 0xFF;
    spi_write_blocking(spi_, &data1, 1);
    spi_write_blocking(spi_, &data2, 1);
    
   //spi_write16_blocking(spi_, &data, 1);
    gpio_put(CS_, 1);
}

void SGL_ST8779VW::drawScreen()
{
  setActiveWindow(0, 0, width_ - 1, height_ - 1);
    gpio_put(DC_, 1);
    gpio_put(CS_, 0);
    uint8_t* ptr = (uint8_t*)buffer_;
    for(int i = 0; i < height_; ++i)
    {
      spi_write_blocking(spi_, ptr, width_ * 2);
      ptr += width_ * 2;
    }
    gpio_put(CS_, 1);
    sendCommand8(0x29);
}

void SGL_ST8779VW::setActiveWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    x0 += x_start_;
    x1 += x_start_;
    y0 += y_start_;
    y1 += y_start_;
    sendCommand8(ST77XX_CASET);
    sendData16(x0);
    sendData16(x1);
    sendCommand8(ST77XX_RASET);
    sendData16(y0);
    sendData16(y1);
    sendCommand8(ST77XX_RAMWR);
}

void SGL_ST8779VW::fillScreen(uint16_t color)
{
  for(int i = 0; i < 240 * 240; ++i)
  {
      buffer_[i] = color;
  }
}

/**************************************************************************/
/*!
    @brief  Set origin of (0,0) of display with offsets
    @param  col  The offset from 0 for the column address
    @param  row  The offset from 0 for the row address
*/
/**************************************************************************/
void SGL_ST8779VW::setColRowStart(int8_t col, int8_t row) {
  colstart_ = col;
  rowstart_ = row;
}

/**************************************************************************/
/*!
 @brief  Change whether display is on or off
 @param  enable True if you want the display ON, false OFF
 */
/**************************************************************************/
void SGL_ST8779VW::enableDisplay(bool enable) {
  sendCommand8(enable ? ST77XX_DISPON : ST77XX_DISPOFF);
}

/**************************************************************************/
/*!
 @brief  Change whether TE pin output is on or off
 @param  enable True if you want the TE pin ON, false OFF
 */
/**************************************************************************/
void SGL_ST8779VW::enableTearing(bool enable) {
  sendCommand8(enable ? ST77XX_TEON : ST77XX_TEOFF);
}

/**************************************************************************/
/*!
 @brief  Change whether sleep mode is on or off
 @param  enable True if you want sleep mode ON, false OFF
 */
/**************************************************************************/
void SGL_ST8779VW::enableSleep(bool enable) {
  sendCommand8(enable ? ST77XX_SLPIN : ST77XX_SLPOUT);
}

void SGL_ST8779VW::setRotation(uint8_t rot)
{
  uint8_t madctl = 0;

  rot = rot & 0x03; // can't be higher than 3
  rotation_ = rot;

  switch (rotation_)
  {
  case 0:
    madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_RGB;
    //x_start_ = colstart_;
    //y_start_ = rowstart_;
    //width_ = windowWidth;
    //height_ = windowHeight;
    break;
  case 1:
    madctl = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
    //x_start_ = rowstart_;
    //y_start_ = colstart_2_;
    //height_ = windowWidth;
    //width_ = windowHeight;
    break;
  case 2:
    madctl = ST77XX_MADCTL_RGB;
    //x_start_ = colstart_2_;
    //y_start_ = rowstart_2_;
    //width_ = windowWidth;
    //height_ = windowHeight;
    break;
  case 3:
    madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
    //x_start_ = rowstart_2_;
    //y_start_ = colstart_;
    //height_ = windowWidth;
    //width_ = windowHeight;
    break;
  default:
    break;
  }

  sendCommand8(ST77XX_MADCTL);
  sendData8(madctl);
}

}
}