/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		UART API Header
* Filename:		dri_uart.h
* Author:		HS
* Origin Date:	09/29/2019
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_uart.h
 *  @brief:	This file contains API function declarations
 *  		for UART on USIC channel
 */
#ifndef DRI_UART_CPP_H_
#define DRI_UART_CPP_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_uart_types.h>


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


/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
 *
 * @brief	UART Class
 *
 ******************************************************************************/

/* Check UART Usage in system */
#if( UART_CHANNELS_USED > 0 )

class UART__
{
/* public members */
public:
	/** Constructors and Destructors */
	explicit UART__( void * p_channel ) : p_handle_( p_channel )
	{
		/* Check channel pointer should not be NULL */
		if( nullptr == p_channel )
		{
			for( ; ; );
		}
		else
		{
			/* Update the callback handler */
			((tStUART_Channel*)p_handle_)->p_callback->fp_callback = &UART_callback_handler_cpp;
			/* Can do other tasks */
		}
	}

	/* Destructor for class */
	~UART__()
	{
		/* Close UART channel */
		init( 0 );
	}

	UART__( const UART__& ) = delete;
	UART__ operator=( const UART__& ) = delete;

	/******* Data Members *******/

	/******* API Member functions *******/

	/**
	 * @function	init
	 *
	 * @brief		Initialization function for UART channel
	 *
	 * @param[in]	init	-	initialization state
	 * 							eUART_Init_	-	UART_INIT_OPEN
	 * 											UART_INIT_CLOSE
	 *
	 * @param[out]	NA
	 *
	 * @return  	eUART_Status_
	 *          	UART_STATUS_SUCCESS:	Operation successful.<BR>
	 *          	UART_STATUS_FAILED:		Operation failed.<BR>
	 *
	 * \par<b>Description:</b><br>
	 * 				This function will initialize UART channel
	 * 				with required parameters for operation
	 *
	 * <i>Imp Note:</i>
	 *
	 */
	long init( const unsigned char& init );

	/**
	 * @function	set_baudrate
	 *
	 * @brief		Set baudrate function
	 *
	 * @param[in]	speed	-	speed of operation of UART
	 *
	 * @param[out]	NA
	 *
	 * @return  	eUART_Status_
	 *          	UART_STATUS_SUCCESS:	Operation successful.<BR>
	 *          	UART_STATUS_FAILED:		Operation failed.<BR>
	 *
	 * \par<b>Description:</b><br>
	 * 				This function will set baud rate for a particular channel
	 *
	 * <i>Imp Note:</i>
	 *
	 */
	long set_baudrate( const unsigned long& speed );

	/**
	 * @function	transmit
	 *
	 * @brief		Registers as request for data transmission
	 *
	 * @param[in]	p_src	-	source data pointer
	 * 				length	-	length of source data
	 *
	 * @param[out]	NA
	 *
	 * @return  	eUART_Status
	 *          	UART_STATUS_SUCCESS:	Operation successful.<BR>
	 *          	UART_STATUS_FAILED:		Operation failed.<BR>
	 *
	 * \par<b>Description:</b><br>
	 * 				This function transmit data using interrupt functionality
	 *
	 * <i>Imp Note:</i>
	 * 				This function can have functionality of waiting as used
	 * 				in Polling of transmission data
	 *
	 */
	long transmit( const unsigned char * p_src, const unsigned long& length = 1 );

	/**
	 * @function	receive
	 *
	 * @brief		Registers a request for data reception
	 *
	 * @param[in]	p_dest	-	destination data pointer
	 * 				length	-	length of data to be received
	 *
	 * @param[out]	p_dest	-	destination data
	 *
	 * @return		eUART_Status
	 *          	UART_STATUS_SUCCESS:	Operation successful.<BR>
	 *          	UART_STATUS_FAILED:		Operation failed.<BR>
	 *
	 * \par<b>Description:</b><br>
	 * 				This function will receive data from UART channel
	 *
	 * <i>Imp Note:</i>
	 * 				This function can have functionality of waiting as used in
	 * 				Polling for receive data
	 *
	 */
	long receive( unsigned char * const p_dest, const unsigned long& length = 1 );

	/**
	 * @function	abort
	 *
	 * @brief		Data abort function
	 *
	 * @param[in]	tx_rx	-	abort state for Tx/Rx
	 * 							eUART_Abort_	-	UART_ABORT_TX
	 * 												UART_ABORT_RX
	 * 												UART_ABORT_TX_RX
	 *
	 * @param[out]	NA
	 *
	 * @return  	eUART_Status
	 *          	UART_STATUS_SUCCESS:	Operation successful.<BR>
	 *          	UART_STATUS_FAILED:		Operation failed.<BR>
	 *
	 * \par<b>Description:</b><br>
	 *
	 * <i>Imp Note:</i>
	 *
	 */
	long abort( const unsigned char& tx_rx );


	/* ISR entry function for UART__ class */
	#if (defined(UART_TX_INTERRUPT_USED) ||	\
		defined(UART_RX_INTERRUPT_USED) ||	\
		defined(UART_PROTOCOL_EVENT_USED))
	static void isr_entry( UART__* p_object, const eUART_InterruptOperation_& type )
	{
		switch( type )
		{
			default:/* Considering all cases in default */
			#ifdef UART_TX_INTERRUPT_USED
			case eUART_InterruptOperation_::UART_INTERRUPT_OPERATION_TX:
				p_object->tx_isr_entry();
				break;
			#endif
			#ifdef UART_RX_INTERRUPT_USED
			case eUART_InterruptOperation_::UART_INTERRUPT_OPERATION_RX:
				p_object->rx_isr_entry();
				break;
			#endif
			#ifdef UART_PROTOCOL_EVENT_USED
			case eUART_InterruptOperation_::UART_INTERRUPT_OPERATION_ERROR:
				p_object->err_isr_entry();
				break;
			#endif
		}
	}
	#endif	/* ISR Handler functions. UART_TX_INTERRUPT_USED,
				UART_RX_INTERRUPT_USED, UART_PROTOCOL_EVENT_USED */


/* private members */
private:
	/******* Private Member Functions *******/
	eUART_Channel get_channel( void ) const;
	void calc_fifo( unsigned long (&fifo_size_arr)[2] );
	void reconfigure_rx_fifo( const unsigned long& data_size ) const;

	/* ISR Handler functions */
	#ifdef UART_TX_INTERRUPT_USED
	void tx_isr_entry( void );
	#endif

	#ifdef UART_RX_INTERRUPT_USED
	void rx_isr_direct( void );
	void rx_isr_entry( void );
	#endif

	#ifdef UART_PROTOCOL_EVENT_USED
	void err_isr_entry( void );
	#endif

/* protected members, if any */
protected:
	/* pointer to handle of UART channel */
	void * p_handle_;
};

#endif	/* UART_CHANNELS_USED */


#endif /* DRI_UART_CPP_H_ */

/********************************** End of File *******************************/
