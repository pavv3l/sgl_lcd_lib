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
//  B	    GP17    User button B
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

/*
void LCD_1IN14_Init(UBYTE Scan_dir)
{
    DEV_SET_PWM(90);
    //Hardware reset
    LCD_1IN14_Reset();

    //Set the resolution and scanning method of the screen
    LCD_1IN14_SetAttributes(Scan_dir);
    
    //Set the initialization register
    LCD_1IN14_InitReg();
}

static void LCD_1IN14_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(100);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(100);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(100);
}

static void LCD_1IN14_SetAttributes(UBYTE Scan_dir)
{
    //Get the screen scan direction
    LCD_1IN14.SCAN_DIR = Scan_dir;
    UBYTE MemoryAccessReg = 0x00;

    //Get GRAM and LCD width and height
    if(Scan_dir == HORIZONTAL) {
        LCD_1IN14.HEIGHT	= LCD_1IN14_WIDTH;
        LCD_1IN14.WIDTH   = LCD_1IN14_HEIGHT;
        MemoryAccessReg = 0X70;
    } else {
        LCD_1IN14.HEIGHT	= LCD_1IN14_HEIGHT;       
        LCD_1IN14.WIDTH   = LCD_1IN14_WIDTH;
        MemoryAccessReg = 0X00;
    }

    // Set the read / write scan direction of the frame memory
    LCD_1IN14_SendCommand(0x36); //MX, MY, RGB mode
    LCD_1IN14_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB
}

    // Set the read / write scan direction of the frame memory
    LCD_1IN14_SendCommand(0x36); //MX, MY, RGB mode
    LCD_1IN14_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB

    static void LCD_1IN14_InitReg(void)
{
    LCD_1IN14_SendCommand(0x3A);
    LCD_1IN14_SendData_8Bit(0x05);

    LCD_1IN14_SendCommand(0xB2);
    LCD_1IN14_SendData_8Bit(0x0C);
    LCD_1IN14_SendData_8Bit(0x0C);
    LCD_1IN14_SendData_8Bit(0x00);
    LCD_1IN14_SendData_8Bit(0x33);
    LCD_1IN14_SendData_8Bit(0x33);

    LCD_1IN14_SendCommand(0xB7);  //Gate Control
    LCD_1IN14_SendData_8Bit(0x35);

    LCD_1IN14_SendCommand(0xBB);  //VCOM Setting
    LCD_1IN14_SendData_8Bit(0x19);

    LCD_1IN14_SendCommand(0xC0); //LCM Control     
    LCD_1IN14_SendData_8Bit(0x2C);

    LCD_1IN14_SendCommand(0xC2);  //VDV and VRH Command Enable
    LCD_1IN14_SendData_8Bit(0x01);
    LCD_1IN14_SendCommand(0xC3);  //VRH Set
    LCD_1IN14_SendData_8Bit(0x12);
    LCD_1IN14_SendCommand(0xC4);  //VDV Set
    LCD_1IN14_SendData_8Bit(0x20);

    LCD_1IN14_SendCommand(0xC6);  //Frame Rate Control in Normal Mode
    LCD_1IN14_SendData_8Bit(0x0F);
    
    LCD_1IN14_SendCommand(0xD0);  // Power Control 1
    LCD_1IN14_SendData_8Bit(0xA4);
    LCD_1IN14_SendData_8Bit(0xA1);

    LCD_1IN14_SendCommand(0xE0);  //Positive Voltage Gamma Control
    LCD_1IN14_SendData_8Bit(0xD0);
    LCD_1IN14_SendData_8Bit(0x04);
    LCD_1IN14_SendData_8Bit(0x0D);
    LCD_1IN14_SendData_8Bit(0x11);
    LCD_1IN14_SendData_8Bit(0x13);
    LCD_1IN14_SendData_8Bit(0x2B);
    LCD_1IN14_SendData_8Bit(0x3F);
    LCD_1IN14_SendData_8Bit(0x54);
    LCD_1IN14_SendData_8Bit(0x4C);
    LCD_1IN14_SendData_8Bit(0x18);
    LCD_1IN14_SendData_8Bit(0x0D);
    LCD_1IN14_SendData_8Bit(0x0B);
    LCD_1IN14_SendData_8Bit(0x1F);
    LCD_1IN14_SendData_8Bit(0x23);

    LCD_1IN14_SendCommand(0xE1);  //Negative Voltage Gamma Control
    LCD_1IN14_SendData_8Bit(0xD0);
    LCD_1IN14_SendData_8Bit(0x04);
    LCD_1IN14_SendData_8Bit(0x0C);
    LCD_1IN14_SendData_8Bit(0x11);
    LCD_1IN14_SendData_8Bit(0x13);
    LCD_1IN14_SendData_8Bit(0x2C);
    LCD_1IN14_SendData_8Bit(0x3F);
    LCD_1IN14_SendData_8Bit(0x44);
    LCD_1IN14_SendData_8Bit(0x51);
    LCD_1IN14_SendData_8Bit(0x2F);
    LCD_1IN14_SendData_8Bit(0x1F);
    LCD_1IN14_SendData_8Bit(0x1F);
    LCD_1IN14_SendData_8Bit(0x20);
    LCD_1IN14_SendData_8Bit(0x23);

    LCD_1IN14_SendCommand(0x21);  //Display Inversion On

    LCD_1IN14_SendCommand(0x11);  //Sleep Out

    LCD_1IN14_SendCommand(0x29);  //Display On
}
// procedura init z innej biblioteki
{
    ST77XX_SWRESET,   ST_CMD_DELAY, //  1: Software reset, no args, w/delay
      150,                          //     ~150 ms delay
    ST77XX_SLPOUT ,   ST_CMD_DELAY, //  2: Out of sleep mode, no args, w/delay
      10,                          //      10 ms delay
    ST77XX_COLMOD , 1+ST_CMD_DELAY, //  3: Set color mode, 1 arg + delay:
      0x55,                         //     16-bit color
      10,                           //     10 ms delay
    ST77XX_MADCTL , 1,              //  4: Mem access ctrl (directions), 1 arg:
      0x08,                         //     Row/col addr, bottom-top refresh
    ST77XX_CASET  , 4,              //  5: Column addr set, 4 args, no delay:
      0x00,
      0,        //     XSTART = 0
      0,
      240,  //     XEND = 240
    ST77XX_RASET  , 4,              //  6: Row addr set, 4 args, no delay:
      0x00,
      0,             //     YSTART = 0
      320>>8,
      320&0xFF,  //     YEND = 320
    ST77XX_INVON  ,   ST_CMD_DELAY,  //  7: hack
      10,
    ST77XX_NORON  ,   ST_CMD_DELAY, //  8: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ST77XX_DISPON ,   ST_CMD_DELAY, //  9: Main screen turn on, no args, delay
      10 };  
#define ST_CMD_DELAY 0x80 // special signifier for command lists

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
*/

