#include "main.h"

#define running 1
#define pause 2
#define end 3
#define cant_calib 10
#define L3GD20_SENSITIVITY_250DPS  ((float)0.0175) 

/* Variables */
volatile static int16_t gyro_data_crudo[3];


void Gyro_init(void);
