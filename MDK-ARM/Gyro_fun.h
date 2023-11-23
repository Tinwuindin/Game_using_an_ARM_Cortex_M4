#include "main.h"

#define running 1
#define pause 2
#define end 3
#define cant_calib 1000
#define L3GD20_SENSITIVITY_250DPS  ((float)0.00875) 

/* Variables */
volatile static int16_t gyro_data_crudo[3];
volatile static float ajuste_x = 0, ajuste_y = 0, ajuste_z = 0;


void Gyro_init(void);
void Gyro_read(void);
