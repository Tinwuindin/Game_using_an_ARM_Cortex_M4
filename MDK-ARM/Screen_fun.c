#include "main.h"
#include "Screen_fun.h"
#include "stm32f429i_discovery_lcd.h"

void Map_draw(void){
	uint16_t x, y, x1, y1;
	/* Funcion para iniciar el juego */
	
	/* Dibujado del mapa */
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	// Marco de la pantalla
	BSP_LCD_FillRect(0, 0, 4, 320);
	BSP_LCD_FillRect(0, 316, 240, 4);
	BSP_LCD_FillRect(236, 0, 4, 320);
	BSP_LCD_FillRect(0, 0, 240, 4);
	
	/* Obstaculos */
	// Linea 1
	x = (0 * rec_size);
	y = (1 * rec_size);
	x1 = (1 * rec_size);
	y1 = (1 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (1 * rec_size);
	y = (1 * rec_size);
	x1 = (2 * rec_size);
	y1 = (0 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	x = (3 * rec_size);
	y = (1 * rec_size);
	x1 = (4 * rec_size);
	y1 = (1 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (6 * rec_size);
	y = (1 * rec_size);
	x1 = (7 * rec_size);
	y1 = (1 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (8 * rec_size);
	y = (0 * rec_size);
	x1 = (9 * rec_size);
	y1 = (1 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	x = (9 * rec_size);
	y = (1 * rec_size);
	x1 = (10 * rec_size);
	y1 = (1 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Segunda linea
	x = (2 * rec_size);
	y = (2 * rec_size);
	x1 = (3 * rec_size);
	y1 = (2 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (4 * rec_size);
	y = (1 * rec_size);
	x1 = (5 * rec_size);
	y1 = (2 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	x = (5 * rec_size);
	y = (2 * rec_size);
	x1 = (6 * rec_size);
	y1 = (1 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	x = (7 * rec_size);
	y = (2 * rec_size);
	x1 = (8 * rec_size);
	y1 = (2 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Tercer linea
	x = (1 * rec_size);
	y = (2 * rec_size);
	x1 = (1 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (2 * rec_size);
	y = (2 * rec_size);
	x1 = (2 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (3 * rec_size);
	y = (2 * rec_size);
	x1 = (3 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (4 * rec_size);
	y = (3 * rec_size);
	x1 = (6 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (5 * rec_size);
	y = (2 * rec_size);
	x1 = (5 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (7 * rec_size);
	y = (2 * rec_size);
	x1 = (7 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (8 * rec_size);
	y = (2 * rec_size);
	x1 = (8 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (9 * rec_size);
	y = (2 * rec_size);
	x1 = (9 * rec_size);
	y1 = (3 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	// Cuarta linea
	x = (1 * rec_size);	
	y = (4 * rec_size);
	x1 = (2 * rec_size);
	y1 = (4 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (3 * rec_size);	
	y = (4 * rec_size);
	x1 = (4 * rec_size);
	y1 = (4 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (5 * rec_size);	
	y = (4 * rec_size);
	x1 = (6 * rec_size);
	y1 = (4 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (7 * rec_size);	
	y = (4 * rec_size);
	x1 = (8 * rec_size);
	y1 = (4 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (9 * rec_size);	
	y = (4 * rec_size);
	x1 = (10 * rec_size);
	y1 = (4 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Quinta linea
	x = (0 * rec_size);	
	y = (5 * rec_size);
	x1 = (1 * rec_size);
	y1 = (5 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (2 * rec_size);	
	y = (5 * rec_size);
	x1 = (3 * rec_size);
	y1 = (5 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (4 * rec_size);	
	y = (5 * rec_size);
	x1 = (5 * rec_size);
	y1 = (5 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (6 * rec_size);	
	y = (5 * rec_size);
	x1 = (7 * rec_size);
	y1 = (5 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (8 * rec_size);	
	y = (5 * rec_size);
	x1 = (9 * rec_size);
	y1 = (5 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Sexta linea
	x = (1 * rec_size);	
	y = (6 * rec_size);
	x1 = (2 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (5 * rec_size);	
	y = (6 * rec_size);
	x1 = (6 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (9 * rec_size);	
	y = (6 * rec_size);
	x1 = (10 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (1 * rec_size);	
	y = (5 * rec_size);
	x1 = (1 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (2 * rec_size);	
	y = (5 * rec_size);
	x1 = (2 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (3 * rec_size);	
	y = (5 * rec_size);
	x1 = (3 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (4 * rec_size);	
	y = (5 * rec_size);
	x1 = (4 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (5 * rec_size);	
	y = (5 * rec_size);
	x1 = (5 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (6 * rec_size);	
	y = (5 * rec_size);
	x1 = (6 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (7 * rec_size);	
	y = (5 * rec_size);
	x1 = (7 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (8 * rec_size);	
	y = (5 * rec_size);
	x1 = (8 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (9 * rec_size);	
	y = (5 * rec_size);
	x1 = (9 * rec_size);
	y1 = (6 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	// Septima linea
	x = (1 * rec_size);	
	y = (7 * rec_size);
	x1 = (2 * rec_size);
	y1 = (7 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (3 * rec_size);	
	y = (7 * rec_size);
	x1 = (4 * rec_size);
	y1 = (7 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (5 * rec_size);	
	y = (7 * rec_size);
	x1 = (6 * rec_size);
	y1 = (7 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (7 * rec_size);	
	y = (7 * rec_size);
	x1 = (8 * rec_size);
	y1 = (7 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Octava linea
	x = (1 * rec_size);	
	y = (7 * rec_size);
	x1 = (1 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (2 * rec_size);	
	y = (7 * rec_size);
	x1 = (2 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (3 * rec_size);	
	y = (7 * rec_size);
	x1 = (3 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (4 * rec_size);	
	y = (7 * rec_size);
	x1 = (4 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (5 * rec_size);	
	y = (7 * rec_size);
	x1 = (5 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (6 * rec_size);	
	y = (7 * rec_size);
	x1 = (6 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (7 * rec_size);	
	y = (7 * rec_size);
	x1 = (7 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (8 * rec_size);	
	y = (7 * rec_size);
	x1 = (8 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (9 * rec_size);	
	y = (7 * rec_size);
	x1 = (9 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (2 * rec_size);	
	y = (8 * rec_size);
	x1 = (3 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (6 * rec_size);	
	y = (8 * rec_size);
	x1 = (7 * rec_size);
	y1 = (8 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Novena linea
	x = (0 * rec_size);	
	y = (9 * rec_size);
	x1 = (1 * rec_size);
	y1 = (9 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (2 * rec_size);	
	y = (9 * rec_size);
	x1 = (3 * rec_size);
	y1 = (9 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (4 * rec_size);	
	y = (9 * rec_size);
	x1 = (5 * rec_size);
	y1 = (9 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (6 * rec_size);	
	y = (9 * rec_size);
	x1 = (7 * rec_size);
	y1 = (9 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (8 * rec_size);	
	y = (9 * rec_size);
	x1 = (9 * rec_size);
	y1 = (9 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Decima linea
	x = (4 * rec_size);	
	y = (10 * rec_size);
	x1 = (6 * rec_size);
	y1 = (10	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Undecima linea
	x = (1 * rec_size);	
	y = (10 * rec_size);
	x1 = (1 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (2 * rec_size);	
	y = (10 * rec_size);
	x1 = (2 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (3 * rec_size);	
	y = (10 * rec_size);
	x1 = (3 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (5 * rec_size);	
	y = (10 * rec_size);
	x1 = (5 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (7 * rec_size);	
	y = (10 * rec_size);
	x1 = (7 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (8 * rec_size);	
	y = (10 * rec_size);
	x1 = (8 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (9 * rec_size);	
	y = (10 * rec_size);
	x1 = (9 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Vertical_line);
	
	x = (2 * rec_size);	
	y = (11 * rec_size);
	x1 = (3 * rec_size);
	y1 = (11	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (7 * rec_size);	
	y = (11 * rec_size);
	x1 = (8 * rec_size);
	y1 = (11	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	// Doceava linea
	x = (0 * rec_size);	
	y = (12 * rec_size);
	x1 = (1 * rec_size);
	y1 = (12	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (3 * rec_size);	
	y = (12 * rec_size);
	x1 = (4 * rec_size);
	y1 = (12	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (6 * rec_size);	
	y = (12 * rec_size);
	x1 = (7 * rec_size);
	y1 = (12	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (9 * rec_size);	
	y = (12 * rec_size);
	x1 = (10 * rec_size);
	y1 = (12	 * rec_size);
	Draw_obs(x, y, x1, y1, Horizontal_line);
	
	x = (4 * rec_size);	
	y = (12 * rec_size);
	x1 = (5 * rec_size);
	y1 = (11 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	x = (5 * rec_size);	
	y = (11 * rec_size);
	x1 = (6 * rec_size);
	y1 = (12	 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	// La cual linea?
	x = (1 * rec_size);	
	y = (12 * rec_size);
	x1 = (2 * rec_size);
	y1 = (13	 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
	x = (8 * rec_size);	
	y = (13 * rec_size);
	x1 = (9 * rec_size);
	y1 = (12 * rec_size);
	Draw_obs(x, y, x1, y1, Diagonal_line);
	
}

void Draw_obs(uint16_t x, uint16_t y, uint16_t x1, uint16_t y1, uint8_t dir){
	uint8_t i;
	for(i = 0; i != grosor; i ++){
		if(dir != Vertical_line){
			y ++;
			y1 ++;
			BSP_LCD_DrawLine(x, y, x1, y1);
		}else{
			x ++;
			x1 ++;
			BSP_LCD_DrawLine(x - offset, y + offset, x1 - offset, y1 + offset);
		}
		
	}
	
	
}

