/*******************************************************************************
* File Name: ECG_ADC_REF_VDAC8_PM.c  
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

#include "ECG_ADC_REF_VDAC8.h"

static ECG_ADC_REF_VDAC8_backupStruct ECG_ADC_REF_VDAC8_backup;


/*******************************************************************************
* Function Name: ECG_ADC_REF_VDAC8_SaveConfig
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
void ECG_ADC_REF_VDAC8_SaveConfig(void) 
{
    if (!((ECG_ADC_REF_VDAC8_CR1 & ECG_ADC_REF_VDAC8_SRC_MASK) == ECG_ADC_REF_VDAC8_SRC_UDB))
    {
        ECG_ADC_REF_VDAC8_backup.data_value = ECG_ADC_REF_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: ECG_ADC_REF_VDAC8_RestoreConfig
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
void ECG_ADC_REF_VDAC8_RestoreConfig(void) 
{
    if (!((ECG_ADC_REF_VDAC8_CR1 & ECG_ADC_REF_VDAC8_SRC_MASK) == ECG_ADC_REF_VDAC8_SRC_UDB))
    {
        if((ECG_ADC_REF_VDAC8_Strobe & ECG_ADC_REF_VDAC8_STRB_MASK) == ECG_ADC_REF_VDAC8_STRB_EN)
        {
            ECG_ADC_REF_VDAC8_Strobe &= (uint8)(~ECG_ADC_REF_VDAC8_STRB_MASK);
            ECG_ADC_REF_VDAC8_Data = ECG_ADC_REF_VDAC8_backup.data_value;
            ECG_ADC_REF_VDAC8_Strobe |= ECG_ADC_REF_VDAC8_STRB_EN;
        }
        else
        {
            ECG_ADC_REF_VDAC8_Data = ECG_ADC_REF_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: ECG_ADC_REF_VDAC8_Sleep
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
*  ECG_ADC_REF_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void ECG_ADC_REF_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(ECG_ADC_REF_VDAC8_ACT_PWR_EN == (ECG_ADC_REF_VDAC8_PWRMGR & ECG_ADC_REF_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        ECG_ADC_REF_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        ECG_ADC_REF_VDAC8_backup.enableState = 0u;
    }
    
    ECG_ADC_REF_VDAC8_Stop();
    ECG_ADC_REF_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: ECG_ADC_REF_VDAC8_Wakeup
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
*  ECG_ADC_REF_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ECG_ADC_REF_VDAC8_Wakeup(void) 
{
    ECG_ADC_REF_VDAC8_RestoreConfig();
    
    if(ECG_ADC_REF_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        ECG_ADC_REF_VDAC8_Enable();

        /* Restore the data register */
        ECG_ADC_REF_VDAC8_SetValue(ECG_ADC_REF_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
