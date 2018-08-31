/* Generated by CodeDescriptor 1.5.0.0907 */
/*
* Project Name      -> XMEGA DMA
* Version           -> 1.0.0.0830
* Author            -> Hm @ Workstadion.: QP-01-02
* Build Date        -> 30.08.2018 07:06:05
* Description       -> Description
*
*
*
*/

#ifndef __XMEGA_DMA_H__
#define __XMEGA_DMA_H__

#include <avr/io.h>
#include <stdbool.h>
#include <stdlib.h>

/*	DMA Adress - Makro 
*	Umwandlung vom "C Pointer" zum "DMA Pointer"
*/
typedef uint32_t	dmaaddr_t;
typedef uint8_t		*dmabuff_t;

#define CPTR2DMA(CPTR)						( ( dmaaddr_t ) ( uintptr_t )( CPTR ) )

#define DOUBLE_BUFFERED(channel)			( dma.doubleBuffered & _BV ( ( channel ) >> 1 ) )
#define CHANNEL(channel)					( ( ( DMA_CH_t * ) &DMA.CH0 )[channel])



enum SrcReload_enum 
{
	SrcReloadNone = DMA_CH_SRCRELOAD_NONE_gc,  /* No reload */
	SrcReloadBlock = DMA_CH_SRCRELOAD_BLOCK_gc,  /* Reload at end of block */
	SrcReloadBurst = DMA_CH_SRCRELOAD_BURST_gc,  /* Reload at end of burst */
	SrcReloadTransaction = DMA_CH_SRCRELOAD_TRANSACTION_gc,  /* Reload at end of transaction */
	SrcReload_bm = SrcReloadNone | SrcReloadBlock | SrcReloadBurst | SrcReloadTransaction
};

enum DestReload_enum 
{
	DestReloadNone = DMA_CH_DESTRELOAD_NONE_gc,  /* No reload */
	DestReloadBlock = DMA_CH_DESTRELOAD_BLOCK_gc,  /* Reload at end of block */
	DestReloadBurst = DMA_CH_DESTRELOAD_BURST_gc,  /* Reload at end of burst */
	DestReloadTransaction = DMA_CH_DESTRELOAD_TRANSACTION_gc,  /* Reload at end of transaction */
	DestReload_bm = DestReloadNone | DestReloadBlock | DestReloadBurst | DestReloadTransaction
};

enum SrcDirection_enum 
{
	SrcDirectionFixed = DMA_CH_SRCDIR_FIXED_gc,  /* Fixed */
	SrcDirectionInc = DMA_CH_SRCDIR_INC_gc,  /* Increment */
	SrcDirectionDec = DMA_CH_SRCDIR_DEC_gc,  /* Decrement */
	SrcDirection_bm = SrcDirectionFixed | SrcDirectionInc | SrcDirectionDec
};

enum DestDirection_enum 
{
	DestDirectionFixed = DMA_CH_DESTDIR_FIXED_gc,  /* Fixed */
	DestDirectionInc = DMA_CH_DESTDIR_INC_gc,  /* Increment */
	DestDirectionDec = DMA_CH_DESTDIR_DEC_gc,  /* Decrement */
	DestDirection_bm = DestDirectionFixed | DestDirectionInc | DestDirectionDec
};

enum BurstLength_enum 
{
	BurstLength1Byte = DMA_CH_BURSTLEN_1BYTE_gc,  /* 1-byte burst mode */
	BurstLength2Byte = DMA_CH_BURSTLEN_2BYTE_gc,  /* 2-byte burst mode */
	BurstLength4Byte = DMA_CH_BURSTLEN_4BYTE_gc,  /* 4-byte burst mode */
	BurstLength8Byte = DMA_CH_BURSTLEN_8BYTE_gc,  /* 8-byte burst mode */
	BurstLength_bm = BurstLength1Byte | BurstLength2Byte | BurstLength4Byte | BurstLength8Byte
};

typedef struct 
{
	uint8_t		usedChannels;
	uint8_t		doubleBuffered;
	uint8_t		autoDestBuffer;
	uint16_t	blockSizes[4];
	dmabuff_t	buffer[4];
}dma_t;
extern dma_t dma;


static inline void dmaSetChannel( uint8_t channel )
{
	dma.usedChannels |= _BV( channel );
}


uint8_t*	dmaUpdateAutoBuffer			( uint8_t channel , uint16_t blockSize );	

void		dmaSetBuffer				( uint8_t channel );							

void		dmaReset					( void );									

void		dmaSetBlockSize				( uint8_t channel , uint16_t blockSize );	

void		dmaUseChannel				( uint8_t channel , uint8_t use );			

void		dmaSetSrcCh					( uint8_t channel , void *source );			

void		dmaSetSrcChDir				( uint8_t channel , void *source , enum SrcDirection_enum direction , enum SrcReload_enum mode ); 

void		dmaSetSrcChDirDblBuff		( uint8_t channel , void *source1 , void *source2 , enum SrcDirection_enum direction , enum SrcReload_enum mode ); 

void		dmaSetSrcDir				( uint8_t channel , enum SrcDirection_enum direction );	

void		dmaSetSrcReload				( uint8_t channel , enum SrcReload_enum mode );			

void		*dmaSetManualDest			( uint8_t channel , void *destination );				

void		*dmaSetDestChDir			( uint8_t channel , void *destination , enum DestDirection_enum direction, enum DestReload_enum mode);						

void		dmaSetDestChDirDblBuff		( uint8_t channel , void *destination1 , void *destination2, enum DestDirection_enum direction, enum DestReload_enum mode); 

void		dmaSetDestDir				( uint8_t channel , enum DestDirection_enum direction);		

void		dmaSetDestReload			( uint8_t channel , enum DestReload_enum mode );				

void		dmaSetBurstLength			( uint8_t channel , enum BurstLength_enum burstLength );		

void		dmaEnableChannel			( uint8_t channel );			

void		dmaDisableChannel			( uint8_t channel );			

bool		dmaIsTransactionComplete	( uint8_t channel );			

bool		dmaIsBlockTransferBusy		( uint8_t channel );			

void		dmaTrigger					( uint8_t channel );			

bool		dmaGetFreeChannel			( uint8_t channel );		

bool		dmaCopySyncron				( void *source , void *destination , uint16_t size );					

bool		dmaCopyAsychron				( uint8_t channel , void *source , void *destination , uint16_t size );	

bool		dmaFillMemory				( void *destination , uint16_t size , uint8_t byte );					

void		dmaSetRepeatCount			( uint8_t channel , uint8_t repeatCount );		

void		dmaSetSingleShot			( uint8_t channel , bool use );					

void		dmaSetTriggerSource			( uint8_t channel , uint8_t triggerSource );		



#endif