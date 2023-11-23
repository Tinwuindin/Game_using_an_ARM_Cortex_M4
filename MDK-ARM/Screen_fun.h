#include "main.h"

#define rec_size 24
#define grosor 4
#define offset (uint8_t)(grosor / 2)
#define Vertical_line 2
#define Diagonal_line 1
#define Horizontal_line 0

#define fondo LCD_COLOR_WHITE

void Map_draw(void);
void Draw_obs(uint16_t x, uint16_t y, uint16_t x1, uint16_t y1, uint8_t dir);
