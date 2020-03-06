/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Peripherals Hooks Source
* Filename:		peripherals_hooks.c
* Author:		HS
* Origin Date:
* Version:
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	peripherals_hooks.c
 *  @brief:	This source file contains callback functions for peripherals
 */


/******************************************************************************
* Includes
*******************************************************************************/

#include <dri_uart_extern.h>

#include <dri_spi_extern.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Functions
*******************************************************************************/

#if (UART_CALLBACK_HANDLER_USED == 1U)
/* UART Callback handler */
void UART_callback_handler( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event );
void UART_callback_handler( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event )
{
	/* Local variables */
	unsigned char * p_data_l = p_data;

	/* Check events */
	switch( event )
	{
		default:
		case UART_EVENT_TX_COMPLETE:
			break;

		case UART_EVENT_RX_COMPLETE:
			break;
		case UART_EVENT_RX_CHAR:
			switch( channel )
			{
			default:
				case UART_CHANNEL_4:
				/* Reception successfull, transmit received data */
				UART_transmit( &UART_Channel_4, p_data_l, 1 );
				break;
			}

			break;
	}
}
#endif	/* UART_CALLBACK_HANDLER_USED */


/* Callback handler for user */
#if (SPI_CALLBACK_HANDLER_USED == 1U)
void SPI_callback_handler( void * p_channel, void * p_data, const eSPI_Events event );
void SPI_callback_handler( void * p_channel, void * p_data, const eSPI_Events event )
{
	(void) p_channel;
	(void) p_data;
	(void) event;
}
#endif


/********************************** End of File *******************************/
