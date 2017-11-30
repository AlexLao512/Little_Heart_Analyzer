/*******************************************************************************
* File Name: ECG_ADC_Delay_Timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ECG_ADC_Delay_Timer.h"

static ECG_ADC_Delay_Timer_backupStruct ECG_ADC_Delay_Timer_backup;


/*******************************************************************************
* Function Name: ECG_ADC_Delay_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  ECG_ADC_Delay_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ECG_ADC_Delay_Timer_SaveConfig(void) 
{
    #if (!ECG_ADC_Delay_Timer_UsingFixedFunction)
        ECG_ADC_Delay_Timer_backup.TimerUdb = ECG_ADC_Delay_Timer_ReadCounter();
        ECG_ADC_Delay_Timer_backup.InterruptMaskValue = ECG_ADC_Delay_Timer_STATUS_MASK;
        #if (ECG_ADC_Delay_Timer_UsingHWCaptureCounter)
            ECG_ADC_Delay_Timer_backup.TimerCaptureCounter = ECG_ADC_Delay_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED)
            ECG_ADC_Delay_Timer_backup.TimerControlRegister = ECG_ADC_Delay_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: ECG_ADC_Delay_Timer_RestoreConfig
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
* Global variables:
*  ECG_ADC_Delay_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ECG_ADC_Delay_Timer_RestoreConfig(void) 
{   
    #if (!ECG_ADC_Delay_Timer_UsingFixedFunction)

        ECG_ADC_Delay_Timer_WriteCounter(ECG_ADC_Delay_Timer_backup.TimerUdb);
        ECG_ADC_Delay_Timer_STATUS_MASK =ECG_ADC_Delay_Timer_backup.InterruptMaskValue;
        #if (ECG_ADC_Delay_Timer_UsingHWCaptureCounter)
            ECG_ADC_Delay_Timer_SetCaptureCount(ECG_ADC_Delay_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED)
            ECG_ADC_Delay_Timer_WriteControlRegister(ECG_ADC_Delay_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: ECG_ADC_Delay_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  ECG_ADC_Delay_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void ECG_ADC_Delay_Timer_Sleep(void) 
{
    #if(!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(ECG_ADC_Delay_Timer_CTRL_ENABLE == (ECG_ADC_Delay_Timer_CONTROL & ECG_ADC_Delay_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            ECG_ADC_Delay_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            ECG_ADC_Delay_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    ECG_ADC_Delay_Timer_Stop();
    ECG_ADC_Delay_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: ECG_ADC_Delay_Timer_Wakeup
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
*  ECG_ADC_Delay_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ECG_ADC_Delay_Timer_Wakeup(void) 
{
    ECG_ADC_Delay_Timer_RestoreConfig();
    #if(!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED)
        if(ECG_ADC_Delay_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                ECG_ADC_Delay_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
