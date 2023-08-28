#ifndef __FONT_H__
#define __FONT_H__

#include <cstdint>

namespace sgl
{

typedef struct { // Data stored PER GLYPH
	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor pos to UL corner
} SGLglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
	uint8_t  *bitmap;      // Glyph bitmaps, concatenated
	SGLglyph *glyph;       // Glyph array
	uint16_t  first, last; // ASCII extents
	uint8_t   yAdvance;    // Newline distance (y axis)
    uint16_t color;
} SGLfont;

class SGLFont
{
private:
public:
    SGLFont(uint8_t _width, uint8_t font_height, SGLglyph* _glyph, char first, char last,const uint8_t* array):
        font_width(_width), font_height(font_height), glyph_array(_glyph), first_char(first), last_char(last), font_array(array), wrap(true)
    {
    }
    virtual ~SGLFont() = default;

    SGLFont(const SGLFont&) = default;
    SGLFont(SGLFont&&) = default;
    SGLFont& operator=(const SGLFont&) = default;
    SGLFont& operator=(SGLFont&&) = default;

    inline uint8_t get_char_width(char c);
    inline uint8_t get_char_width(const char* c);

    uint8_t font_width; // max width
    uint8_t font_height;// max height
    unsigned char first_char;    // first char in table
    unsigned char last_char;     // last char in table
    SGLglyph* glyph_array;
    const uint8_t* font_array;
    bool wrap;          // wrap text to a new line?
};

} // namespace sgl

#endif // __FONT_H__