/*******************************************************************************
* File Name: ECG_RL_DRIVE_DAC.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "ECG_RL_DRIVE_DAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 ECG_RL_DRIVE_DAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 ECG_RL_DRIVE_DAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static ECG_RL_DRIVE_DAC_backupStruct ECG_RL_DRIVE_DAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_Init(void) 
{
    ECG_RL_DRIVE_DAC_CR0 = (ECG_RL_DRIVE_DAC_MODE_V );

    /* Set default data source */
    #if(ECG_RL_DRIVE_DAC_DEFAULT_DATA_SRC != 0 )
        ECG_RL_DRIVE_DAC_CR1 = (ECG_RL_DRIVE_DAC_DEFAULT_CNTL | ECG_RL_DRIVE_DAC_DACBUS_ENABLE) ;
    #else
        ECG_RL_DRIVE_DAC_CR1 = (ECG_RL_DRIVE_DAC_DEFAULT_CNTL | ECG_RL_DRIVE_DAC_DACBUS_DISABLE) ;
    #endif /* (ECG_RL_DRIVE_DAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(ECG_RL_DRIVE_DAC_DEFAULT_STRB != 0)
        ECG_RL_DRIVE_DAC_Strobe |= ECG_RL_DRIVE_DAC_STRB_EN ;
    #endif/* (ECG_RL_DRIVE_DAC_DEFAULT_STRB != 0) */

    /* Set default range */
    ECG_RL_DRIVE_DAC_SetRange(ECG_RL_DRIVE_DAC_DEFAULT_RANGE); 

    /* Set default speed */
    ECG_RL_DRIVE_DAC_SetSpeed(ECG_RL_DRIVE_DAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_Enable(void) 
{
    ECG_RL_DRIVE_DAC_PWRMGR |= ECG_RL_DRIVE_DAC_ACT_PWR_EN;
    ECG_RL_DRIVE_DAC_STBY_PWRMGR |= ECG_RL_DRIVE_DAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(ECG_RL_DRIVE_DAC_restoreVal == 1u) 
        {
             ECG_RL_DRIVE_DAC_CR0 = ECG_RL_DRIVE_DAC_backup.data_value;
             ECG_RL_DRIVE_DAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  ECG_RL_DRIVE_DAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(ECG_RL_DRIVE_DAC_initVar == 0u)
    { 
        ECG_RL_DRIVE_DAC_Init();
        ECG_RL_DRIVE_DAC_initVar = 1u;
    }

    /* Enable power to DAC */
    ECG_RL_DRIVE_DAC_Enable();

    /* Set default value */
    ECG_RL_DRIVE_DAC_SetValue(ECG_RL_DRIVE_DAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_Stop(void) 
{
    /* Disble power to DAC */
    ECG_RL_DRIVE_DAC_PWRMGR &= (uint8)(~ECG_RL_DRIVE_DAC_ACT_PWR_EN);
    ECG_RL_DRIVE_DAC_STBY_PWRMGR &= (uint8)(~ECG_RL_DRIVE_DAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        ECG_RL_DRIVE_DAC_backup.data_value = ECG_RL_DRIVE_DAC_CR0;
        ECG_RL_DRIVE_DAC_CR0 = ECG_RL_DRIVE_DAC_CUR_MODE_OUT_OFF;
        ECG_RL_DRIVE_DAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    ECG_RL_DRIVE_DAC_CR0 &= (uint8)(~ECG_RL_DRIVE_DAC_HS_MASK);
    ECG_RL_DRIVE_DAC_CR0 |=  (speed & ECG_RL_DRIVE_DAC_HS_MASK);
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_SetRange(uint8 range) 
{
    ECG_RL_DRIVE_DAC_CR0 &= (uint8)(~ECG_RL_DRIVE_DAC_RANGE_MASK);      /* Clear existing mode */
    ECG_RL_DRIVE_DAC_CR0 |= (range & ECG_RL_DRIVE_DAC_RANGE_MASK);      /*  Set Range  */
    ECG_RL_DRIVE_DAC_DacTrim();
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 ECG_RL_DRIVE_DAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    ECG_RL_DRIVE_DAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        ECG_RL_DRIVE_DAC_Data = value;
        CyExitCriticalSection(ECG_RL_DRIVE_DAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((ECG_RL_DRIVE_DAC_CR0 & ECG_RL_DRIVE_DAC_RANGE_MASK) >> 2) + ECG_RL_DRIVE_DAC_TRIM_M7_1V_RNG_OFFSET;
    ECG_RL_DRIVE_DAC_TR = CY_GET_XTND_REG8((uint8 *)(ECG_RL_DRIVE_DAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
