
#include "USART.h"
#include "USART_config.h"

 /****************************Pointer to functions to be assigned to ISR*********************************/

static void (*UART_RX_Fptr) (void);
static void (*UART_TX_Fptr) (void);


/********************************************initialization **********************************************/

/************************* Array of  UBRR values ***************************/
const uint16_t BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
		 {{{103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34}},
		  {{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68}}};

void UART_Init(void)
{
	uint8  UCSRC_var=0;
	uint16_t UBRR_var=0;
/***************************** transmission speed***************************/
	#if (SPEED_MODE==NORMAL_SPEED)
	ClearBit(UCSRA,U2X);
	#elif (SPEED_MODE==DOUBLE_SPEED)
	SetBit(UCSRA,U2X);
	#endif

//******************set URSEL to write data to UCSRC register***************/
   SetBit(UCSRC_var,URSEL);

//********************************synch***********************************/
	 #if (SYNCH_MODE==SYNCH)
	 SetBit(UCSRC_var,UMSEL)
	 #elif (SYNCH_MODE==ASYNCH)
 	 ClearBit(UCSRC_var,UMSEL);
	 #endif
 //*****************************parity mode*******************************/

	#if (PARITY_MODE==NO_PARITY)
	ClearBit(UCSRC_var,UPM0);
	ClearBit(UCSRC_var,UPM1);
	#elif (PARITY_MODE==EVEN_PARITY)
	ClearBit(UCSRC_var,UPM0);
	SetBit(UCSRC_var,UPM1);
	#elif (PARITY_MODE==ODD_PARITY)
	SetBit(UCSRC_var,UPM0);
	SetBit(UCSRC_var,UPM1);
	#endif
//************************Data bits*******************************/
	#if (N_DATA_BITS==_5_DATA_BITS)
	ClearBit(UCSRC_var,UCSZ0);
	ClearBit(UCSRC_var,UCSZ1);
	ClearBit(UCSRC_var,UCSZ2);
	#elif (N_DATA_BITS==_6_DATA_BITS)
	SetBit(UCSRC_var,UCSZ0);
	ClearBit(UCSRC_var,UCSZ1);
	ClearBit(UCSRC_var,UCSZ2);
    #elif (N_DATA_BITS==_7_DATA_BITS)
    ClearBit(UCSRC_var,UCSZ0);
    SetBit(UCSRC_var,UCSZ1);
    ClearBit(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_8_DATA_BITS)
	SetBit(UCSRC_var,UCSZ0);
	SetBit(UCSRC_var,UCSZ1);
	ClearBit(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_9_DATA_BITS)
	SetBit(UCSRC_var,UCSZ0);
	SetBit(UCSRC_var,UCSZ1);
	SetBit(UCSRB,UCSZ2);
	#endif
//************************Stop bits*******************************/
	#if (N_STOP_BITS==ONE_STOP_BIT)
	ClearBit(UCSRC_var,USBS);
	#elif (N_STOP_BITS==TWO_STOP_BIT)
	SetBit(UCSRC_var,USBS);
	#endif
//*****************set UCSRC value   *******************************/
	UCSRC=UCSRC_var;

//************************Baud rate *******************************/

    UBRR_var=BaudRateArray[SPEED_MODE][CPU_F][BUAD_RATE];
	UBRRH = (uint8)(UBRR_var>>8);
	UBRRL = (uint8)UBRR_var;

//************************Enable  *******************************/
//enable UART  receiver.
SetBit(UCSRB,RXEN);
//enable UART  transmitter .
SetBit(UCSRB,TXEN);
}
/*
void UART_Init(void)
{
	// transmission speed
	ClearBit(UCSRA,U2X);

	//enable UART  receiver.
	SetBit(UCSRB,RXEN);

	//enable UART  transmitter .
	SetBit(UCSRB,TXEN);

	//B- Bit data
	SetBit(UCSRC,UCSZ0);
	SetBit(UCSRC,UCSZ1);
	ClearBit(UCSRB,UCSZ2);

	//Async
	ClearBit(UCSRC,UMSEL);
	//NO parity
	ClearBit(UCSRC,UPM0);
	ClearBit(UCSRC,UPM1);
	// One stop bit
	ClearBit(UCSRC,USBS);



	UBRRH = 0;
	UBRRL = 51;
}
*/


/*****************************************Interrupt functions*********************************************/


 void UART_RX_InterruptEnable(void)
{
	SetBit(UCSRB,RXCIE);
}

 void UART_RX_InterruptDisable(void)
{
	ClearBit(UCSRB,RXCIE);
}

 void UART_TX_InterruptEnable(void)
{
	SetBit(UCSRB,TXCIE);
}

 void UART_TX_InterruptDisable(void)
{
	ClearBit(UCSRB,TXCIE);
}
/*****************************************Set Call Back Functions*********************************************/
 void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

 void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}
/***********************************************ISR ************************************************************/
 ISR(USART_RXC_vect)
{
	if (UART_RX_Fptr!=((void*)0))
	{
		UART_RX_Fptr();
	}
}

 ISR(USART_TXC_vect)
{
	if (UART_TX_Fptr!=((void*)0))
	{
		UART_TX_Fptr();
	}
}


/****************************************Send and receive functions with no ckecking********************************/

void UART_SendByteNoBlock(uint8 data)
{
	UDR = data;
}

uint8 UART_ReceiveByteNoBlock(void)
{
    return UDR;
}
/****************************************Send and receive functions with polling     ********************************/
void UART_SendByte(uint8 data)
{
	/*UDRE flag is set when the buffer is empty and ready
	for transmitting a new byte so wait until this flag is set to one
	and it will cleared by hardware when u write  new data to puffer.*/
	while(!(GetBit(UCSRA,UDRE)));
	UDR = data;
}

uint8 UART_ReceiveByte(void)
{
	/*RXC flag is set when the UART receive data so  wait until this flag is set to one
	and it will cleared by hardware when u read the data*/
	while(!(GetBit(UCSRA,RXC)));
    return UDR;
}



uint8 UART_Receive_NoBlock(uint8*pdata)
{
	uint8 status=0;
	if(GetBit(UCSRA,RXC))
	{
		*pdata=UDR;
		status=1;
	}
	else
	{
		status=0;
	}
return status;
}









