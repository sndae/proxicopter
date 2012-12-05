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
  QuadRes bRes = ERR_OK;
  if(eSrc == QUAD_SRCDST_ACC){
    s_eCurrentI2CSrc = eSrc;
    bRes = I2C2_SelectSlave(ACC_I2C_ADDR);
  }else if(eSrc == QUAD_SRCDST_GYRO){
    s_eCurrentI2CSrc = eSrc;
    bRes = I2C2_SelectSlave(L3G4200D_I2C_ADDR);
  }

  return bRes;
}

QUAD_SRCDSST_E  Quad_GetI2CSlave(){
  return s_eCurrentI2CSrc;
}

QuadRes QuadSendPack(QUAD_PACK_U *puPack)
{
  UInt32 uiDataCntr = puPack->tHead.uiLen;
  UInt16 usDataSizeSent = 0;
  UInt8* psData =  (UInt8*)&puPack->tPack2.tData;
  QuadRes   bRes = ERR_OK;
  
  switch(puPack->tHead.eDst){
    case QUAD_SRCDST_INT :
      break;
    case QUAD_SRCDST_ACC :
    case QUAD_SRCDST_GYRO:
      bRes = Quad_SetI2CSlave(puPack->tHead.eDst);
      if(bRes == ERR_OK){
        if(puPack->tHead.uiCmd == QUAD_CMD_WRITE_DATA_REQ){
          bRes = I2C2_SendBlock(psData, uiDataCntr, &usDataSizeSent);
        }else if(puPack->tHead.uiCmd == QUAD_CMD_READ_DATA_REQ){
          bRes = I2C2_RecvBlock(psData, uiDataCntr, &usDataSizeSent);
        }else{
          bRes = S_FAIL;
        }
      }
      break;      
    case QUAD_SRCDST_RF  :
      if(puPack->tHead.uiCmd == QUAD_CMD_WRITE_DATA_REQ){
        while((bRes == ERR_OK) && (uiDataCntr--)){
          bRes = SM1_SendChar(*(psData)++);
        }
      }else if(puPack->tHead.uiCmd == QUAD_CMD_READ_DATA_REQ){
        while((bRes == ERR_OK) && (uiDataCntr--)){
          bRes = SM1_RecvChar(psData++);
        }
      }else{
        bRes = S_FAIL;
      }
      break;
    case QUAD_SRCDST_UART:
      uiDataCntr += QUAD_PACK_HEAD_SIZE; 
      psData -= QUAD_PACK_HEAD_SIZE;
      if(puPack->tHead.uiCmd == QUAD_CMD_WRITE_DATA_REQ){
        while((bRes == ERR_OK) && (uiDataCntr--)){
          bRes = AS1_SendChar(*(psData)++);
        }
      }else if(puPack->tHead.uiCmd == QUAD_CMD_READ_DATA_REQ){
        while((bRes == ERR_OK) && (uiDataCntr--)){
          bRes = AS1_RecvChar(psData++);
        }
      }else{
        bRes = S_FAIL;
      }
      break;
    default:
      bRes = S_FAIL;
      break;
  }
  
  return bRes;
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