namespace sgl
{
namespace st8779vw
{

class SGL_ST8779VW: public SGL
{
public:
    SGL_ST8779VW(uint16_t x, uint16_t y, uint MOSI, uint MISO, uint CLK, uint CS, uint DC, uint RST) : SGL(x, y), MOSI_(MOSI), MISO_(MISO), CLK_(CLK), CS_(CS), DC_(DC), RST_(RST) {}
    SGL_ST8779VW(uint16_t x, uint16_t y, uint MOSI, uint MISO, uint CLK, uint CS, uint DC, uint RST, uint BLK) : SGL(x, y), MOSI_(MOSI), MISO_(MISO), CLK_(CLK), CS_(CS), DC_(DC), RST_(RST), BLK_(BLK) {}
    SGL_ST8779VW(uint16_t x, uint16_t y, spi_inst_t* spi, uint CS, uint DC, uint RST) : SGL(x, y), spi_(spi), CS_(CS), DC_(DC), RST_(RST) {}
    SGL_ST8779VW(uint16_t x, uint16_t y, spi_inst_t* spi, uint CS, uint DC, uint RST, uint BLK) : SGL(x, y), spi_(spi), CS_(CS), DC_(DC), RST_(RST), BLK_(BLK) {}
    void drawPixel(uint16_t x, uint16_t y, const uint16_t color = WHITE, const Mode mode = Mode::pixelAND) override;
    void init();
    // backlight level, 0 means power off, 100 means power max, 1-99 by PWM Control
    //void setBackLight(uint8_t level);
    //void reset();
protected:
    spi_inst_t* spi_ = nullptr;
    uint MOSI_  = 0;
    uint MISO_  = 0;
    uint CLK_   = 0;
    uint CS_    = 0;
    uint DC_    = 0;
    uint RST_   = 0;
    uint BLK_   = 0;
    //void sendCommand(uint8_t command);
    //void sendData_8bit(uint8_t data);
    //void sendData_16bit(uint16_t data);
    //void startDataWrite();
    //void startCommandWrite();
    //void stopDataWrite();
    //void stopCommandWrite();
};

}
}
