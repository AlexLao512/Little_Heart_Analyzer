/*******************************************************************************
* File Name: ECG_MuxControl_N.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ECG_MuxControl_N_ALIASES_H) /* Pins ECG_MuxControl_N_ALIASES_H */
#define CY_PINS_ECG_MuxControl_N_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define ECG_MuxControl_N_0			(ECG_MuxControl_N__0__PC)
#define ECG_MuxControl_N_0_INTR	((uint16)((uint16)0x0001u << ECG_MuxControl_N__0__SHIFT))

#define ECG_MuxControl_N_1			(ECG_MuxControl_N__1__PC)
#define ECG_MuxControl_N_1_INTR	((uint16)((uint16)0x0001u << ECG_MuxControl_N__1__SHIFT))

#define ECG_MuxControl_N_2			(ECG_MuxControl_N__2__PC)
#define ECG_MuxControl_N_2_INTR	((uint16)((uint16)0x0001u << ECG_MuxControl_N__2__SHIFT))

#define ECG_MuxControl_N_INTR_ALL	 ((uint16)(ECG_MuxControl_N_0_INTR| ECG_MuxControl_N_1_INTR| ECG_MuxControl_N_2_INTR))

#endif /* End Pins ECG_MuxControl_N_ALIASES_H */


/* [] END OF FILE */
