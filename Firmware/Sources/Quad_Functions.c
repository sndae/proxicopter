#include "Quadro_Public.h"
#include "I2C2.h"
#include "AS1.h"
#include "SM1.h"

#define ACC_I2C_ADDR             0x19
#define QUAD_POOLELELMENT_SIZE   0x0A

static QUAD_PACK_U  s_atPackPool[QUAD_POOLELELMENT_SIZE];
static QUAD_PACK_U  s_uiPackPoolLevel = 0;

QUAD_PACK_U QuadPoolPacketGet()
{
  return;
}

QuadRes QuadSendPack(UInt16 uiDst, QUAD_PACK_HEAD_T *ptPck)
{
  UInt32 uiDataCntr = ptPck->uiLen;
  UInt16 usDataSizeSent = 0;
  UInt8* psData =  (UInt8*)ptPck + QUAD_PACK_HEAD_SIZE;
  
  
  switch(uiDst){
    case QUAD_DST_INT :
      break;
    case QUAD_DST_ACC :
      I2C2_SelectSlave(ACC_I2C_ADDR);
      break;
    case QUAD_DST_GYRO:
      I2C2_SelectSlave(L3G4200D_I2C_ADDR);
      I2C2_SendBlock(psData, uiDataCntr, &usDataSizeSent);
      break;      
    case QUAD_DST_RF  :      
      while(uiDataCntr--){
        SM1_SendChar(*(psData)++);
      } 
      break;
    case QUAD_DST_UART:
      uiDataCntr += QUAD_PACK_HEAD_SIZE; 
      psData -= QUAD_PACK_HEAD_SIZE;
      while(uiDataCntr--){
        AS1_SendChar(*(psData)++);
      } 
      break;
    default:
      return S_FAIL;
  }
  
  return S_OK;
}

QuadRes QuadGetPack(QUAD_PACK_HEAD_T *ptPck){
  
}
