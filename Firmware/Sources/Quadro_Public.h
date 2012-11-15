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

#include "PE_Types.h"

/***** Commands list ******/

#define QUAD_CMD_GET_DATA_REQ   (0x0001)
#define QUAD_CMD_GET_DATA_CNF   (0x0002)

#define QUAD_CMD_SET_PWM_REQ    (0x0003)
#define QUAD_CMD_SET_PWM_CNF    (0x0004)

#define QUAD_CMD_DATA_IND       (0x0005)
#define QUAD_CMD_DATA_RES       (0x0006)

/****** Sources list *****/

#define QUAD_SRC_INT            (0x0000)
#define QUAD_SRC_ACC            (0x0001)
#define QUAD_SRC_GYRO           (0x0002)
#define QUAD_SRC_RF             (0x0003)
#define QUAD_SRC_UART           (0x0004)

/****** Destinations list *****/

#define QUAD_DST_INT            (0x0000)
#define QUAD_DST_ACC            (0x0001)
#define QUAD_DST_GYRO           (0x0002)
#define QUAD_DST_RF             (0x0003)
#define QUAD_DST_UART           (0x0004)

/****** Quadro types definitions ******/
typedef UInt16  QuadRes;
#define S_OK    (0x0000)
#define S_FAIL  (0x0001)


/******* Data structures definitions *******/
#define QUAD_PACK_HEAD_SIZE sizeof(QUAD_PACK_HEAD_T)

typedef struct QUAD_PACK_HEAD_Ttag{
  UInt16  uiCmd;
  UInt16  uiSrc;
  UInt16  uiDst;
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
  QUAD_PACK_GET_DATA_REQ_T tPack1;
  QUAD_PACK_GET_DATA_CNF_T tPack2;
  QUAD_PACK_SET_PWM_REQ_T  tPack3;
  QUAD_PACK_SET_PWM_CNF_T  tPack4;
  QUAD_PACK_DATA_IND_T     tPack5;
  QUAD_PACK_DATA_RES_T     tPack6;
}QUAD_PACK_U;

/***** Function declarations *****/
QuadRes QuadSendPack(UInt16 uiDst, QUAD_PACK_HEAD_T *ptPck);
QuadRes QuadGetPack(QUAD_PACK_HEAD_T *ptPck);
