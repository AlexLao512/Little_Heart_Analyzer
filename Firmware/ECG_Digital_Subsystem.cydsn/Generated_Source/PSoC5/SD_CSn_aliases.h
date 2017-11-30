/*******************************************************************************
* File Name: SD_CSn.h  
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

#if !defined(CY_PINS_SD_CSn_ALIASES_H) /* Pins SD_CSn_ALIASES_H */
#define CY_PINS_SD_CSn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define SD_CSn_0			(SD_CSn__0__PC)
#define SD_CSn_0_INTR	((uint16)((uint16)0x0001u << SD_CSn__0__SHIFT))

#define SD_CSn_INTR_ALL	 ((uint16)(SD_CSn_0_INTR))

#endif /* End Pins SD_CSn_ALIASES_H */


/* [] END OF FILE */
