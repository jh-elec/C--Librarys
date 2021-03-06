/* Generated by Header_Generator V1.0 */ 

/*
* Project Name -> Portexpander - MCP23017
* Version      -> 1.0 
* Author       -> Hm
* Build Date   -> 24.04.2017
* Description  -> Driver Header
*				  
*				  
*				  
*/		

#ifndef __MCP23017_H__
#define __MCP23017_H__


#define MCP23017_ADDR		0x40

enum state
{
	BIT_RESET,
	BIT_SET,	
};

enum __attribute__((packed)) eMcp23017Regs
{
	IODIRA 		=	0x00,
	IODIRB 		=	0x01,
	IPOLA 		=	0x02,
	IPOLB 		=	0x03,
	GPINTENA 	=	0x04,
	GPINTENB 	=	0x05,
	DEFVALA 	=	0x06,
	DEFVALB 	=	0x07,
	INTCONA 	=	0x08,
	INTCONB 	=	0x09,
	IOCON	 	=	0x0A,
	IOCONx 		=	0x0B,
	GPPUA 		=	0x0C,
	GPPUB 		=	0x0D,
	INTFA 		=	0x0E,
	INTFB 		=	0x0F,
	INTCAPA 	=	0x10,
	INTCAPB 	=	0x11,
	GPIOA 		=	0x12,
	GPIOB 		=	0x13,
	OLATA 		=	0x14,
	OLATB 		=	0x15,
};

void Mcp23017Init( uint8_t uiCnfgA , uint8_t uiCnfgB );

void Mcp23017SetGPA(uint8_t cmd);

void Mcp23017SetGPB(uint8_t cmd);

#endif // __MCP23017_H__