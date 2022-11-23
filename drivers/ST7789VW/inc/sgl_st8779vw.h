#include "sgl.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

// waveshare lcd for RPI PICO 1.14 INCH AND 1.3 INCH
//  VSYS            Power Input
//  GND             GND
//  DIN     GP11    MOSI pin of SPI, slave device data input
//  CLK     GP10    SCK pin of SPI, clock pin
//  CS      GP9     Chip selection of SPI, low active
//  DC      GP8     Data/Command control pin (High for data; Low for command)
//  RST     GP12    Reset pin, low active
//  BL      GP13    Backlight control
//  A       GP15    User button A
//  B       GP17    User button B
//  UP      GP2     Joystick-up
//  DOWM    GP18    Joystick-down
//  LEFT    GP16    Joystick-left
//  RIGHT   GP20    Joystick-right
//  CTRL    GP3     Joystick-center

// waveshare lcd for RPI PICO 1.3 INCH
//  X       GP19    User button X
//  Y       GP21    User button Y

// LCD 1.14 INCH    X:240 Y:135
// LCD 1.3  INCH    X:240 Y:240

// frame buffer 12bit   16bit
//  resolution  kB      kB
//  135x240     48,6    64,8
//  240x240     86,4    115,2
//  240x320     115,2   153,6

#define ST77XX_NOP      0x00
#define ST77XX_SWRESET  0x01
#define ST77XX_RDDID    0x04
#define ST77XX_RDDST    0x09

#define ST77XX_SLPIN    0x10
#define ST77XX_SLPOUT   0x11
#define ST77XX_PTLON    0x12
#define ST77XX_NORON    0x13

#define ST77XX_INVOFF   0x20
#define ST77XX_INVON    0x21
#define ST77XX_DISPOFF  0x28
#define ST77XX_DISPON   0x29
#define ST77XX_CASET    0x2A
#define ST77XX_RASET    0x2B
#define ST77XX_RAMWR    0x2C
#define ST77XX_RAMRD    0x2E

#define ST77XX_PTLAR    0x30
#define ST77XX_TEOFF    0x34
#define ST77XX_TEON     0x35
#define ST77XX_MADCTL   0x36
#define ST77XX_COLMOD   0x3A

#define ST77XX_MADCTL_MY  0x80
#define ST77XX_MADCTL_MX  0x40
#define ST77XX_MADCTL_MV  0x20
#define ST77XX_MADCTL_ML  0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1    0xDA
#define ST77XX_RDID2    0xDB
#define ST77XX_RDID3    0xDC
#define ST77XX_RDID4    0xDD


namespace sgl
{
namespace st8779vw
{

  enum class ScanDir: uint8_t
  {
    Horizontal = 0x00,
    Vertical = 0x01
  };

class SGL_ST8779VW: public SGL
{
public:
    SGL_ST8779VW(uint16_t w, uint16_t h, uint MOSI, uint MISO, uint CLK, uint CS, uint DC, uint RST) : SGL(w, h), MOSI_(MOSI), MISO_(MISO), CLK_(CLK), CS_(CS), DC_(DC), RST_(RST) {}
    SGL_ST8779VW(uint16_t w, uint16_t h, uint MOSI, uint MISO, uint CLK, uint CS, uint DC, uint RST, uint BLK) : SGL(w, h), MOSI_(MOSI), MISO_(MISO), CLK_(CLK), CS_(CS), DC_(DC), RST_(RST), BLK_(BLK) {}
    SGL_ST8779VW(uint16_t w, uint16_t h, spi_inst_t* spi, uint CS, uint DC, uint RST) : SGL(w, h), spi_(spi), CS_(CS), DC_(DC), RST_(RST) {}
    SGL_ST8779VW(uint16_t w, uint16_t h, spi_inst_t* spi, uint CS, uint DC, uint RST, uint BLK) : SGL(w, h), spi_(spi), CS_(CS), DC_(DC), RST_(RST), BLK_(BLK) {}
    void drawPixel(uint16_t w, uint16_t h, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) override;
    void init(ScanDir dir = ScanDir::Horizontal);
    // backlight level, 0 means power off, 100 means power max, 1-99 by PWM Control
    //void setBackLight(uint8_t level);
    void reset();
    void drawScreen();
    void setActiveWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
protected:
    spi_inst_t* spi_ = nullptr;
    uint MOSI_  = 0;
    uint MISO_  = 0;
    uint CLK_   = 0;
    uint CS_    = 0;
    uint DC_    = 0;
    uint RST_   = 0;
    uint BLK_   = 0;
    void setPosition(ScanDir dir);
    void initReg();
    void sendCommand8(uint8_t command);
    void sendData8(uint8_t data);
    void sendData16(uint16_t data);
    //void startDataWrite();
    //void startCommandWrite();
    //void stopDataWrite();
    //void stopCommandWrite();
};

}
}
