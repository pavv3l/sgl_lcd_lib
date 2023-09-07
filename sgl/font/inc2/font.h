#ifndef __FONT_H__
#define __FONT_H__

#include <cstdint>

namespace sgl
{

class SGLglyph // Data stored PER GLYPH
{
public:
	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor pos to UL corner
};

class SGLFont // Data stored for FONT AS A WHOLE:
{
public:
	uint8_t  *font_array;      // Glyph bitmaps, concatenated
	SGLglyph *glyph;       // Glyph array
	uint8_t  first_char, last_char; // ASCII extents
	uint8_t   yAdvance;    // Newline distance (y axis)
    uint16_t color;
    bool wrap = true;
    uint8_t get_char_width(unsigned char ch)
    {
        
    }
    uint8_t get_char_height(unsigned char ch)
    {
        ;
    }
};


} // namespace sgl

#endif // __FONT_H__