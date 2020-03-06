/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Main Source
* Filename:		main.cpp
* Author:		HS
* Origin Date:
* Version:
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	main.cpp
 *  @brief:	This source file contains main function entry with
 *  		Exception handlers and callback functions
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include Application Headers */
#include <led_task.hpp>

/* Include peripheral device files */
#include <dri_gpio_pins.h>
#include <dri_uart_extern.h>
#include <dri_uart_cpp_extern.h>

/* Include RTOS files */
#include <dri_mem.h>
#include <rtos_wrappers.h>

/* Include server task headers */
#include <server_task.h>
#include <client_task.h>

/* Include application headers */
#include <logger.h>
#include <external_flash.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/

#define FREERTOS_TCP_CLIENT


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Functions
*******************************************************************************/

/* Extern "C" block for C variables
 *
 * C Linkage in CPP Application
 * */
#ifdef __cplusplus
extern "C"
{

#define EXCEPTION_HANDLER_DEBUG_ON

/******* User defined initialization functions *******/

void init_user_before_main( void );

/* Exception Handling functions */
#ifdef EXCEPTION_HANDLER_DEBUG_ON
void get_registers_from_stack( unsigned long *pulFaultStackAddress );
void BusFault_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void UsageFault_Handler(void);
#endif

}
#endif	/* __cplusplus */


/*****************************************************************************/


/**
 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point.
 * It is invoked by the device startup code.
 */
int main(void)
{
	/* Task Parameters Variable */
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wwrite-strings"
	TaskCreationParams TaskParams = {"LED_TASK", configMINIMAL_STACK_SIZE, 1 };
	#pragma GCC diagnostic pop

	/* The MAC address array is not declared const as the MAC address will
	 * normally be read from an EEPROM and not hard coded (in real deployed
	 * applications) or read using HAL API from ETH MAC */
	static uint8_t ucMACAddress[ 6 ] = { 0x00U, 0x03U, 0x19U, 0x45U, 0x00, 0x00 };

	/* Define the network addressing.  These parameters will be used if either
	 * ipconfigUDE_DHCP is 0 or if ipconfigUSE_DHCP is 1 but DHCP auto configuration failed. */
	static const uint8_t ucIPAddress[ 4 ] = { 192, 168, 1, 9 };
	static const uint8_t ucNetMask[ 4 ] = { 255, 255, 255, 0 };
	static const uint8_t ucGatewayAddress[ 4 ] = { 192, 168, 1, 1 };
	/* The following is the address of an OpenDNS server. */
	static const uint8_t ucDNSServerAddress[ 4 ] = { 208, 67, 222, 222 };

    /* Hardware peripherals fucnioning test */
    const unsigned char *p_data_l = (const unsigned char *)"Hello Embedded World\r\n";
	/* Send data to UART Channel */
    p_UART_Object_3->transmit( p_data_l, strlen((const char *)p_data_l) );
	UART_transmit( &UART_Channel_4, p_data_l, strlen((const char *)p_data_l) );

	logger << "Hello I am your Logger" << logger.endl;

	/* Create LED tasks
	 *
	 * <i>Imp Note:</i>
	 * Application task creation shall be done using new while creating objects
	 * otherwise Bus Fault Exception will come!!
	 * */
	LedTask__ * LedTask = new LedTask__( XMC_GPIO_PORT1 , 0, &TaskParams );
	LedTask->xvinit();
	
	/* Initialize the RTOS’s TCP/IP stack.  The tasks that use the network
	 * are created in the vApplicationIPNetworkEventHook() hook function below.
	 * The hook function is called when the network connects. */
	BaseType_t xReturn = FreeRTOS_IPInit( ucIPAddress, ucNetMask, ucGatewayAddress, ucDNSServerAddress, ucMACAddress );

	/* Check IP Init status */
	if( xReturn == pdPASS )
	{
		/* Create Server Handler task */
		ServerTask__ server( ipconfigIP_TASK_PRIORITY, configMINIMAL_STACK_SIZE );//-1

		#if defined(FREERTOS_TCP_CLIENT)
		ClientTask__ client( ipconfigIP_TASK_PRIORITY - 1, configMINIMAL_STACK_SIZE );
		#endif

		/* Start Task Scheduler */
		vTaskStartScheduler();

		for( ; ; )
		{
		}
	}
	else
	{
		/* Could not initialize Network, shall hang N/W related tasks */
		while(1U)
		{
			;
		}
	}

	return 0;
}


/******************************************************************************/


/** Exception Handler functions for debugging and tracing **/

