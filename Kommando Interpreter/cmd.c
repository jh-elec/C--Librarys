/* Generated by CodeDescriptor 1.5.0.0907 */
/*
* Project Name      -> Kommando Interpreter
* Version           -> 1.0.1.1124
* Author            -> Hm @ Workstadion.: QP-01-02
* Build Date        -> 20.09.2017 07:50:01
* Description       -> Description
*
*
*
*/

#ifndef _WIN64
#include <avr/io.h>
#endif 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cmd.h"


/*	++Speicherplatz für den Antwort Header++
*	Die Nutzdaten sind in "pData" von
*	der "cmd_t" Struktur abzurufen
*/
static uint8_t	FrameHeader[ __CMD_HEADER_ENTRYS__ ];

static Crc_t sCrc;

static int8_t FrameStart = 0;

void ( *pCmdSendCallback )			( uint8_t *pData , uint8_t uiLength );


static inline uint8_t _Crc8CCITTUpdate	( uint8_t uiCrcStart , uint8_t *pData )
{
	uint8_t   i = 0;
	static uint8_t data = 0;
	
	uint8_t *pDataTmp = pData;
	
	data = ( uiCrcStart ^ ( *pDataTmp ) );
	
	for ( i = 0; i < 8; i++ )
	{
		if ( ( data & 0x80 ) != 0 )
		{
			data <<= 1;
			data ^= 0x07;
		}
		else
		{
			data <<= 1;
		}
	}

	return data;
}

static inline uint8_t _Crc8StrCCITT		( uint8_t uiCrcStart , uint8_t *pData , uint8_t uiLength )
{
	uint8_t uiCrcStartTmp = uiCrcStart;
	uint8_t *pDataTmp = pData;
	
	for( uint8_t x = 0 ; x < uiLength ; x++ )
	{
		uiCrcStartTmp = _Crc8CCITTUpdate( uiCrcStartTmp , ( uint8_t * ) pDataTmp++ );
	}
	
	return uiCrcStartTmp;
}

static inline int8_t cmdSearchFrame			( uint8_t *pReceive , uint8_t uiLength )
{
	for ( uint8_t x = 0 ; x < uiLength ; x++ )
	{
		if ( pReceive[x] == '-' )
		{
		  if ( pReceive[x+1] == '+' )
		  {
			return (int8_t)x + 2;
		  }
		  else
		  {
			  return -1;
		  }
		}
	}
	
	return -1;
}



void		cmdInit				( cmd_t *psAnswer )					
{
	#ifndef _WIN64
	pCmdSendCallback = _CMD_SEND_CB_FNC_PTR_;
	#endif
	
	if ( pCmdSendCallback == NULL ){
		return;
	}

	psAnswer->uiDataLength	= 0;			    // L�nge der Nutzdaten Bytes
	psAnswer->eDataType		= DATA_TYP_UINT8;	// Datentyp der Nutzdaten
	psAnswer->eMessageID	= ID_APPLICATION;	// Message Identifikation
	psAnswer->eExitcode		= CMD_EXIT_OK;		// Exitcode aus Funktionen
	psAnswer->pData			= NULL;				// Zeiger auf Nutzdaten
	
	sCrc.uiExternal		= 0;	// Extern resetten
	sCrc.uiInternal		= 0;	// Intern resetten 
	FrameStart			= 0;	// Index eines Frames
}

/*
*	In "*pReceive" muss die Zeichenfolge "-+" enthalten sein.
*	Dadurch wird der Beginn eines neuen Telegrammes erkannt.
*/
uint8_t		cmdParse			( uint8_t *pReceive , cmd_t *psParsed , uint16_t uiBufferLength )		
{
	FrameStart = cmdSearchFrame( pReceive , uiBufferLength );
	
	if ( FrameStart == - 1 ){
		return 1;
	}
		
	psParsed->uiDataLength 	= pReceive[ FrameStart + CMD_START_FRAME_OFFSET + CMD_HEADER_LENGTH_OF_FRAME ] -__CMD_HEADER_ENTRYS__;
	psParsed->eDataType		= pReceive[ FrameStart + CMD_START_FRAME_OFFSET + CMD_HEADER_DATA_TYP		 ];
	psParsed->eMessageID 	= pReceive[ FrameStart + CMD_START_FRAME_OFFSET + CMD_HEADER_ID				 ];
	psParsed->eExitcode		= pReceive[ FrameStart + CMD_START_FRAME_OFFSET + CMD_HEADER_EXITCODE		 ];	
	sCrc.uiExternal			= pReceive[ FrameStart + CMD_START_FRAME_OFFSET + CMD_HEADER_CRC			 ];
	
	if ( psParsed->uiDataLength ){
		psParsed->pData = pReceive + ( FrameStart + CMD_START_FRAME_OFFSET + __CMD_HEADER_ENTRYS__ );
	}
	else{
		psParsed->pData = NULL; // Keine Nutzdaten
	}
	
	sCrc.uiInternal = 0;
	
	pReceive[ FrameStart + CMD_START_FRAME_OFFSET + CMD_HEADER_CRC ] = 0;

	/*
	*	Checksumme vom Frame Header bilden
	*/
	sCrc.uiInternal = _Crc8StrCCITT( sCrc.uiInternal , 
									 &pReceive[FrameStart + CMD_START_FRAME_OFFSET ] , 
									 __CMD_HEADER_ENTRYS__ );
	
	/*
	*	Checksumme von Rohdaten bilden
	*/
	sCrc.uiInternal = _Crc8StrCCITT( sCrc.uiInternal , 
									 &pReceive[FrameStart + CMD_START_FRAME_OFFSET + __CMD_HEADER_ENTRYS__ ] , 
									 psParsed->uiDataLength );
	
	
	/* Checksummen vergleichen */
	if ( sCrc.uiInternal != sCrc.uiExternal ){
		return 2;
	}
		
	return 0;
}

