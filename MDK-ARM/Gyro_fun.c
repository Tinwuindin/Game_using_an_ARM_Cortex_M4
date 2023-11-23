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
	mandar_spi[1]=0x0f; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
	/* Registro 21 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); // Indicacion de inicio
	HAL_Delay(20);
	mandar_spi[0]=0x21; // Direccion a cual mandar
	// Sin filtro pasa altas
	mandar_spi[1]=0x00; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
	/* Registro 22 en default */
	
	/* Registro 23 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); // Indicacion de inicio
	HAL_Delay(20);
	mandar_spi[0]=0x23; // Direccion a cual mandar
	// Escala a 500 dps
	mandar_spi[1]=0x10; // Dato a mandar 
	HAL_SPI_Transmit(&hspi5,mandar_spi,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET); // Poner canal en espera
	HAL_Delay(20);
	
	// Recolecci�n de las muestras para la calibracion
	uint32_t i;
	int32_t temp_cali_x = 0;
	int32_t temp_cali_y = 0;
	int32_t temp_cali_z = 0;
	
	for(i = 0; i != cant_calib; i++){
		// Medimos los valores actuales
		Gyro_read();
		
		// Vaciamos los datos leidos a un buffer para calcular el ajuste y ruido promedio
		temp_cali_x += gyro_data_crudo[0];
		temp_cali_y += gyro_data_crudo[1];
		temp_cali_z += gyro_data_crudo[2];
		
	}
	ajuste_x = temp_cali_x / cant_calib;
	ajuste_y = temp_cali_y / cant_calib;
	ajuste_z = temp_cali_z / cant_calib;
	
}

void Gyro_read(void){
	/* leer datos del sensor */
	uint8_t lect_buffer[6];
	uint8_t Registro_leer;
	
	// Condicion de inicio
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
	
	// primer registro de datos + modo lectura con autodesplazamiento
	Registro_leer = 0x28|0xC0;
	HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
	HAL_SPI_Receive(&hspi5,&lect_buffer[0],1,50);
	HAL_SPI_Receive(&hspi5,&lect_buffer[1],1,50);
	HAL_SPI_Receive(&hspi5,&lect_buffer[2],1,50);
	HAL_SPI_Receive(&hspi5,&lect_buffer[3],1,50);
	HAL_SPI_Receive(&hspi5,&lect_buffer[4],1,50);
	HAL_SPI_Receive(&hspi5,&lect_buffer[5],1,50);
	
	//Condicion de reposo
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
	
	/* Se ajustan los valores de los registros a 16 bits */
	
	gyro_data_crudo[0] = (lect_buffer[0] | (lect_buffer[1] << 8)) - ajuste_x;
	gyro_data_crudo[1] = (lect_buffer[2] | (lect_buffer[3] << 8)) - ajuste_y;
	gyro_data_crudo[2] = (lect_buffer[4] | (lect_buffer[5] << 8)) - ajuste_z;
	
	
	
}