#ifdef EXCEPTION_HANDLER_DEBUG_ON

void get_registers_from_stack( unsigned long *pulFaultStackAddress )
{
	/* These are volatile to try and prevent the compiler/linker optimizing them
	 away as the variables never actually get used.  If the debugger won't show the
	 values of the variables, make them global my moving their declaration outside
	 of this function. */
	volatile uint32_t r0;
	volatile uint32_t r1;
	volatile uint32_t r2;
	volatile uint32_t r3;
	volatile uint32_t r12;
	volatile uint32_t lr;	/**< Link register. */
	volatile uint32_t pc;	/**< Program counter. */
	volatile uint32_t psr;	/**< Program status register. */

	/* Assign Register values into local variables */
	r0 = pulFaultStackAddress[0];
	r1 = pulFaultStackAddress[1];
	r2 = pulFaultStackAddress[2];
	r3 = pulFaultStackAddress[3];

	r12 = pulFaultStackAddress[4];
	lr = pulFaultStackAddress[5];
	pc = pulFaultStackAddress[6];
	psr = pulFaultStackAddress[7];

	/* When the following line is hit, the variables contain the register values. */
	for( ; ; );

	/* Avoid compiler warnings */
	(void) r0; (void) r1; (void) r2; (void) r3; (void) r12;
	(void) lr; (void) pc; (void) psr;
}

#endif	/* EXCEPTION_HANDLER_DEBUG_ON */

void BusFault_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
	__asm volatile
	(
			" tst lr, #4                                                \n"
			" ite eq                                                    \n"
			" mrseq r0, msp                                             \n"
			" mrsne r0, psp                                             \n"
			" ldr r1, [r0, #24]                                         \n"
			" ldr r2, bus_fault_handler_address_const                   \n"
			" bx r2                                                     \n"
			" bus_fault_handler_address_const: .word get_registers_from_stack    \n"
	);
#endif
	for( ; ; );
}

void HardFault_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
	__asm volatile
	(
			" tst lr, #4                                                \n"
			" ite eq                                                    \n"
			" mrseq r0, msp                                             \n"
			" mrsne r0, psp                                             \n"
			" ldr r1, [r0, #24]                                         \n"
			" ldr r2, hard_fault_handler_address_const                  \n"
			" bx r2                                                     \n"
			" hard_fault_handler_address_const: .word get_registers_from_stack    \n"
	);
	for( ; ; );
#endif	/* EXCEPTION_HANDLER_DEBUG_ON */
}

void MemManage_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
    __asm volatile
        (
         " tst lr, #4                                                \n"
         " ite eq                                                    \n"
         " mrseq r0, msp                                             \n"
         " mrsne r0, psp                                             \n"
         " ldr r1, [r0, #24]                                         \n"
         " ldr r2, mem_manage_handler_address_const                  \n"
         " bx r2                                                     \n"
         " mem_manage_handler_address_const: .word get_registers_from_stack    \n"
        );
#endif	/* EXCEPTION_HANDLER_DEBUG_ON */
    for( ; ; );
}


void UsageFault_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
    __asm volatile
        (
         " tst lr, #4                                                \n"
         " ite eq                                                    \n"
         " mrseq r0, msp                                             \n"
         " mrsne r0, psp                                             \n"
         " ldr r1, [r0, #24]                                         \n"
         " ldr r2, usage_fault_handler_address_const                  \n"
         " bx r2                                                     \n"
         " usage_fault_handler_address_const: .word get_registers_from_stack    \n"
        );
#endif	/* EXCEPTION_HANDLER_DEBUG_ON */
    for( ; ; );
}


/* Extern "C" block for C Functions */
/** User defined functions **/
extern "C" void init_user_before_main( void )
{
	/** Initialize GPIO Pin functionalities **/
	extern void gpio_init_c( void );
	gpio_init_c();

	/** Initialize Peripherals **/
	/* Initialize UART Channels */
	p_UART_Object_2->init( 1 );
	p_UART_Object_3->init( 1 );
	UART_init( &UART_Channel_4, 1 );

	/* Initialize SPI Channels */
	SPI0_Channel0_API.fp_init( &SPI0_Channel0_Handle, 1 );

	/* Initialize Ethernet MAC */
	extern void initialize_ethernet_mac( void );	/* MAC Initialization function */
	initialize_ethernet_mac();

	/** Initialize Devices **/
	/* Initialize External Flash */
	ext_flash.init( 1 );	/* TODO: Not tested fully, shared for design */
}


/********************************** End of File *******************************/
