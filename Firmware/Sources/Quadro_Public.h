/** ###################################################################
**     Filename    : Quadro_public.h
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Component   : Events
**     Version     : Driver 01.03
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-11-06, 21:40, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Public structures
**
** ###################################################################*/

#ifndef __QUADRO_PUBLIC_H__
#define __QUADRO_PUBLIC_H__

#include "PE_Types.h"
#include "PE_Error.h"
/***** Commands list ******/

#define QUAD_CMD_READ_DATA_REQ   (0x0001)
#define QUAD_CMD_READ_DATA_CNF   (0x0002)

#define QUAD_CMD_SET_PWM_REQ     (0x0003)
#define QUAD_CMD_SET_PWM_CNF     (0x0004)

#define QUAD_CMD_DATA_IND        (0x0005)
#define QUAD_CMD_DATA_RES        (0x0006)

#define QUAD_CMD_WRITE_DATA_REQ  (0x0007)
#define QUAD_CMD_WRITE_DATA_CNF  (0x0008)


/****** Destinations list *****/

typedef enum QUAD_SRCDST_Etag{
  QUAD_SRCDST_UKNWN         = (0x0000),
  QUAD_SRCDST_INT           = (0x0001),
  QUAD_SRCDST_ACC           = (0x0002),
  QUAD_SRCDST_GYRO          = (0x0003),
  QUAD_SRCDST_RF            = (0x0004),
  QUAD_SRCDST_UART          = (0x0005),
}QUAD_SRCDST_E;

/****** Quadro types definitions ******/
typedef byte    QuadRes;
#define S_OK    (ERR_OK)
#define S_FAIL  (ERR_OK + 1)


/******* Data structures definitions *******/
#define QUAD_PACK_HEAD_SIZE sizeof(QUAD_PACK_HEAD_T)

typedef struct QUAD_PACK_HEAD_Ttag{
  UInt16  uiCmd;
  QUAD_SRCDST_E  eSrc;
  QUAD_SRCDST_E  eDst;
  UInt16  uiLen;  
}QUAD_PACK_HEAD_T;

typedef struct QUAD_ACCMETER_DATA_Ttag{
  Int16 iAccX;
  Int16 iAccY;
  Int16 iAccZ;  
}QUAD_ACCMETER_DATA_T;

typedef struct QUAD_GYROMETER_DATA_Ttag{
  Int16 iGyroX;
  Int16 iGyroY;
  Int16 iGyroZ;    
}QUAD_GYROMETER_DATA_T;

typedef struct QUAD_PWM_DATA_Ttag{
  UInt16 uiPwmA;
  UInt16 uiPwmB;
  UInt16 uiPwmC;    
  UInt16 uiPwmD;      
}QUAD_PWM_DATA_T;

typedef struct QUAD_GET_DATA_Ttag{
  QUAD_ACCMETER_DATA_T  tAccData;
  QUAD_GYROMETER_DATA_T tGyroData;
}QUAD_GET_DATA_T;

/***** GetData request packet *****/

typedef struct QUAD_PACK_GET_DATA_REQ_Ttag{
  QUAD_PACK_HEAD_T  tHead;
}QUAD_PACK_GET_DATA_REQ_T;

typedef struct QUAD_PACK_GET_DATA_CNF_Ttag{
  QUAD_PACK_HEAD_T  tHead;
  QUAD_GET_DATA_T   tData;
}QUAD_PACK_GET_DATA_CNF_T;

/***** SetPwm request packet *****/

typedef struct QUAD_PACK_SET_PWM_REQ_Ttag{
  QUAD_PACK_HEAD_T  tHead;
  QUAD_PWM_DATA_T   tData;
}QUAD_PACK_SET_PWM_REQ_T;

typedef struct QUAD_PACK_SET_PWM_CNF_Ttag{
  QUAD_PACK_HEAD_T  tHead;
}QUAD_PACK_SET_PWM_CNF_T;

/***** Data indication packet *****/

typedef struct QUAD_PACK_DATA_IND_Ttag{
  QUAD_PACK_HEAD_T  tHead;
  QUAD_GET_DATA_T   tData;  
}QUAD_PACK_DATA_IND_T;

typedef struct QUAD_PACK_DATA_RES_Ttag{
  QUAD_PACK_HEAD_T  tHead;
  QUAD_PWM_DATA_T   tData;  
}QUAD_PACK_DATA_RES_T;

/***** Union of all public packets *****/

typedef union QUAD_PACK_Utag{
  QUAD_PACK_HEAD_T         tHead;
  QUAD_PACK_GET_DATA_REQ_T tPack1;
  QUAD_PACK_GET_DATA_CNF_T tPack2;
  QUAD_PACK_SET_PWM_REQ_T  tPack3;
  QUAD_PACK_SET_PWM_CNF_T  tPack4;
  QUAD_PACK_DATA_IND_T     tPack5;
  QUAD_PACK_DATA_RES_T     tPack6;
}QUAD_PACK_U;

/***** Function declarations *****/
QuadRes QuadSendPack(QUAD_PACK_U *ptPck);
QuadRes Quad_SetI2CSlave(QUAD_SRCDST_E eSrc);
QUAD_PACK_U *QuadWaitForPacket(bool bInfinite);
QUAD_PACK_U *QuadPoolPacketGet();
void QuadPackRelease(QUAD_PACK_U *ptPack);
byte Quad_GetI2CSlave();

#endif
