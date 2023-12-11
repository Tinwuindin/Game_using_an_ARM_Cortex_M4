#include "Gyro_fun.h"
#include "main.h"
#include "spi.h"

void Gyro_init(void){
	uint8_t mandar_spi[2];
	/* Configuracion inicial */
	
	// Poner canal en espera
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
	HAL_Delay(20);
	
	/* Registro 20 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); // Indicacion de inicio
	HAL_Delay(20);
	mandar_spi[0]=0x20; // Direccion a cual mandar
	// PD bit set, zxy bits set
	mandar_spi[1]=0xFF; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,1,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
	/* Registro 21 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); // Indicacion de inicio
	HAL_Delay(20);
	mandar_spi[0]=0x21; // Direccion a cual mandar
	// filtro pasa altas a 51.4 Hz
	mandar_spi[1]=0x20; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,1,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
	/* Registro 22 en default */
	
	/* Registro 23 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); // Indicacion de inicio
	HAL_Delay(20);
	mandar_spi[0]=0x23; // Direccion a cual mandar
	// Escala a 500 dps
	mandar_spi[1]=0x20; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,1,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
	/* Registro 24 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); // Indicacion de inicio
	HAL_Delay(20);
	mandar_spi[0]=0x24; // Direccion a cual mandar
	//Activamos el pasa altos
	mandar_spi[1]=0x10; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,1,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
}
