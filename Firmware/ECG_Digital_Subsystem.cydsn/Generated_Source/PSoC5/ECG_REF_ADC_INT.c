/*******************************************************************************
* File Name: ECG_REF_ADC_INT.c
* Version 3.0
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ECG_REF_ADC.h"



/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(ECG_REF_ADC_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ECG_REF_ADC_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( ECG_REF_ADC_ISR )
    {
        #ifdef ECG_REF_ADC_ISR_INTERRUPT_CALLBACK
            ECG_REF_ADC_ISR_InterruptCallback();
        #endif /* ECG_REF_ADC_ISR_INTERRUPT_CALLBACK */          

        
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */

          /* `#END`  */
    }

#endif   /* End ECG_REF_ADC_IRQ_REMOVE */

/* [] END OF FILE */
