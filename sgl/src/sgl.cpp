#include "sgl.h"


namespace sgl
{

void SGL::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t color, const Mode mode)
{
#ifdef CHECK_LINE_PARAMETRS
    if(x0 >= width_)
        x0 = width_ - 1;
    if(x1 >= width_)
        x1 = width_ - 1;
    if(y0 >= height_)
        y0 = height_ - 1;
    if(y1 >= height_)
        y1 = height_ - 1;
#endif

    uint16_t dx = abs(x0 - x1);
    uint16_t dy = abs(y0 - y1);

    // signs of x and y axes
    int8_t x_mult = (x0 > x1) ? -1 : 1;
    int8_t y_mult = (y0 > y1) ? -1 : 1;

    if(dx == 0)
    {
        drawVerticalLine(x0, y0, (y1 - y0), color, mode);
    }
     else if(dy == 0)
    {
        drawHorizontalLine(x0, y0, (x1 - x0), color, mode);
    }
    // positive slope
    else if(dy < dx)
    {
        int16_t d = (2 * dy) - dx;
        uint16_t y = 0;
        for(uint16_t x = 0; x <= dx; ++x)
        {
            drawPixel(x0 + (x * x_mult), y0 + (y * y_mult), color, mode);
            if(d > 0)
            {
                ++y;
                d -= dx;
            }
            d += dy;
        }
    }
    else if(dy > dx) // negative slope
    {
        int16_t d = (2 * dx) - dy;
        uint16_t x = 0;
        for(uint16_t y = 0; y <= dy; ++y)
        {
            drawPixel(x0 + (x * x_mult), y0 + (y * y_mult), color, mode);
            if(d > 0)
            {
                ++x;
                d -= dy;
            }
            d += dx;
        }
    }
    else if(dx == dy)
    {
        drawPixel(x0, y0, color, mode);
    }
}

void SGL::drawLine2(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t color, const Mode mode)
{
#ifdef CHECK_LINE_PARAMETRS
    if(x0 >= width_)
        x0 = width_ - 1;
    if(x1 >= width_)
        x1 = width_ - 1;
    if(y0 >= height_)
        y0 = height_ - 1;
    if(y1 >= height_)
        y1 = height_ - 1;
#endif

    uint16_t dx = abs(x0 - x1);
    uint16_t dy = abs(y0 - y1);

    if(dx == 0)
    {
        drawVerticalLine(x0, y0, (y1 - y0), color, mode);
    }
     else if(dy == 0)
    {
        drawHorizontalLine(x0, y0, (x1 - x0), color, mode);
    }

    // signs of x and y axes
    int8_t x_mult = (x0 < x1) ? 1 : -1;
    int8_t y_mult = (y0 < y1) ? 1 : -1;
    int16_t err = ((dx > dy) ? dx : -dy) / 2;
    int16_t e2;

    while (true)
    {
        drawPixel(x0, y0, color, mode);

        if (x0 == x1 && y0 == y1) {
            break;
        };

        e2 = err + err;

        if (e2 > -dx) {
            err -= dy;
            x0 += x_mult;
        }

        if (e2 < dy) {
            err += dx;
            y0 += y_mult;
        }
    }
}

void SGL::drawHorizontalLine(uint16_t x0, uint16_t y0, int16_t len, const uint16_t color, const Mode mode)
{
#ifdef CHECK_LINE_PARAMETRS
    if((x0 + len) >= width_ )
    {
        len = width_ - x0 - 1;
    }
    else if((x0 + len) < 0)
    {
        len = -x0;
    }
#endif
    if(len > 0)
    {
#ifdef SGL_USE_BUFFER
        memset16((buffer_ + y0 * height_ + x0), color, len + 1);
#else
        for(int16_t i = 0; i <= len; ++i)
        {
            drawPixel(x0 + i, y0, color, mode);
        }
#endif
    }
    else if(len < 0)
    {
#ifdef SGL_USE_BUFFER
        len = abs(len);
        memset16((buffer_ + (y0 * height_ + x0 - len)), color, len + 1);
#else
        for(int16_t i = 0; i >= len; --i)
        {
            drawPixel(x0 + i, y0, color, mode);
        }
#endif
    }
    else
    {
        //do nothing
    }
}

void SGL::drawVerticalLine(uint16_t x0, uint16_t y0, int16_t len, const uint16_t color, const Mode mode)
{
#ifdef CHECK_LINE_PARAMETRS
    if((y0 + len) > height_ )
    {
        len = width_ - y0;
    }
    else if((y0 + len) < 0)
    {
        len = -y0;
    }
#endif

    if(len > 0)
    {
        for(int16_t i = 0; i <= len; ++i)
        {
            drawPixel(x0, y0 + i, color, mode);
        }
    }
    else if(len < 0)
    {
        for(int16_t i = 0; i >= len; --i)
        {
            drawPixel(x0, y0 + i, color, mode);
        }
    }
    else
    {
        //do nothing
    }
}

