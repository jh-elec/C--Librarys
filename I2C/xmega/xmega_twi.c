/* Generated by CodeDescriptor 1.0.0.0 */
/*
* Project Name      -> xMEGA TWI (I2C)
* Version           -> 1.0
* Author            -> Hm @ Workstadion.: QP-01-02
* Build Date        -> 15.05.2017 16:18:16
* Description       -> Routines for TWI Handling
*
*
*
*/
#include <avr/io.h>
#include "xmega_twi.h"


uint32_t tmeout = 0;

void twi_init(TWI_t * twiname)
{			
	twiname->MASTER.CTRLB	= TWI_MASTER_SMEN_bm;
	twiname->MASTER.BAUD	= TWI_BAUDSETTING;
	twiname->MASTER.CTRLA	= TWI_MASTER_ENABLE_bm;
	twiname->MASTER.STATUS	= TWI_MASTER_BUSSTATE_IDLE_gc;
}

void twi_write(TWI_t *twi, uint8_t reg, uint8_t data)
{
	twi->MASTER.ADDR   = (SLAVE_ADDRESS<<1);
	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));

	twi->MASTER.DATA   = reg;
	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));

	twi->MASTER.DATA   = data;
	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));
	
	twi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
}

uint8_t twi_read(TWI_t *twi, uint8_t reg)
{
	uint8_t ret=0;
	
	twi->MASTER.ADDR = ((SLAVE_ADDRESS<<1));
	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));
 
	twi->MASTER.DATA = reg;
	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));
 
	twi->MASTER.ADDR = ((SLAVE_ADDRESS<<1)|0x01);

	while(!(twi->MASTER.STATUS & TWI_MASTER_RIF_bm));
	ret = twi->MASTER.DATA;
 
	twi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;

	return ret;
}

void twi_reads(TWI_t *twi, uint8_t reg, uint8_t numb, uint8_t *buff)
{ 	
 	twi->MASTER.ADDR = ((SLAVE_ADDRESS<<1));
 	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));
 	
 	twi->MASTER.DATA = reg;
 	while(!(twi->MASTER.STATUS&TWI_MASTER_WIF_bm));
 	
 	twi->MASTER.ADDR = ((SLAVE_ADDRESS<<1)|0x01);
 		
	for (uint8_t BytesReaded=0;BytesReaded<numb;BytesReaded++)
	{	
		
		twi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
		while(!(twi->MASTER.STATUS & TWI_MASTER_RIF_bm));
		*buff++ = twi->MASTER.DATA;	
	 }

 	twi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
}