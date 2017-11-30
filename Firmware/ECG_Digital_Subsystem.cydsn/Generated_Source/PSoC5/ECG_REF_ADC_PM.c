/*******************************************************************************
* File Name: ECG_REF_ADC_PM.c
* Version 3.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ECG_REF_ADC.h"


/***************************************
* Local data allocation
***************************************/

static ECG_REF_ADC_BACKUP_STRUCT  ECG_REF_ADC_backup =
{
    ECG_REF_ADC_DISABLED
};


/*******************************************************************************
* Function Name: ECG_REF_ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ECG_REF_ADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ECG_REF_ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ECG_REF_ADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ECG_REF_ADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ECG_REF_ADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECG_REF_ADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ECG_REF_ADC_Sleep(void)
{
    if((ECG_REF_ADC_PWRMGR_SAR_REG  & ECG_REF_ADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((ECG_REF_ADC_SAR_CSR0_REG & ECG_REF_ADC_SAR_SOF_START_CONV) != 0u)
        {
            ECG_REF_ADC_backup.enableState = ECG_REF_ADC_ENABLED | ECG_REF_ADC_STARTED;
        }
        else
        {
            ECG_REF_ADC_backup.enableState = ECG_REF_ADC_ENABLED;
        }
        ECG_REF_ADC_Stop();
    }
    else
    {
        ECG_REF_ADC_backup.enableState = ECG_REF_ADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ECG_REF_ADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ECG_REF_ADC_Sleep() was called. If the component was enabled before the
*  ECG_REF_ADC_Sleep() function was called, the
*  ECG_REF_ADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECG_REF_ADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ECG_REF_ADC_Wakeup(void)
{
    if(ECG_REF_ADC_backup.enableState != ECG_REF_ADC_DISABLED)
    {
        ECG_REF_ADC_Enable();
        #if(ECG_REF_ADC_DEFAULT_CONV_MODE != ECG_REF_ADC__HARDWARE_TRIGGER)
            if((ECG_REF_ADC_backup.enableState & ECG_REF_ADC_STARTED) != 0u)
            {
                ECG_REF_ADC_StartConvert();
            }
        #endif /* End ECG_REF_ADC_DEFAULT_CONV_MODE != ECG_REF_ADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
