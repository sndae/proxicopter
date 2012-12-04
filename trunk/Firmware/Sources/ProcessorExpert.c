/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Version     : Driver 01.14
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-11-06, 21:40, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "I2C2.h"
#include "AS1.h"
#include "SM1.h"
#include "PWMC1.h"
#include "eFPWM1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "PE_Types.h"
#include "IO_Map.h"

void main(void)
{
  /* Write your local variable definition here */
  UInt32  uiCntr = 0;
  QUAD_PACK_U *ptPack = 0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

  for(;;) {
    ptPack = QuadWaitForPacket(FALSE);
    if(ptPack){
      switch(ptPack->tHead.uiCmd){
        case QUAD_CMD_READ_DATA_REQ:
        case QUAD_CMD_WRITE_DATA_REQ:
          QuadSendPack(ptPack);
          break;
        break;
        case QUAD_CMD_DATA_IND:

        default:
        break;
      }
      QuadPackRelease(ptPack);
    }
  }
}

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
