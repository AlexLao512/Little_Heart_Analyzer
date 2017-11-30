/*******************************************************************************
* File Name: ECG_RL_DRIVE_DAC_PM.c  
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

#include "ECG_RL_DRIVE_DAC.h"

static ECG_RL_DRIVE_DAC_backupStruct ECG_RL_DRIVE_DAC_backup;


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_SaveConfig
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
void ECG_RL_DRIVE_DAC_SaveConfig(void) 
{
    if (!((ECG_RL_DRIVE_DAC_CR1 & ECG_RL_DRIVE_DAC_SRC_MASK) == ECG_RL_DRIVE_DAC_SRC_UDB))
    {
        ECG_RL_DRIVE_DAC_backup.data_value = ECG_RL_DRIVE_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_RestoreConfig
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
void ECG_RL_DRIVE_DAC_RestoreConfig(void) 
{
    if (!((ECG_RL_DRIVE_DAC_CR1 & ECG_RL_DRIVE_DAC_SRC_MASK) == ECG_RL_DRIVE_DAC_SRC_UDB))
    {
        if((ECG_RL_DRIVE_DAC_Strobe & ECG_RL_DRIVE_DAC_STRB_MASK) == ECG_RL_DRIVE_DAC_STRB_EN)
        {
            ECG_RL_DRIVE_DAC_Strobe &= (uint8)(~ECG_RL_DRIVE_DAC_STRB_MASK);
            ECG_RL_DRIVE_DAC_Data = ECG_RL_DRIVE_DAC_backup.data_value;
            ECG_RL_DRIVE_DAC_Strobe |= ECG_RL_DRIVE_DAC_STRB_EN;
        }
        else
        {
            ECG_RL_DRIVE_DAC_Data = ECG_RL_DRIVE_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_Sleep
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
*  ECG_RL_DRIVE_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(ECG_RL_DRIVE_DAC_ACT_PWR_EN == (ECG_RL_DRIVE_DAC_PWRMGR & ECG_RL_DRIVE_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        ECG_RL_DRIVE_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        ECG_RL_DRIVE_DAC_backup.enableState = 0u;
    }
    
    ECG_RL_DRIVE_DAC_Stop();
    ECG_RL_DRIVE_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: ECG_RL_DRIVE_DAC_Wakeup
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
*  ECG_RL_DRIVE_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ECG_RL_DRIVE_DAC_Wakeup(void) 
{
    ECG_RL_DRIVE_DAC_RestoreConfig();
    
    if(ECG_RL_DRIVE_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        ECG_RL_DRIVE_DAC_Enable();

        /* Restore the data register */
        ECG_RL_DRIVE_DAC_SetValue(ECG_RL_DRIVE_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