Header_t	cmdBuildHeader		( cmd_t *psAnswer )					
{		
	static Header_t HeaderInfo;
		
	FrameHeader[CMD_HEADER_CRC]	= 0;

	uint16_t FrameSize = __CMD_HEADER_ENTRYS__ + psAnswer->uiDataLength;
	
	if ( FrameSize >= 255 ){
		HeaderInfo.Exitcode |= CMD_HEADER_EXITCODE_OVF; // Frame darf nicht >= 255 Bytes sein	
		return HeaderInfo;
	}
	
	if ( psAnswer->pData == NULL ){
		HeaderInfo.Exitcode |= CMD_HEADER_EXITCODE_NO_DATA; // Es wurden keine Nutzdaten übergeben
		// Wir brauchen deswegen nicht direkt die Funktion zu verlassen!
	}
	
	FrameHeader[CMD_HEADER_LENGTH_OF_FRAME]	= (uint8_t)FrameSize;	// Länge der ganzen Antwort
	FrameHeader[CMD_HEADER_DATA_TYP]		= psAnswer->eDataType;	// (u)char , (u)int8 , (u)int16 , (u)int32 usw.	
	FrameHeader[CMD_HEADER_ID]				= psAnswer->eMessageID; // 0..255
	FrameHeader[CMD_HEADER_EXITCODE]		= psAnswer->eExitcode;	// 0..255
	
	sCrc.uiInternal = 0; // alte Checksumme löschen
	
	sCrc.uiInternal = _Crc8StrCCITT( sCrc.uiInternal , FrameHeader , __CMD_HEADER_ENTRYS__ );
	
	/*	Checksumme von Nutzdaten bilden
	*	Falls keine Nutzdaten vorhanden sind, sollte die "for Schleife" von "_Crc8StrCCITT"
	*	ohne einen Durchlauf beendet werden.
	*/	
	sCrc.uiInternal = _Crc8StrCCITT( sCrc.uiInternal , psAnswer->pData , psAnswer->uiDataLength );		

	FrameHeader[CMD_HEADER_CRC] = sCrc.uiInternal;
		
	psAnswer->eMessageID	= 0;
	psAnswer->eDataType	= 0;
	psAnswer->eExitcode	= 0;
				
	HeaderInfo.FramePtr = FrameHeader;
				
	return HeaderInfo;
}

void		cmdBuildAnswer		(	
									cmd_t *psAnswer , 
									enum Cmd_Ident_Enum eIdent , 
									enum Cmd_Data_Type_Enum eDataType , 
									enum Cmd_Exitcodes_Enum eExitcode , 
									uint8_t DataLength , 
									uint8_t *pData 
								)
{
	psAnswer->eMessageID	= eIdent;		// Beschreibt den Nachrichten Typ. Damit die gegenstelle die Nachrichten unterscheiden kann
	psAnswer->eDataType		= eDataType;	// Gibt an um welchen Daten Typ es sich handelt
	psAnswer->eExitcode		= eExitcode;	// Ruekgabewert einer Funktion 
	psAnswer->pData			= pData;		// Zeiger auf die Daten die gesendet werden sollen
	psAnswer->uiDataLength	= DataLength;	// Anzahl der Bytes
}

void		cmdSendAnswer		( cmd_t *psAnswer )					
{
	Header_t HeaderInfo  = cmdBuildHeader( psAnswer );
	
	#ifndef _WIN64
		pCmdSendCallback( HeaderInfo.FramePtr , __CMD_HEADER_ENTRYS__ );
		pCmdSendCallback( psAnswer->pData , psAnswer->uiDataLength );
	#else
		printf( "eMessageID = %d\r\neDataType = %d\r\neExitcode = %d\r\npData = %s\r\nuiDataLength = %d\r\nsCrc.uiInternal = %d" , psAnswer->eMessageID , psAnswer->eDataType , psAnswer->eExitcode , psAnswer->pData , psAnswer->uiDataLength , sCrc.uiInternal );
	
		printf( "\r\nTelegramm: " );
		for ( uint8_t ui = 0 ; ui < __CMD_HEADER_ENTRYS__ ; ui++ )
		{
			printf( "%02x " , HeaderInfo.FramePtr[ui] );
		}
	
		for( uint8_t ui = 0 ; ui < psAnswer->uiDataLength ; ui++ )
		{
			printf( "%02x " , psAnswer->pData[ui] );
		}
	#endif
	
}
