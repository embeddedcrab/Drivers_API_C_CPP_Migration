/*****************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		SPI Configuration Source
* Filename:		dri_spi_conf.c
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_spi_conf.c
 *  @brief:	This source file contains configuration function definitions for SPI
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_spi.h>


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
* Private Function Declarations
*******************************************************************************/

extern void SPI_isr_entry( void * p_channel, const eSPI_InterruptOperation type );


/******************************************************************************
* Variables
*******************************************************************************/

/* Callback handler for user */
#if (SPI_CALLBACK_HANDLER_USED == 1U)
extern void SPI_callback_handler( void * p_channel, void * p_data, const eSPI_Events event );
#endif


/*
 * @brief	SPI API functions
 *
 * \par<b>Description:</b><br>
 * 			This is data structure for SPI API functions to be used by Application
 */
tStSPI_MasterApi SPI0_Channel0_API =
{
	.fp_init = &SPI_Master_init,
	.fp_set_slave = &SPI_Master_set_slave,
	.fp_slave_select = &SPI_Master_slave_select,
	.fp_set_mode = &SPI_Master_set_mode,
	.fp_set_data_size = &SPI_Master_set_data_size,
	.fp_set_speed = &SPI_Master_set_speed,
	.fp_write = &SPI_Master_transmit,
	.fp_read = &SPI_Master_receive,
	.fp_abort = &SPI_Master_abort
};


/** SPI Channels Configurations **/

#if (SPI0_CHANNEL0_USED == 1U)
/* SPI 0 Channel 0 Data structure */
static XMC_SPI_CH_CONFIG_t SPI0_Channel0_ChannelConfiguration =
{
	.baudrate = 30000000,
	.bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
	.parity_mode = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
	.selo_inversion = XMC_USIC_CH_PARITY_MODE_NONE
};

static tStSPI_FIFO_Configuartion SPI0_Channel0_FifoConfiguration =
{
	.tx_fifo_size = XMC_USIC_CH_FIFO_SIZE_64WORDS,
	.rx_fifo_size = XMC_USIC_CH_FIFO_SIZE_64WORDS
};

static tStSPI_InterruptConfiguartion SPI0_Channel0_Transmit_InterruptConfiguration =
{
	.irq = { .irq_num = USIC0_0_IRQn, .irq_priority = 52 },
	.sr = SPI0_CHANNEL0_TX_SR
};

static tStSPI_InterruptConfiguartion SPI0_Channel0_Receive_InterruptConfiguration =
{
	.irq = { .irq_num = USIC0_1_IRQn, .irq_priority = 51 },
	.sr = SPI0_CHANNEL0_RX_SR
};

#if (SPI_PROTOCOL_EVENTS_USED == 1U)
static tStSPI_InterruptConfiguartion SPI0_Channel0_Protocol_InterruptConfiguration =
{
	.irq = { .irq_num = USIC0_2_IRQn, .irq_priority = 52 },
	.sr = SPI0_CHANNEL0_EVENT_SR
};
#endif	/* SPI_PROTOCOL_EVENTS_USED */

tStSPI_MasterConfiguartion SPI0_Channel0_Configuration =
{
	.p_channel_context = XMC_SPI0_CH0,
	.p_channel_config = &SPI0_Channel0_ChannelConfiguration,
	.p_fifo_config = &SPI0_Channel0_FifoConfiguration,
	.tx_isr_config = &SPI0_Channel0_Transmit_InterruptConfiguration,
	.rx_isr_config = &SPI0_Channel0_Receive_InterruptConfiguration,
	#if (SPI_PROTOCOL_EVENTS_USED == 1U)
	.protocol_isr_config = &SPI0_Channel0_Protocol_InterruptConfiguration,
	#endif
	.word_length = 8,
	.frame_length = 8,
	.input_pin_source = 1,
	.bit_order = SPI_BIT_ORDER_MSB_FIRST,
	.input_pin = XMC_SPI_CH_INPUT_DIN0,
	.channel_mode = XMC_SPI_CH_MODE_STANDARD
};

tStSPI_MasterControl SPI0_Channel0_Control;

#if (SPI_CALLBACK_HANDLER_USED == 1U)
tStSPI_MasterCallbacks SPI0_Channel0_Callback =
{
	.fp_callback = &SPI_callback_handler
};
#endif
#endif	/* SPI0_CHANNEL0_USED */


/*****************************************************************************/


/** Global Handle for SPI Channels **/
#if (SPI0_CHANNEL0_USED == 1U)
tStSPI_Master SPI0_Channel0_Handle =
{
	.p_config = &SPI0_Channel0_Configuration,
	.p_control = &SPI0_Channel0_Control
	#if (SPI_CALLBACK_HANDLER_USED == 1U)
	,.p_callback = &SPI0_Channel0_Callback
	#endif
};
#endif


/******************************************************************************
* Function Definitions
*******************************************************************************/

/******* ISR Handlers for SPI channel *******/

/* Channels ISR Entries */
#if ( SPI0_CHANNEL0_USED == 1U )

void SPI0_Channel0_Transmit_Handler( void )
{
	SPI_isr_entry( &SPI0_Channel0_Handle, SPI_INTERRUPT_OPERATION_TX );
}

void SPI0_Channel0_Receive_Handler( void )
{
	SPI_isr_entry( &SPI0_Channel0_Handle, SPI_INTERRUPT_OPERATION_RX );
}

#if (SPI_PROTOCOL_EVENTS_USED == 1U)
void SPI0_Channel0_Protocol_Handler( void )
{
	SPI_isr_entry( &SPI0_Channel0_Handle, SPI_INTERRUPT_PROTOCOl_ERROR );
}
#endif	/* SPI_PROTOCOL_EVENTS_USED */

#endif	/* SPI0_CHANNEL0_USED */


/*********************************** End of File ******************************/
