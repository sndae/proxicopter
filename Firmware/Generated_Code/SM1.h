/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SM1.h
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Component   : SynchroMaster
**     Version     : Component 02.344, Driver 02.04, CPU db: 3.00.240
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-11-22, 23:31, # CodeGen: 33
**     Abstract    :
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**         Synchro type                : MASTER
**
**         Serial channel              : QSPI0
**
**         Protocol
**             Init baud rate          : 0_06666us
**             Clock edge              : rising
**             Width                   : 8 bits
**             Empty character         : 0
**             Empty char. on input    : RECEIVED
**
**         Registers
**             Input buffer            : QSPI0_DRCV [F202]
**             Output buffer           : QSPI0_DXMIT [F203]
**             Control register        : QSPI0_SCTRL [F200]
**             Mode register           : QSPI0_DSCTRL [F201]
**             Baud setting reg.       : QSPI0_SCTRL [F200]
**
**         Input interrupt
**             Vector name             : INT_SPI_RxFull
**             Priority                : 1
**
**         Output interrupt
**             Vector name             : INT_SPI_TxEmpty
**             Priority                : 1
**
**         Used pins                   :
**         ----------------------------------------------------------
**              Function    | On package |    Name
**         ----------------------------------------------------------
**               Input      |     33     |  GPIOC8_MISO_RXD0
**               Output     |     35     |  GPIOC10_MOSI_XB_IN5_MISO
**               Clock      |     34     |  GPIOC9_SCLK_XB_IN4
**         ----------------------------------------------------------
**
**     Contents    :
**         RecvChar        - byte SM1_RecvChar(SM1_TComData *Chr);
**         SendChar        - byte SM1_SendChar(SM1_TComData Chr);
**         GetCharsInRxBuf - word SM1_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word SM1_GetCharsInTxBuf(void);
**         GetError        - byte SM1_GetError(SM1_TError *Err);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __SM1
#define __SM1

/* MODULE SM1. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "Cpu.h"


#ifndef __BWUserType_SM1_TError
#define __BWUserType_SM1_TError
  typedef union {
    byte err;
    struct {
      bool OverRun  : 1;               /* OverRun error flag */
      bool RxBufOvf : 1;               /* Rx buffer full error flag */
      bool FaultErr : 1;               /* Fault mode error flag */
    }errName;
  } SM1_TError;                        /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
#endif

#define SM1_EOF 0                      /* Empty character */

#ifndef __BWUserType_SM1_TComData
#define __BWUserType_SM1_TComData
  typedef byte SM1_TComData;           /* User type for communication. Size of this type depends on the communication data witdh. */
#endif


byte SM1_RecvChar(SM1_TComData *Chr);
/*
** ===================================================================
**     Method      :  SM1_RecvChar (component SynchroMaster)
**
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). 
**         For information about SW overrun behavior please see
**         <General info page>.
**         [ Version specific information for Freescale 56800
**         derivatives ] 
**         DMA mode:
**         If DMA controller is available on selected CPU and receiver
**         is configured to use DMA controller then this method only
**         sets the selected DMA channel. Status of the DMA transfer
**         can then be checked using method GetCharsInRxBuf. See
**         typical usage for details about communication using DMA.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to the received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - No data in receiver.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. In
**                           polling mode, this error code is returned
**                           only when the hardware supports detection
**                           of the overrun error. If interrupt service
**                           is enabled, and input buffer allocated by
**                           the component is full, the component
**                           behaviour depends on <Input buffer size>
**                           property : if property is 0, last received
**                           data-word is preserved (and previous is
**                           overwritten), if property is greater than 0,
**                           new received data-word are ignored.
**                           ERR_FAULT - Fault error was detected from
**                           the last char or block received. In the
**                           polling mode the ERR_FAULT is return until
**                           the user clear the fault flag bit, but in
**                           the interrupt mode ERR_FAULT is returned
**                           only once after the fault error occured.
**                           This error is supported only on the CPUs
**                           supports the faul mode function - where
**                           <Fault mode> property is available.
** ===================================================================
*/

byte SM1_SendChar(SM1_TComData Chr);
/*
** ===================================================================
**     Method      :  SM1_SendChar (component SynchroMaster)
**
**     Description :
**         Sends one character to the channel.
**         [ Version specific information for Freescale 56800
**         derivatives ] 
**         DMA mode:
**         If DMA controller is available on the selected CPU and the
**         transmitter is configured to use DMA controller then this
**         method only sets the selected DMA channel. The status of the
**         DMA transfer can then be checked using GetCharsInTxBuf
**         method. See the typical usage for details about
**         communication using DMA.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/

word SM1_GetCharsInRxBuf(void);
/*
** ===================================================================
**     Method      :  SM1_GetCharsInRxBuf (component SynchroMaster)
**
**     Description :
**         Returns the number of characters in the input buffer.
**         Note: If the Interrupt service is disabled, and the Ignore
**         empty character is set to yes, and a character has been
**         received, then this method returns 1 although it was an
**         empty character.
**         [ Version specific information for Freescale 56800
**         derivatives ] 
**         DMA mode:
**         If DMA controller is available on the selected CPU and the
**         receiver is configured to use DMA controller then this
**         method returns the number of characters in the receive
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/

word SM1_GetCharsInTxBuf(void);
/*
** ===================================================================
**     Method      :  SM1_GetCharsInTxBuf (component SynchroMaster)
**
**     Description :
**         Returns the number of characters in the output buffer.
**         [ Version specific information for Freescale 56800
**         derivatives ] 
**         DMA mode:
**         If DMA controller is available on the selected CPU and the
**         transmitter is configured to use DMA controller then this
**         method returns the number of characters in the transmit
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/

byte SM1_GetError(SM1_TError *Err);
/*
** ===================================================================
**     Method      :  SM1_GetError (component SynchroMaster)
**
**     Description :
**         Returns a set of errors on the channel (errors that cannot
**         be returned in given methods). The component accumulates
**         errors in a set; after calling [GetError] this set is
**         returned and cleared. This method is available only if the
**         "Interrupt service/event" property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Err             - A pointer to the returned set of errors
**     Returns     :
**         ---             - Error code (if GetError did not succeed),
**                           possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

void SM1_InterruptRx(void);
/*
** ===================================================================
**     Method      :  SM1_InterruptRx (component SynchroMaster)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void SM1_InterruptTx(void);
/*
** ===================================================================
**     Method      :  SM1_InterruptTx (component SynchroMaster)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void SM1_Init(void);
/*
** ===================================================================
**     Method      :  SM1_Init (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END SM1. */

#endif /* ifndef __SM1 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