void SGL::drawRectangle(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, const uint16_t color, const Fill fill, const Mode mode)
{
    uint16_t x1 = x0 + width;
    uint16_t y1 = y0 + height;

    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;

    /*
    if(dx == 0)
    {
        drawVerticalLine(x0, y0, (y1 - y0 + 1), color, mode);
        return;
    }
    else if(dy == 0)
    {
        drawHorizontalLine(x0, y0, (x1 - x0 + 1), color, mode);
        return;
    }
     */

    if(fill == Fill::solid)
    {
        if(dx > dy) // slightly better efficiency
        {
            //horizontal
            int16_t len = x1 - x0 + 1;
            for(uint16_t i = y0; i <= y1; ++i)
            {
                drawHorizontalLine(x0, i, len, color,mode);
            }
        }
        else
        {   
            //vertical
            int16_t len = y1 - y0 + 1;
            for(uint16_t i = x0; i <= x1; ++i)
            {
                drawVerticalLine(i, y0, len, color,mode);
            }
        }
    }
    else
    {
        int16_t lenX = x1 - x0 + 1;
        int16_t lenY = y1 - y0 + 1;
        drawHorizontalLine(x0, y0, lenX, color, mode);
        drawHorizontalLine(x0, y1, lenX, color, mode);
        drawVerticalLine(x0, y0, lenY, color, mode);
        drawVerticalLine(x1, y0, lenY, color, mode);
    }
}

void SGL::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t x2, const uint16_t y2, const uint16_t color, const Fill fill, const Mode mode)
{

    // the drawLine function checks the arguments
    /*
    if(x0 >= width_)
        x0 = width_ - 1;
    if(x1 >= width_)
        x1 = width_ -1;
    if(x2 >= width_)
        x2 = width_ -1;
    if(y0 >= height_)
        y0 = height_ - 1;
    if(y1 >= height_)
        y1 = height_ - 1;
    if(y2 >= height_)
        y2 = height_ - 1;
    */

    // if transparent, just draw outline
    if(fill == Fill::hole)
    {
        drawLine(x0, y0, x1, y1, color, mode);
        drawLine(x1, y1, x2, y2, color, mode);
        drawLine(x2, y2, x0, y0, color, mode);
    }
    else
    {
        // not implemented yet, draw outline only
        drawLine(x0, y0, x1, y1, color, mode);
        drawLine(x1, y1, x2, y2, color, mode);
        drawLine(x2, y2, x0, y0, color, mode);
    }
}
        
