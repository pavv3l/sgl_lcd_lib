To bedzie biblioteka sgl zawieracja podstawowe abstracje do rysowanie
drivery - dla poszczegolnych wyswietlaczy z driverami pcd854, ili9341, st7789
oraz jakas abstrkcja dla transportu na rozne plytki, chcialbym, zeby to dzialalo
na RPI PICO (Podstawowe) STM32 (dodatkowo) Arduino(ewentualnie) oraz esp32(ewentualnie)

interfejs SGL:

//  Funkcja konwertujaca kolor rgb 24(RGB888) BIT do 16(RGB565) bitowego hex
#define RGB565(r,g,b) ((((uint16_t)r & 0x00F8) << 8) | (((uint16_t)g & 0x00FC) << 3) | (((uint16_t)b & 0x00F8) >> 3))

    enum class Mode : uint8_t
    {
        pixel_copy = 0x0,   // zwykle nadpisywanie(pixel_and)
        pixel_or = 0x1,
        pixel_xor = 0x2,
        pixel_clr = 0x3
        //pixel_invt = 0x4,
        //pixel_nor  = 0x5,
        //pixel_xnor = 0x6,
        //pixel_nclr = 0x7
    };

    enum class Fill : uint8_t
    {
        solid = 0x0, // BLACK for monochrome
        hole = 0x01  // WHITE for monochrome
    };

    struct Coord
    {
        uint16_t x;
        uint16_t y;
    }

    mozna dodawac funkcje rozszerzajace rysowanie o jakies abstracje
    wszystkie funckje rysujace uzywaja drawPixel - ewentualne usprawnienia dla poszczegolnych driverow
    w klasach pochodnych
// drawPixel jest abstrakcyjny poniewaz jest charakterystyczny dla drivera(rozne metody adresacji/ komunikacji)

virtual void drawPixel(uint16_t x, uint16_t y, uint16_t color = WHITE, Mode mode = Mode::pixel_copy) = 0;
virtual void drawPixel(const Coord& coord,const uint16_t& color = WHITE, const Mode& mode = Mode::pixel_copy) = 0;

virtual void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color = WHITE, Mode mode = Mode::pixel_copy);

// W celu przyspieszenia ryswania na lcd ponizsze funcje powinno sie przeslonic, domyslnie korzystaja z drawPixel
// horizontal i vertical line - dla len = 0 brak linii, dla len = 1 pojedynczy pixel
virtual void drawHorizontalLine(uint16_t x, uint16_t y, int16_t len, uint16_t color = WHITE, Mode mode = Mode::pixel_copy);

virtual void drawVerticalLine(uint16_t x, uint16_t y, int16_t len, uint16_t color = WHITE, Mode mode = Mode::pixel_copy);

void drawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color = WHITE, Fill fill = Fill::hole, Mode mode = Mode::pixel_copy);

void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
    uint16_t color = WHITE, Fill fill = Fill::hole, Mode mode = Mode::pixel_copy);

void drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color = WHITE, Fill fill = Fill::hole, Mode mode = Mode::pixel_copy);