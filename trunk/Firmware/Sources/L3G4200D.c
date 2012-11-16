/** ###################################################################
**     Filename    : L3G4200D.c
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Component   : L3G4200D
**     Version     : Driver 01.03
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-11-06, 21:40, # CodeGen: 0
**     Abstract    :
**         This gyro driver module.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/

#include "L3G4200D.h"
#include "I2C2.h"

static float   gyroRate[3] = {0.0,0.0,0.0};
static Int32   gyroZero[3] = {0,0,0};
static UInt32  gyroSample[3] = {0,0,0};
static float   gyroScaleFactor = 0.0;
static float   gyroHeading = 0.0;
static UInt32  gyroLastMesuredTime = 0;
static byte    gyroSampleCount = 0;

QuadRes L3G4200D_Init(void){
  UInt8 bChar = 0;
  Uint8 bRes = ERR_OK;
  I2C2_SelectSlave(L3G4200D_I2C_ADDR);
  I2C2_SendChar(0xFF);
  I2C2_RecvChar(&bChar);

  return S_OK;
}

QuadRes L3G4200D_MeasuregyroSum(){

  return S_OK;
}

QuadRes L3G4200D_EvaluateGyroRate(){

  return S_OK;
}

QuadRes L3G4200D_InitializeGyro(){

  return S_OK;
}

QuadRes L3G4200D_MeasureGyro(){

  return S_OK;
}

QuadRes L3G4200D_CalibrateGyro(){
  r
  eturn S_OK;
}

QuadRes L3G4200D_ReadGyroTemp(){

  return S_OK;
}