void SGL::drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, const uint16_t color, const Fill fill, const Mode mode)
{
    if(radius <= 0)
        return;
    // from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm

    int16_t x = radius;
    int16_t y = 0;
    int16_t radiusError = 1 -x;

    while (x >= y)
    {

        // if transparent, just draw outline
        if (fill == Fill::hole)
        {
            drawPixel( x + x0,  y + y0, color, mode);
            drawPixel(-x + x0,  y + y0, color, mode);
            drawPixel(-x + x0,  y + y0, color, mode);

            drawPixel( y + x0,  x + y0, color, mode);
            drawPixel(-y + x0,  x + y0, color, mode);

            drawPixel(-y + x0, -x + y0, color, mode);
            drawPixel( y + x0, -x + y0, color, mode);

            drawPixel( x + x0, -y + y0, color, mode);
            drawPixel(-x + x0, -y + y0, color, mode);
        }
        else
        { // drawing filled circle, so draw lines between points at same y value
            drawLine(-x + x0,  y + y0, x + x0,  y + y0, color, mode);

            drawLine(-y + x0,  x + y0, y + x0,  x + y0, color, mode);

            drawLine(-y + x0, -x + y0, y + x0, -x + y0, color, mode);

            drawLine(-x + x0, -y + y0, x + x0, -y + y0, color, mode);
        }

        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

uint16_t SGL::getXOffset() const
{
        return x_start_;
}

void SGL::setXOffset(uint16_t xStart)
{
        x_start_ = xStart;
}

uint16_t SGL::getYOffset() const
{
        return y_start_;
}

void SGL::setYOffset(uint16_t yStart)
{
        y_start_ = yStart;
}

void SGL::drawChar(char c, uint16_t x, uint16_t y) // for the new font
// bedzie problem z pusta linia po lewej znaku - w szerokosci fontu sie tego nie uwzglednia, a nie wszystkie znaki to maja
// podsumowujac czasem jest, czasem nie ma pustej linii z lewej - nie ma informacji kiedy jest
// trzeba by sprobowac rysowac je ze stala szerokoscia fontu, nie chara
// lub cos usunac ta linie z char gdzie wystepuje i ja szcztucznie dorysowywac
// w creatorze fontow mozna je wszystkie przysnapowac do lewej, nastepnie na podstawie szerokosci narysowac i dododac space z prawej
// lub dodawac tylko w draw sring, chociaz chyba w draw char bedzie prosciej
// moze stworzyc klase, strukture, statyczna strukture, jedna tabela zawiera tylko szerokosci znakow, druga zawiera bitmapy
// od razu dodac wysokosc i ile bajtow wychodzi na kolumne
{
}

void SGL::drawString(const unsigned char* c, uint16_t x, uint16_t y)
{
    uint lenstr = strlen(reinterpret_cast<const char*>(c));
    for(int i = 0; i < lenstr ; ++c ++i) {
        if(x > width_ - _font->get_char_width(*c-32) && _font->wrap == false)
        {
            return;
        }
        if(x > width_ - _font->get_char_width(*c-32))
        {
            y += _font->font_height;
        }
        if(*c > 126)
        {
            drawChar((char)127, x, y);
        }
        else
        {
            drawChar(*c, x, y);
        }
        x += _font->get_char_width(*c-32);
    }
}

void SGL::drawChar_2(uchar c, uint16_t x, uint16_t y, int8_t size, uint8_t size_x, uint8_t size_y)
{
    c -= _font->first_char;
    //
    SGLglyph* glyph = &(_font->glyph[c]);
    //
    uint8_t *bitmap = _font->font_array;
    uint16_t bo = glyph->bitmapOffset;
    uint8_t w = glyph->width;
    uint8_t h = glyph->height;
    int8_t xo = glyph->xOffset;
    int8_t yo = glyph->yOffset;
    uint8_t xx, yy, bits = 0, bit = 0;
    int16_t xo16 = 0, yo16 = 0;

    if (size_x > 1 || size_y > 1)
    {
      xo16 = xo;
      yo16 = yo;
    }


    for (yy = 0; yy < h; yy++) {
      for (xx = 0; xx < w; xx++) {
        if (!(bit++ & 7)) {
          bits = bitmap[bo++];
        }
        if (bits & 0x80) {
          if (size_x == 1 && size_y == 1) {
            drawPixel(x + xo + xx, y + yo + yy, _font->color);
          } else {
            drawRectangle(x + (xo16 + xx) * size_x, y + (yo16 + yy) * size_y,
                          size_x, size_y, _font->color, Fill::solid);
          }
        }
        bits <<= 1;
      }
    }
}


void SGL::drawChar_3(uchar c, uint16_t x, uint16_t y, int8_t size, uint8_t size_x, uint8_t size_y)
{
    // Filter out bad characters not present in font
    if ((c >= _font->first_char) && (c <= _font->last_char))
    {

      c -= _font->first_char;
      GFXglyph *glyph  = &(((GFXglyph *)pgm_read_dword(&gfxFont->glyph))[c]);
      uint8_t  *bitmap = (uint8_t *)pgm_read_dword(&gfxFont->bitmap);

      uint32_t bo = pgm_read_word(&glyph->bitmapOffset);
      uint8_t  w  = pgm_read_byte(&glyph->width),
               h  = pgm_read_byte(&glyph->height);
               //xa = pgm_read_byte(&glyph->xAdvance);
      int8_t   xo = pgm_read_byte(&glyph->xOffset),
               yo = pgm_read_byte(&glyph->yOffset);
      uint8_t  xx, yy, bits=0, bit=0;
      int16_t  xo16 = 0, yo16 = 0;

      if(size > 1) {
        xo16 = xo;
        yo16 = yo;
      }

      // GFXFF rendering speed up
      uint16_t hpc = 0; // Horizontal foreground pixel count
      for(yy=0; yy<h; yy++)
      {
        for(xx=0; xx<w; xx++)
        {
          if(bit == 0)
          {
            bits = pgm_read_byte(&bitmap[bo++]);
            bit  = 0x80;
          }
          if(bits & bit) hpc++;
          else
          {
           if (hpc)
           {
              if(size == 1) drawFastHLine(x+xo+xx-hpc, y+yo+yy, hpc, _font->color);
              else fillRect(x+(xo16+xx-hpc)*size, y+(yo16+yy)*size, size*hpc, size, -font->color);
              hpc=0;
            }
          }
          bit >>= 1;
        }
        // Draw pixels for this line as we are about to increment yy
        if (hpc) {
          if(size == 1) drawFastHLine(x+xo+xx-hpc, y+yo+yy, hpc, _font->color);
          else fillRect(x+(xo16+xx-hpc)*size, y+(yo16+yy)*size, size*hpc, size, _font->color);
          hpc=0;
        }
      }
    }
}
void SGL::drawString_2(const unsigned char* c, uint16_t x, uint16_t y)
{
    ;
}

void SGL::drawBitmap16(uint16_t* bitmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    // TO DO CHECK IF THIS IS CORRECT
    if(x >= width_)
        x = width_ - 1;
    if(y >= height_)
        y = height_ - 1;
    if((x + width) >= width_)
        width = width_ - x - 1;
    if((y + height_) >= height_)
        height = height_ - y - 1;
    for(uint16_t i = 0; i <= width; i++)
    {
        for(uint16_t j = 0; j <= height; j++)
        {
            drawPixel(i + x, j + x, *(bitmap + i + j * width));
        }
    }
}

unsigned char SGL::reverseBytes(unsigned char b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}


}