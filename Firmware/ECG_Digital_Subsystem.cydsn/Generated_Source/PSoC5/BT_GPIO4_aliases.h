/*******************************************************************************
* File Name: BT_GPIO4.h  
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

#if !defined(CY_PINS_BT_GPIO4_ALIASES_H) /* Pins BT_GPIO4_ALIASES_H */
#define CY_PINS_BT_GPIO4_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define BT_GPIO4_0			(BT_GPIO4__0__PC)
#define BT_GPIO4_0_INTR	((uint16)((uint16)0x0001u << BT_GPIO4__0__SHIFT))

#define BT_GPIO4_INTR_ALL	 ((uint16)(BT_GPIO4_0_INTR))

#endif /* End Pins BT_GPIO4_ALIASES_H */


/* [] END OF FILE */