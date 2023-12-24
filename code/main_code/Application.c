#include "Modules_Includes.h"
#include "Application.h"

#define BLUE 	2
#define WHITE 	3
int main (void)
{
	intialize_section();

	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);

	while(1){
	byte = mfrc522_request(PICC_REQALL,str);
	_delay_ms(100);
			if(byte == CARD_FOUND)
			{
			  byte = mfrc522_get_card_serial(str);
			  if(byte == CARD_FOUND)
			  {
				DIO_WriteChannel(DIO_ChannelA0 ,STD_High);
				person_recognised = 1;
				UART_SendByte('@');
				for(byte=0;byte<8;byte++){
					UART_SendByte(str[byte]);
				}
				UART_SendByte(';');
				}

			}
			if(1 == person_recognised){
				person_recognised = 0;
			data_recieved = UART_ReceiveByte();
			if('1' == data_recieved){
				DIO_WriteChannel(DIO_ChannelA1 ,STD_High);
				_delay_ms(500);
				DIO_WriteChannel(DIO_ChannelA1 ,STD_Low);
        DIO_WriteChannel(DIO_ChannelA0 ,STD_Low);
			}
			else if('2' == data_recieved){
				DIO_WriteChannel(DIO_ChannelA2 ,STD_High);
				_delay_ms(500);
				DIO_WriteChannel(DIO_ChannelA2 ,STD_Low);
        DIO_WriteChannel(DIO_ChannelA0 ,STD_Low);
			}else{/*Nothing*/}

		}
	}
return 0;
}

void intialize_section(void){
	SPI_Init(&SPI_Options);
	mfrc522_init();
	UART_Init();
	DIO_ConfigChannel(DIO_ChannelA0 ,OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA1 ,OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA2 ,OUTPUT);

}
