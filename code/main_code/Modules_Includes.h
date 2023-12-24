#ifndef MODULES_INCLUDES_H_
#define MODULES_INCLUDES_H_
#include <avr/io.h>
#include <stdlib.h>
#include "../Library/BitMath.h"
#include "../Library/Clock.h"
#include "../MCAL/DIO/DIO.h"
#include "../HAL/LCD/Includes/LCD.h"

#include "../MCAL/int_EEPROM/eeprom.h"
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/USART/USART.h"


#include "../HAL/MFRC_522/mfrc522.h"
/*===========(Custom Characters)===========
U8 Smile_Face[]={0x1B,
	0x1B,
	0x00,
	0x04,
	0x04,
	0x11,
	0x1F,
0x0E};
U8 Hard_F[]={0b11111,
	0b11111,
	0b11000,
	0b11111,
	0b11111,
	0b11000,
	0b11000,
0b11000};


U8 Mem[]={0b00000,
	0b00000,
	0b11110,
	0b01001,
	0b01001,
	0b00110,
	0b00000,
0b00000};

U8 Haa[]={0b11100,
	0b00011,
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
0b00000};

U8 Mem2[]={0b00000,
	0b00000,
	0b11111,
	0b01010,
	0b01010,
	0b00100,
	0b00000,
0b00000};

U8 Daal[]={	0b00000,
	0b00001,
	0b00001,
	0b00001,
	0b11110,
	0b00000,
	0b00000,
0b00000};
*/
#endif /* MODULES_INCLUDES_H_ */
