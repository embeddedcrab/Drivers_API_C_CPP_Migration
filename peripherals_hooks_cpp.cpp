/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Peripherals Hooks Source
* Filename:		peripherals_hooks_cpp.cpp
* Author:		HS
* Origin Date:
* Version:
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	peripherals_hooks_cpp.cpp
 *  @brief:	This source file contains callback functions for peripherals
 */


/******************************************************************************
* Includes
*******************************************************************************/

#include <dri_uart_cpp_extern.h>


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
void UART_callback_handler_cpp( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event );
void UART_callback_handler_cpp( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event )
{
	/* Local variables */
	unsigned char * p_data_l = p_data;

	/* Check events */
	switch( event )
	{
		default:
		case UART_EVENT_TX_COMPLETE:
			switch( channel )
			{
			default:
				case UART_CHANNEL_2:
				break;
				case UART_CHANNEL_3:
					break;
			}
			break;
		case UART_EVENT_RX_COMPLETE:
			switch( channel )
			{
			default:
				case UART_CHANNEL_2:
				break;
				case UART_CHANNEL_3:
					break;
			}
			break;
		case UART_EVENT_RX_CHAR:
			switch( channel )
			{
			default:
				case UART_CHANNEL_2:
				/* Reception successfull, transmit received data */
				p_UART_Object_2->transmit( p_data_l, 1 );
				break;
				case UART_CHANNEL_3:
				/* Reception successfull, transmit received data */
				p_UART_Object_3->transmit( p_data_l, 1 );
				break;
			}

			break;
	}
}
#endif	/* UART_CALLBACK_HANDLER_USED */


/********************************** End of File *******************************/
