/*******************************************************************************
* File Name: ECG_MuxControl_P.h  
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

#if !defined(CY_PINS_ECG_MuxControl_P_ALIASES_H) /* Pins ECG_MuxControl_P_ALIASES_H */
#define CY_PINS_ECG_MuxControl_P_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define ECG_MuxControl_P_0			(ECG_MuxControl_P__0__PC)
#define ECG_MuxControl_P_0_INTR	((uint16)((uint16)0x0001u << ECG_MuxControl_P__0__SHIFT))

#define ECG_MuxControl_P_1			(ECG_MuxControl_P__1__PC)
#define ECG_MuxControl_P_1_INTR	((uint16)((uint16)0x0001u << ECG_MuxControl_P__1__SHIFT))

#define ECG_MuxControl_P_2			(ECG_MuxControl_P__2__PC)
#define ECG_MuxControl_P_2_INTR	((uint16)((uint16)0x0001u << ECG_MuxControl_P__2__SHIFT))

#define ECG_MuxControl_P_INTR_ALL	 ((uint16)(ECG_MuxControl_P_0_INTR| ECG_MuxControl_P_1_INTR| ECG_MuxControl_P_2_INTR))

#endif /* End Pins ECG_MuxControl_P_ALIASES_H */


/* [] END OF FILE */
