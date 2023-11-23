/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Gyro_fun.h"
#include <stdio.h>
#include <stdlib.h>
#include "rtc.h"
#include "spi.h"
#include "stm32f429i_discovery_lcd.h"
#include "Screen_fun.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct{
	uint16_t ball_x;
	uint16_t ball_y;
}ball_pos;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define Colision_detected 1
#define No_colision 0
#define Cir_size 8
#define friccion (-0.01)
#define peso 5
#define extend peso + 2
#define sensibilidad 10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

extern uint8_t Linea;

extern volatile uint8_t game_status;
extern RTC_TimeTypeDef hora;


	uint16_t helper_x = 0, helper_y = 0;
	int16_t diff;
	
/* USER CODE END Variables */
osThreadId GraphicsHandle;
osThreadId LogicsHandle;
osThreadId ComunnicationHandle;
osMessageQId x_colaHandle;
osMessageQId y_colaHandle;
osMessageQId z_colaHandle;
osMessageQId BallHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */


/* USER CODE END FunctionPrototypes */

void Image_task(void const * argument);
void Logic_task(void const * argument);
void Com_task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of x_cola */
  osMessageQDef(x_cola, 1, int16_t);
  x_colaHandle = osMessageCreate(osMessageQ(x_cola), NULL);

  /* definition and creation of y_cola */
  osMessageQDef(y_cola, 1, int16_t);
  y_colaHandle = osMessageCreate(osMessageQ(y_cola), NULL);

  /* definition and creation of z_cola */
  osMessageQDef(z_cola, 1, int16_t);
  z_colaHandle = osMessageCreate(osMessageQ(z_cola), NULL);

  /* definition and creation of Ball */
  osMessageQDef(Ball, 1, ball_pos);
  BallHandle = osMessageCreate(osMessageQ(Ball), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Graphics */
  osThreadDef(Graphics, Image_task, osPriorityNormal, 0, 128);
  GraphicsHandle = osThreadCreate(osThread(Graphics), NULL);

  /* definition and creation of Logics */
  osThreadDef(Logics, Logic_task, osPriorityNormal, 0, 128);
  LogicsHandle = osThreadCreate(osThread(Logics), NULL);

  /* definition and creation of Comunnication */
  osThreadDef(Comunnication, Com_task, osPriorityHigh, 0, 128);
  ComunnicationHandle = osThreadCreate(osThread(Comunnication), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Image_task */
/**
  * @brief  Function implementing the Graphics thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Image_task */
void Image_task(void const * argument)
{
  /* USER CODE BEGIN Image_task */
  /* Infinite loop */
	
	uint16_t prev_x = 10, prev_y = 10;
	ball_pos coordenadas;
	
  for(;;)
  {
		switch (game_status){
			case running:
				// Recibimos las posiciones del circulo
				xQueueReceive(BallHandle, &coordenadas,((TickType_t) 10));
				// Borramos la figura previa
				BSP_LCD_SetTextColor(fondo);
				BSP_LCD_FillCircle(prev_x, prev_y, Cir_size);
				// Dibujamos la nueva figura
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
				BSP_LCD_FillCircle(coordenadas.ball_x, coordenadas.ball_y, Cir_size);
				// Dibujamos el mapa
				Map_draw();
				// Guardamos la posición del circulo dibujado
				prev_x = coordenadas.ball_x;
				prev_y = coordenadas.ball_y;
				break;
			case pause:
				// Limpiamos la pantalla del juego
				BSP_LCD_Clear(LCD_COLOR_WHITE);
				// Mostramos el mensaje de pausa
				Linea = 5;
				printf("Juego pausado\n");
				printf("Presione start\n");
				printf("para continuar\n");
				// Esperamos sin hacer nada para evitar parpadeos
				while(game_status == pause);
				BSP_LCD_Clear(LCD_COLOR_WHITE);
				break;
			case end:
				// Limpiamos la pantalla
				BSP_LCD_Clear(LCD_COLOR_WHITE);
				// Mostramos el mensaje	
				Linea = 5;
				printf("Game over\n");
				// Recuperamos el tiempo tomado y lo mostramos
				HAL_RTC_GetTime(&hrtc, &hora, RTC_FORMAT_BIN);
				printf("Min: %d\n",hora.Minutes);
				printf("Sec: %d\n",hora.Seconds);
				// Esperamos a que pase el estado de terminado
				while(game_status == end);
				// Reiniciamos el rtc
				hora.Seconds = 0;
				hora.Minutes = 0;
				HAL_RTC_SetTime(&hrtc, &hora, RTC_FORMAT_BIN);
				// Limpiamos la pantalla
				BSP_LCD_Clear(LCD_COLOR_WHITE);
				break;
			
			
		}
		
		
    osDelay(23);
  }
  /* USER CODE END Image_task */
}

/* USER CODE BEGIN Header_Logic_task */
/**
* @brief Function implementing the Logics thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Logic_task */
void Logic_task(void const * argument)
{
  /* USER CODE BEGIN Logic_task */
  /* Infinite loop */
  
	// Variables para la colision
	uint32_t col_value;
	int16_t xc, yc, xb, yb;
	
	uint8_t ver_col = 0, hor_col = 0;
	
	// Variables para la velocidad
	int16_t rel_x = 0, rel_y = 0, rel_z = 0;
	int16_t x_speed = 0, y_speed = 0, z_speed = 0;
	uint16_t prev_cir_x = 121, prev_cir_y = 292;
	ball_pos position;
	
	position.ball_x = 121;
	position.ball_y = 292;
	
	uint8_t i, j;
  for(;;)
  {
		if(game_status == running){
			/* Desplazar la figura */
			//Recibimos los datos de velocidad en otra variable para evitar perder el origen
			xQueueReceive(x_colaHandle, &x_speed,((TickType_t) 10));
			xQueueReceive(y_colaHandle, &y_speed,((TickType_t) 10));
			xQueueReceive(z_colaHandle, &rel_z,((TickType_t) 10));
			
			// Guardamos la velocidad sin modificar
			rel_x += x_speed;
			rel_y += y_speed;	
			
			// Pasamos los datos a la velocidad actual
			x_speed += rel_x;
			y_speed += rel_y;		
			
			// Logica del rozamiento
			/*if(x_speed >= 1)
				x_speed --;
			else if(x_speed <= -1)
				x_speed ++;
			if(y_speed >= 1)
				y_speed --;
			else if (y_speed <= -1)
				y_speed ++;
			*/
			
			// Peso de la pelota
			if(y_speed > peso){
				y_speed = peso;
				rel_y = peso;
			}
			if(y_speed < -peso){
				y_speed = -peso;
				rel_y = -peso;
			}
			if(x_speed > peso){
				x_speed = peso;
				rel_x = peso;
			}
			if(x_speed < -peso){
				x_speed = -peso;
				rel_x = -peso;
			}
			
			/* Comprobar posible colision */
			
			// Primer cuadrante
			// Horizontal
			i = 0;
			while( (i <= (Cir_size)) && (hor_col == No_colision)){
				for(j = 1; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x + j, position.ball_y - i);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						xc = position.ball_x + j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						xb = position.ball_x + j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = abs(xb - xc);
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff <= x_speed){
							hor_col = Colision_detected;
						}
						break;
					}
				}
				
				i++;
			}
			// Vertical
			i = 0;
			while( (i <= (Cir_size)) && (ver_col == No_colision)){
				for(j = 0; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x + i, position.ball_y - j);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						yc = position.ball_y - j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						yb = position.ball_y - j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = yb - yc;
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff >= y_speed){
							ver_col = Colision_detected;
						}
						break;
					}
				}
				i++;
			}
			// Segundo cuadrante
			// Horizontal
			i = 0;
			while( (i <= (Cir_size)) && (hor_col == No_colision)){
				for(j = 0; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x - j, position.ball_y - i);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						xc = position.ball_x - j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						xb = position.ball_x - j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = xb - xc;
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff >= x_speed){
							hor_col = Colision_detected;
							xb = 0;
							xc = 0;
						}else{
							xb = 0;
						}
						break;
					}
				}
				i++;
			}
			// Vertical
			i = 0;
			while( (i <= (Cir_size)) && (ver_col == No_colision)){
				for(j = 1; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x - i, position.ball_y - j);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						yc = position.ball_y - j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						yb = position.ball_y - j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = yb - yc;
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff >= y_speed){
							ver_col = Colision_detected;
							yb = 0;
							yc = 0;
						}else{
							yb = 0;
						}
						break;
					}
				}
				
				i++;
			}
			
			// Tercer cuadrante
			// Horizontal
			i = 0;
			while( (i <= (Cir_size)) && (hor_col == No_colision)){
				for(j = 0; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x - j, position.ball_y + i);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						xc = position.ball_x - j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						xb = position.ball_x - j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = xb - xc;
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff >= x_speed){
							hor_col = Colision_detected;
						}
						break;
					}
				}
				
				i++;
			}
			// Vertical
			i = 0;
			while( (i <= (Cir_size)) && (ver_col == No_colision)){
				for(j = 1; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x - i, position.ball_y + j);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						yc = position.ball_y + j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						yb = position.ball_y + j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = abs(yb - yc);
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff <= y_speed){
							ver_col = Colision_detected;
						}
						break;
					}
				}
				
				i++;
			}
			// Cuarto cuadrante
			// Horizontal
			i = 0;
			while( (i <= (Cir_size)) && (hor_col == No_colision)){
				for(j = 1; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x + j, position.ball_y + i);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						xc = position.ball_x + j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						xb = position.ball_x + j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = abs(xb - xc);
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff <= x_speed){
							hor_col = Colision_detected;
						}
						break;
					}
				}
				
				i++;
			}
			// Vertical
			i = 0;
			while( (i <= (Cir_size)) && (ver_col == No_colision)){
				for(j = 0; j <= (Cir_size + extend); j++){
					//Desplazamiento horizontal
					col_value = BSP_LCD_ReadPixel(position.ball_x + i, position.ball_y + j);
					// Guardamos la ultima posicion del circulo
					if(col_value == LCD_COLOR_RED)
						yc = position.ball_y + j;
					// Guardamos la primera posicion del borde y detenemos
					if(col_value == LCD_COLOR_BLACK){
						yb = position.ball_y + j;
						// Sacamos la diferencia de entre el circulo y el borde
						diff = abs(yb - yc);
						// Si la diferencia es menor al movimiento se marca como colision
						if(diff <= y_speed){
							ver_col = Colision_detected;
						}
						break;
					}
				}
				
				i++;
			}

			if(ver_col == Colision_detected){
				// Ajustamos la velocidad por el choque
				y_speed *= friccion;
				// Borramos la direccion del choque
				ver_col = No_colision;
			}
			if(hor_col == Colision_detected){
				// Ajustamos la velocidad por el choque
				x_speed *= friccion;
				// Borramos la direccion del choque
				hor_col = No_colision;
			}
				
			// Ajustamos la posicion de la pelota
			position.ball_x += x_speed;
			position.ball_y += y_speed;
			
			// Mandamos los datos por la cola
			xQueueSend(BallHandle, &position,((TickType_t) 10));
			
			/* Apoyo para perdida de origen */
			diff = abs(position.ball_x - prev_cir_x);
			if(diff < 1)
				helper_x++;
			if(helper_x >= 100){
				rel_x = 0;
				helper_x = 0;
			}
			diff = abs(position.ball_y - prev_cir_y);
			if(diff < 1)
				helper_y++;
			if(helper_y >= 100){
				rel_y = 0;
				helper_y = 0;
			}
			
			prev_cir_x = position.ball_x;
			prev_cir_y = position.ball_y;
			
			/* Comprobar si se llego a la meta */
			if(position.ball_y <= (Cir_size + 6)){
				position.ball_x = 121;
				position.ball_y = 292;
				game_status = end;
			}
		}
    osDelay(50);
  }
  /* USER CODE END Logic_task */
}

