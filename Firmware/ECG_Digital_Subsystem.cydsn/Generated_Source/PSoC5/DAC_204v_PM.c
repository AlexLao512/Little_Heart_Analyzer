/*******************************************************************************
* File Name: DAC_204v_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "DAC_204v.h"

static DAC_204v_backupStruct DAC_204v_backup;


/*******************************************************************************
* Function Name: DAC_204v_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void DAC_204v_SaveConfig(void) 
{
    if (!((DAC_204v_CR1 & DAC_204v_SRC_MASK) == DAC_204v_SRC_UDB))
    {
        DAC_204v_backup.data_value = DAC_204v_Data;
    }
}


/*******************************************************************************
* Function Name: DAC_204v_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void DAC_204v_RestoreConfig(void) 
{
    if (!((DAC_204v_CR1 & DAC_204v_SRC_MASK) == DAC_204v_SRC_UDB))
    {
        if((DAC_204v_Strobe & DAC_204v_STRB_MASK) == DAC_204v_STRB_EN)
        {
            DAC_204v_Strobe &= (uint8)(~DAC_204v_STRB_MASK);
            DAC_204v_Data = DAC_204v_backup.data_value;
            DAC_204v_Strobe |= DAC_204v_STRB_EN;
        }
        else
        {
            DAC_204v_Data = DAC_204v_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: DAC_204v_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  DAC_204v_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void DAC_204v_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(DAC_204v_ACT_PWR_EN == (DAC_204v_PWRMGR & DAC_204v_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        DAC_204v_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        DAC_204v_backup.enableState = 0u;
    }
    
    DAC_204v_Stop();
    DAC_204v_SaveConfig();
}


/*******************************************************************************
* Function Name: DAC_204v_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  DAC_204v_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DAC_204v_Wakeup(void) 
{
    DAC_204v_RestoreConfig();
    
    if(DAC_204v_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        DAC_204v_Enable();

        /* Restore the data register */
        DAC_204v_SetValue(DAC_204v_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
