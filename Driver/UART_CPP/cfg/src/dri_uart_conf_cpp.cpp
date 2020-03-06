/*****************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		UART Configuration Source
* Filename:		dri_uart_conf_cpp.cpp
* Author:		HS
* Origin Date:	09/29/2019
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_uart_conf_cpp.cpp
 *  @brief:	This source file contains configuration function definitions for
 *  		UART on USIC channel
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_uart_cpp.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/* Callback handler for user */
#if ( UART_CALLBACK_HANDLER_USED == 1U )
extern void UART_callback_handler_cpp( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event );
#endif


/** Configurations for UART Channels **/
#if (UART_CHANNELS_USED > 0)


#ifdef UART_CHANNEL_2_USED
/* Reference of UART Channel 2 Data structure */
extern tStUART_Channel UART_Channel_2;
/* Global constructor fo UART Channel 2 */
static UART__ UART_Object_2( &UART_Channel_2 );
/* Global pointer to UART Channel 2 object to be used */
UART__ * p_UART_Object_2 = &UART_Object_2;
#endif

#ifdef UART_CHANNEL_3_USED
/* Reference of UART Channel 3 Data structure */
extern tStUART_Channel UART_Channel_3;
/* Global constructor fo UART Channel 3 */
static UART__ UART_Object_3( &UART_Channel_3 );
/* Global pointer to UART Channel 3 object to be used */
UART__ * p_UART_Object_3 = &UART_Object_3;
#endif

#endif	/* (UART_CHANNELS_USED > 0) */


/******************************************************************************
* Function Definitions
*******************************************************************************/


#if (defined(UART_TX_INTERRUPT_USED) ||\
	defined(UART_RX_INTERRUPT_USED) || \
	defined(UART_PROTOCOL_EVENT_USED))
extern void UART_isr_entry( void * p_channel, const eUART_InterruptOperation );
#endif


/******* ISR Handlers for UART__ 2 channel *******/
#ifdef UART_2_TX_HANDLER
/**
 * @function	UART_2_TX_HANDLER
 *
 * @brief		UART2 tx handler
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void UART_2_TX_HANDLER( void )
{
	/* Call ISR entry function */
	UART__::isr_entry( &UART_Object_2, UART_INTERRUPT_OPERATION_TX );
}
#endif	/* UART_2_TX_HANDLER */


#ifdef UART_2_RX_HANDLER
/**
 * @function	UART_2_RX_HANDLER
 *
 * @brief		UART2 rx handler
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void UART_2_RX_HANDLER( void )
{
	/* Call ISR entry function */
	UART__::isr_entry( &UART_Object_2, UART_INTERRUPT_OPERATION_RX );
}
#endif	/* UART_2_RX_HANDLER */


#ifdef UART_2_ERR_HANDLER
/**
 * @function	UART_2_ERR_HANDLER
 *
 * @brief		UART2 err handler
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void UART_2_ERR_HANDLER( void )
{
	/* Call ISR entry function */
	UART__::isr_entry( &UART_Object_2, UART_INTERRUPT_OPERATION_ERROR );
}
#endif	/* UART_2_ERR_HANDLER */


/******* ISR Handlers for UART__ 3 channel *******/
#ifdef UART_3_TX_HANDLER
/**
 * @function	UART_3_TX_HANDLER
 *
 * @brief		UART3 tx handler
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void UART_3_TX_HANDLER( void )
{
	/* Call ISR entry function */
	UART__::isr_entry( &UART_Object_3, UART_INTERRUPT_OPERATION_TX );
}
#endif	/* UART_3_TX_HANDLER */


#ifdef UART_3_RX_HANDLER
/**
 * @function	UART_3_RX_HANDLER
 *
 * @brief		UART3 rx handler
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void UART_3_RX_HANDLER( void )
{
	/* Call ISR entry function */
	UART__::isr_entry( &UART_Object_3, UART_INTERRUPT_OPERATION_RX );
}
#endif	/* UART_3_RX_HANDLER */


#ifdef UART_3_ERR_HANDLER
/**
 * @function	UART_3_ERR_HANDLER
 *
 * @brief		UART3 err handler
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void UART_3_ERR_HANDLER( void )
{
	/* Call ISR entry function */
	UART__::isr_entry( &UART_Object_3, UART_INTERRUPT_OPERATION_ERROR );
}
#endif	/* UART_3_ERR_HANDLER */


/*********************************** End of File ******************************/
