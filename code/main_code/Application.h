	#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "Modules_Includes.h"
/* ------------------------------------Includes--------------------------------------*/

/* ------------------------------------Macro Declarations--------------------------- */
SPI_Init_Types SPI_Options ={
SPI_Master,
SPI_Clock_128,
SPI_DoubleSpeed_Enable,
SPI_MSB,
SPI_Interrupt_Disable,
SPI_Mode0
};

uint8_t byte;
uint8_t str[MAX_LEN];
uint8_t person_recognised = 0;

uint8 data_recieved = 0;

/* ------------------------------------Macro Function Declarations------------------ */

/* ------------------------------------Data Type Declarations----------------------- */

/* ------------------------------------Software Interface Declarations-------------- */
void intialize_section(void);

#endif /* APPLICATION_H_ */
