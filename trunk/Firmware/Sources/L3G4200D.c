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
  UInt8 bData[4] = 0;
  Uint8 bRes = ERR_OK;
  Uint8 bSnt = 0

  bRes = I2C2_SelectSlave(L3G4200D_I2C_ADDR);
  if(bRes != ERR_OK){
    return bRes;
  }


  /* Select the FIFO mode (Bypass mode) by FIFO_CTRL_REG. Watermark is not needed in this mode.
   * Watermark is used if we want an interrupt service to be generated on DRDY/INT2 pin
   * when the the FIFO is empty or full */

  /* Init FIFO_CTRL_REG register */
  /* FIFO_CTRL_REG = 0x00 */

  /* Init CTRL_REG1 register. Select 100 Hz for refreshing X,Z,Y axises, Normal mode is selected,
   * Enable X,Z,Y axises. */
  /* CTRL_REG1 = 0x0F */

  bData[0] = L3G_CTRL_REG1;
  bData[1] = 0x0F;
  bRes = I2C2_SendBlock((void*)&bData[0], 2, &bSnt);
  if(bRes != ERR_OK){
    return bRes;
  }

  /* CTRL_REG2 register is configured with default setting
   * Highpass filter mode is normal ; High pass filter frequency is 8Hz (ODR=100kHz);
   * */

  bData[0] = L3G_CTRL_REG2;
  bData[1] = 0x00;
  bRes = I2C2_SendBlock((void*)&bData[0], 2, &bSnt);
  if(bRes != ERR_OK){
    return bRes;
  }
  /* CTRL_REG3 register is configured with 0x00. ISRs are not needed in the Bypass mode.
   * I2_DRDY bit can be used for checking the data consistency in the feature */
  /* CTRL_REG3 = 0x00 */
  bData[0] = L3G_CTRL_REG3;
  bData[1] = 0x00;
  bRes = I2C2_SendBlock((void*)&bData[0], 2, &bSnt);
  if(bRes != ERR_OK){
    return bRes;
  }

  /* CTRL_REG4 register is configured with 0x00.
   * Block data update - continious update
   * Data LSB @ lower address
   * Full scale = 250dps
   * Self-test diabled  */
  /* CTRL_REG4 = 0x00 */
  bData[0] = L3G_CTRL_REG4;
  bData[1] = 0x00;
  bRes = I2C2_SendBlock((void*)&bData[0], 2, &bSnt);
  if(bRes != ERR_OK){
    return bRes;
  }

  /* Init CTRL_REG5 register. Enable FIFO, Enable HPen */
  /* CTRL_REG5 = 0x50 */


  return S_OK;
}

/* Function for reading the X,Y,Z axis */
QuadRes L3G4200D_ReadAxisData(){

  /* Read data from the X axis. The register is 16 bits. It consist of
   * two registers from 8 bites - OUT_X_L , OUT_X_H  */

  /* Read data from the Y axis. The register is 16 bits. It consist of
   * two registers from 8 bites - OUT_Y_L , OUT_Y_H  */

  /* Read data from the Z axis. The register is 16 bits. It consist of
   * two registers from 8 bites - OUT_Z_L , OUT_Z_H  */

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

  return S_OK;
}

QuadRes L3G4200D_ReadGyroTemp(){

  return S_OK;
}


