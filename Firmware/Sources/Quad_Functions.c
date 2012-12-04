#include "Quadro_Public.h"
#include "I2C2.h"
#include "AS1.h"
#include "SM1.h"

#define ACC_I2C_ADDR             0x19
#define QUAD_POOLELELMENT_SIZE   0x0A

static QUAD_PACK_U  s_atPackPool[QUAD_POOLELELMENT_SIZE];
static QUAD_PACK_U  s_uiPackPoolLevel = 0;

static  QUAD_SRC_E  s_eCurrentI2CSrc;


QuadRes Quad_SetI2CSlave(QUAD_SRCDSST_E eDst){
  if(eSrc == QUAD_SRCDST_ACC){
    s_eCurrentI2CSrc = eSrc;
    I2C2_SelectSlave(ACC_I2C_ADDR);
  }else if(eSrc == QUAD_SRCDST_GYRO){
    s_eCurrentI2CSrc = eSrc;
    I2C2_SelectSlave(L3G4200D_I2C_ADDR);
  }

  return S_OK;
}

QUAD_SRCDSST_E  Quad_GetI2CSlave(){
  return s_eCurrentI2CSrc;
}

QuadRes QuadSendPack(QUAD_PACK_HEAD_T *ptPck)
{
  UInt32 uiDataCntr = ptPck->uiLen;
  UInt16 usDataSizeSent = 0;
  UInt8* psData =  (UInt8*)ptPck + QUAD_PACK_HEAD_SIZE;
  
  
  switch(ptPck->eDst){
    case QUAD_DST_INT :
      break;
    case QUAD_DST_ACC :
    case QUAD_DST_GYRO:
      Quad_SetI2CSlave(ptPck->eDst);
      if(ptPck->uiCmd == QUAD_CMD_WRITE_DATA_REQ){
        I2C2_SendBlock(psData, uiDataCntr, &usDataSizeSent);
      }else if(ptPck->uiCmd == QUAD_CMD_READ_DATA_REQ){
        I2C2_RecvBlock(psData, uiDataCntr, &usDataSizeSent);
      }
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

QUAD_PACK_U *QuadWaitForPacket(bool bInfinite){
  do{
    if(s_uiPackPoolLevel){
      return &s_atPackPool[s_uiPackPoolLevel];
    }
  }while(bInfinite);

  return 0;
}

void QuadPackRelease(QUAD_PACK_U *ptPack){
  s_uiPackPoolLevel--;
}
