/*******************************************************************************
* File Name: DAC_204v.c  
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
#include "DAC_204v.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 DAC_204v_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 DAC_204v_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static DAC_204v_backupStruct DAC_204v_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: DAC_204v_Init
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
void DAC_204v_Init(void) 
{
    DAC_204v_CR0 = (DAC_204v_MODE_V );

    /* Set default data source */
    #if(DAC_204v_DEFAULT_DATA_SRC != 0 )
        DAC_204v_CR1 = (DAC_204v_DEFAULT_CNTL | DAC_204v_DACBUS_ENABLE) ;
    #else
        DAC_204v_CR1 = (DAC_204v_DEFAULT_CNTL | DAC_204v_DACBUS_DISABLE) ;
    #endif /* (DAC_204v_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(DAC_204v_DEFAULT_STRB != 0)
        DAC_204v_Strobe |= DAC_204v_STRB_EN ;
    #endif/* (DAC_204v_DEFAULT_STRB != 0) */

    /* Set default range */
    DAC_204v_SetRange(DAC_204v_DEFAULT_RANGE); 

    /* Set default speed */
    DAC_204v_SetSpeed(DAC_204v_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: DAC_204v_Enable
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
void DAC_204v_Enable(void) 
{
    DAC_204v_PWRMGR |= DAC_204v_ACT_PWR_EN;
    DAC_204v_STBY_PWRMGR |= DAC_204v_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(DAC_204v_restoreVal == 1u) 
        {
             DAC_204v_CR0 = DAC_204v_backup.data_value;
             DAC_204v_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: DAC_204v_Start
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
*  DAC_204v_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void DAC_204v_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(DAC_204v_initVar == 0u)
    { 
        DAC_204v_Init();
        DAC_204v_initVar = 1u;
    }

    /* Enable power to DAC */
    DAC_204v_Enable();

    /* Set default value */
    DAC_204v_SetValue(DAC_204v_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: DAC_204v_Stop
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
void DAC_204v_Stop(void) 
{
    /* Disble power to DAC */
    DAC_204v_PWRMGR &= (uint8)(~DAC_204v_ACT_PWR_EN);
    DAC_204v_STBY_PWRMGR &= (uint8)(~DAC_204v_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        DAC_204v_backup.data_value = DAC_204v_CR0;
        DAC_204v_CR0 = DAC_204v_CUR_MODE_OUT_OFF;
        DAC_204v_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: DAC_204v_SetSpeed
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
void DAC_204v_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    DAC_204v_CR0 &= (uint8)(~DAC_204v_HS_MASK);
    DAC_204v_CR0 |=  (speed & DAC_204v_HS_MASK);
}


/*******************************************************************************
* Function Name: DAC_204v_SetRange
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
void DAC_204v_SetRange(uint8 range) 
{
    DAC_204v_CR0 &= (uint8)(~DAC_204v_RANGE_MASK);      /* Clear existing mode */
    DAC_204v_CR0 |= (range & DAC_204v_RANGE_MASK);      /*  Set Range  */
    DAC_204v_DacTrim();
}


/*******************************************************************************
* Function Name: DAC_204v_SetValue
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
void DAC_204v_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 DAC_204v_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    DAC_204v_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        DAC_204v_Data = value;
        CyExitCriticalSection(DAC_204v_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: DAC_204v_DacTrim
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
void DAC_204v_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((DAC_204v_CR0 & DAC_204v_RANGE_MASK) >> 2) + DAC_204v_TRIM_M7_1V_RNG_OFFSET;
    DAC_204v_TR = CY_GET_XTND_REG8((uint8 *)(DAC_204v_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
