/* Generated by CodeDescriptor 1.5.0.0907 */
/*
* Project Name      -> ATxmegaA3BU Xplained Board
* Version           -> 1.0.0.0905
* Author            -> Hm @ Workstadion.: QP-01-02
* Build Date        -> 05.09.2018 07:46:44
* Description       -> Board Beschreibungen
*
*
*
*/

#ifndef __XMEGA_A3BU_XPLAINED_H__
#define __XMEGA_A3BU_XPLAINED_H__


#include <avr/io.h>



/*	Power LED
*/
#define _XMEGA_A3BU_LED_POWER_CNFG_OUT_			PORTD.DIRSET = 1<<5
#define _XMEGA_A3BU_LED_POWER_ON_				PORTD.OUTCLR = 1<<5
#define _XMEGA_A3BU_LED_POWER_OFF_				PORTD.OUTSET = 1<<5

/*	Status LED
*/
#define _XMEGA_A3BU_LED_STATUS_CNFG_OUT_		PORTD.DIRSET = 1<<4
#define _XMEGA_A3BU_LED_STATUS_ON_				PORTD.OUTCLR = 1<<4		
#define _XMEGA_A3BU_LED_STATUS_OFF_				PORTD.OUTSET = 1<<4		

/*	LED0
*/
#define _XMEGA_A3BU_LED0_CNFG_OUT_				PORTR.DIRSET = 1<<0
#define _XMEGA_A3BU_LED0_ON_					PORTR.OUTCLR = 1<<0
#define _XMEGA_A3BU_LED0_OFF_					PORTR.OUTSET = 1<<0

/*	LED1
*/
#define _XMEGA_A3BU_LED1_CNFG_OUT_				PORTR.DIRSET = 1<<1
#define _XMEGA_A3BU_LED1_ON_					PORTR.OUTCLR = 1<<1
#define _XMEGA_A3BU_LED1_OFF_					PORTR.OUTSET = 1<<1

/*	GLCD Backlight
*/
#define _XMEGA_A3BU_GLCD_BACKLIGHT_CNFG_OUT_	PORTE.DIRSET = 1<<4
#define _XMEGA_A3BU_GLCD_BACKLIGHT_ON_			PORTE.OUTSET = 1<<4
#define _XMEGA_A3BU_GLCD_BACKLIGHT_OFF_			PORTE.OUTCLR = 1<<4
#define _XMEGA_A3BU_GLCD_BACKLIGHT_TOGGLE_		PORTE.OUTTGL = 1<<4
/*...*/

/*	GLCD I/O�s
*/
#define _XMEGA_A3BU_GLCD_MOSI_PORT_				PORTD
#define _XMEGA_A3BU_GLCD_SCK_PORT_				PORTD
#define _XMEGA_A3BU_GLCD_REGISTER_SELECT_PORT_	PORTD
#define _XMEGA_A3BU_GLCD_SLAVE_SELECT_PORT_		PORTF
#define _XMEGA_A3BU_GLCD_RESET_PORT_			PORTA

#define _XMEGA_A3BU_GLCD_MOSI_bp_				3 
#define _XMEGA_A3BU_GLCD_SCK_bp_				1 
#define _XMEGA_A3BU_GLCD_REGISTER_SELECT_bp_	0 
#define _XMEGA_A3BU_GLCD_SLAVE_SELECT_bp_		3 
#define _XMEGA_A3BU_GLCD_RESET_bp_				3 

#define _XMEGA_A3BU_GLCD_CNFG_OUT_				_XMEGA_A3BU_GLCD_MOSI_PORT_.DIRSET				= 1<<_XMEGA_A3BU_GLCD_MOSI_bp_;\
												_XMEGA_A3BU_GLCD_SCK_PORT_.DIRSET				= 1<<_XMEGA_A3BU_GLCD_SCK_bp_;\
												_XMEGA_A3BU_GLCD_REGISTER_SELECT_PORT_.DIRSET	= 1<<_XMEGA_A3BU_GLCD_REGISTER_SELECT_bp_;\
												_XMEGA_A3BU_GLCD_SLAVE_SELECT_PORT_.DIRSET		= 1<<_XMEGA_A3BU_GLCD_SLAVE_SELECT_bp_;\
												_XMEGA_A3BU_GLCD_RESET_PORT_.DIRSET				= 1<<_XMEGA_A3BU_GLCD_RESET_bp_;	
													
											



#endif //__XMEGA_A3BU_XPLAINED_H__