/* USER CODE BEGIN Header_Com_task */
/**
* @brief Function implementing the Comunnication thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Com_task */
void Com_task(void const * argument)
{
  /* USER CODE BEGIN Com_task */
  /* Infinite loop */
  
	int16_t prevx = 0, prevy = 0, prevz = 0, buff_x, buff_y;
	uint8_t lect_buffer[6];
	uint8_t Registro_leer;
	float x_d, y_d,z_d;
	
  for(;;)
  {
		/* Obtener la velocidad del movimento */
		
		// Llamamos a los nuevos datos
		// Condicion de inicio
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
		// registo a leer
		Registro_leer = 0x28|0x80;
		HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
		HAL_SPI_Receive(&hspi5,&lect_buffer[0],1,50);
		//Condicion de reposo
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
		
		// Condicion de inicio
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
		// registo a leer
		Registro_leer = 0x29|0x80;
		HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
		HAL_SPI_Receive(&hspi5,&lect_buffer[1],1,50);
		//Condicion de reposo
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
		
		// Condicion de inicio
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
		// registo a leer
		Registro_leer = 0x2A|0x80;
		HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
		HAL_SPI_Receive(&hspi5,&lect_buffer[2],1,50);
		//Condicion de reposo
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
		
		// Condicion de inicio
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
		// registo a leer
		Registro_leer = 0x2B|0x80;
		HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
		HAL_SPI_Receive(&hspi5,&lect_buffer[3],1,50);
		//Condicion de reposo
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
		
		// Condicion de inicio
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
		// registo a leer
		Registro_leer = 0x2C|0x80;
		HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
		HAL_SPI_Receive(&hspi5,&lect_buffer[4],1,50);
		//Condicion de reposo
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);

		// Condicion de inicio
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
		// registo a leer
		Registro_leer = 0x2D|0x80;
		HAL_SPI_Transmit(&hspi5,&Registro_leer,1,50);
		HAL_SPI_Receive(&hspi5,&lect_buffer[5],1,50);
		//Condicion de reposo
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);	
		
		
		/* Se ajustan los valores de los registros a 16 bits */
		gyro_data_crudo[0] = (lect_buffer[0] | (lect_buffer[1] << 8)) - ajuste_x;
		gyro_data_crudo[1] = (lect_buffer[2] | (lect_buffer[3] << 8)) - ajuste_y;
		gyro_data_crudo[2] = (lect_buffer[4] | (lect_buffer[5] << 8)) - ajuste_z;
		
		// Ajustamos los valores para x 
		if(((gyro_data_crudo[0] - prevx) < 15) || ((gyro_data_crudo[0] - prevx) > 15)){ // Si la difencia es mayor al ruido 
			x_d = (float)(gyro_data_crudo[0] * L3GD20_SENSITIVITY_250DPS);
			prevx = gyro_data_crudo[0];
		}else
			x_d = 0;
		
		// Ajustamos los valores para y
		if(((gyro_data_crudo[1] - prevy) < 15) || ((gyro_data_crudo[1] - prevy) > 15)){
			y_d = (float)(gyro_data_crudo[1] * L3GD20_SENSITIVITY_250DPS);
			prevy = gyro_data_crudo[1];
		}else 
			y_d = 0;
		
		// Ajustamos los valores para z
		if(((gyro_data_crudo[2] - prevz) < 15) || ((gyro_data_crudo[2] - prevz) > 15)){
			z_d = (float)(gyro_data_crudo[2] * L3GD20_SENSITIVITY_250DPS);
			prevz = gyro_data_crudo[2];
		}
		
		// Convertimos los valores para recibirlos en la funcion de choques
		// Giramos los datos X y Y
		buff_x = (int16_t)(y_d / sensibilidad);
		buff_y = (int16_t)(x_d / sensibilidad);
		z_d = (int16_t)(z_d / sensibilidad);
		
		// Mandamos los valores por la cola hacia el calculador de velocidad
		xQueueSend(x_colaHandle, &buff_x,((TickType_t) 10));
		xQueueSend(y_colaHandle, &buff_y,((TickType_t) 10));
		xQueueSend(z_colaHandle, &z_d,((TickType_t) 10));

    osDelay(50);
  }
  /* USER CODE END Com_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
