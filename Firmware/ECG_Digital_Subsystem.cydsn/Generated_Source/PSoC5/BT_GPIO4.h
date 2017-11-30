/*******************************************************************************
* File Name: BT_GPIO4.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BT_GPIO4_H) /* Pins BT_GPIO4_H */
#define CY_PINS_BT_GPIO4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BT_GPIO4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BT_GPIO4__PORT == 15 && ((BT_GPIO4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BT_GPIO4_Write(uint8 value);
void    BT_GPIO4_SetDriveMode(uint8 mode);
uint8   BT_GPIO4_ReadDataReg(void);
uint8   BT_GPIO4_Read(void);
void    BT_GPIO4_SetInterruptMode(uint16 position, uint16 mode);
uint8   BT_GPIO4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BT_GPIO4_SetDriveMode() function.
     *  @{
     */
        #define BT_GPIO4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BT_GPIO4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BT_GPIO4_DM_RES_UP          PIN_DM_RES_UP
        #define BT_GPIO4_DM_RES_DWN         PIN_DM_RES_DWN
        #define BT_GPIO4_DM_OD_LO           PIN_DM_OD_LO
        #define BT_GPIO4_DM_OD_HI           PIN_DM_OD_HI
        #define BT_GPIO4_DM_STRONG          PIN_DM_STRONG
        #define BT_GPIO4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BT_GPIO4_MASK               BT_GPIO4__MASK
#define BT_GPIO4_SHIFT              BT_GPIO4__SHIFT
#define BT_GPIO4_WIDTH              1u

/* Interrupt constants */
#if defined(BT_GPIO4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BT_GPIO4_SetInterruptMode() function.
     *  @{
     */
        #define BT_GPIO4_INTR_NONE      (uint16)(0x0000u)
        #define BT_GPIO4_INTR_RISING    (uint16)(0x0001u)
        #define BT_GPIO4_INTR_FALLING   (uint16)(0x0002u)
        #define BT_GPIO4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BT_GPIO4_INTR_MASK      (0x01u) 
#endif /* (BT_GPIO4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BT_GPIO4_PS                     (* (reg8 *) BT_GPIO4__PS)
/* Data Register */
#define BT_GPIO4_DR                     (* (reg8 *) BT_GPIO4__DR)
/* Port Number */
#define BT_GPIO4_PRT_NUM                (* (reg8 *) BT_GPIO4__PRT) 
/* Connect to Analog Globals */                                                  
#define BT_GPIO4_AG                     (* (reg8 *) BT_GPIO4__AG)                       
/* Analog MUX bux enable */
#define BT_GPIO4_AMUX                   (* (reg8 *) BT_GPIO4__AMUX) 
/* Bidirectional Enable */                                                        
#define BT_GPIO4_BIE                    (* (reg8 *) BT_GPIO4__BIE)
/* Bit-mask for Aliased Register Access */
#define BT_GPIO4_BIT_MASK               (* (reg8 *) BT_GPIO4__BIT_MASK)
/* Bypass Enable */
#define BT_GPIO4_BYP                    (* (reg8 *) BT_GPIO4__BYP)
/* Port wide control signals */                                                   
#define BT_GPIO4_CTL                    (* (reg8 *) BT_GPIO4__CTL)
/* Drive Modes */
#define BT_GPIO4_DM0                    (* (reg8 *) BT_GPIO4__DM0) 
#define BT_GPIO4_DM1                    (* (reg8 *) BT_GPIO4__DM1)
#define BT_GPIO4_DM2                    (* (reg8 *) BT_GPIO4__DM2) 
/* Input Buffer Disable Override */
#define BT_GPIO4_INP_DIS                (* (reg8 *) BT_GPIO4__INP_DIS)
/* LCD Common or Segment Drive */
#define BT_GPIO4_LCD_COM_SEG            (* (reg8 *) BT_GPIO4__LCD_COM_SEG)
/* Enable Segment LCD */
#define BT_GPIO4_LCD_EN                 (* (reg8 *) BT_GPIO4__LCD_EN)
/* Slew Rate Control */
#define BT_GPIO4_SLW                    (* (reg8 *) BT_GPIO4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BT_GPIO4_PRTDSI__CAPS_SEL       (* (reg8 *) BT_GPIO4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BT_GPIO4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BT_GPIO4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BT_GPIO4_PRTDSI__OE_SEL0        (* (reg8 *) BT_GPIO4__PRTDSI__OE_SEL0) 
#define BT_GPIO4_PRTDSI__OE_SEL1        (* (reg8 *) BT_GPIO4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BT_GPIO4_PRTDSI__OUT_SEL0       (* (reg8 *) BT_GPIO4__PRTDSI__OUT_SEL0) 
#define BT_GPIO4_PRTDSI__OUT_SEL1       (* (reg8 *) BT_GPIO4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BT_GPIO4_PRTDSI__SYNC_OUT       (* (reg8 *) BT_GPIO4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BT_GPIO4__SIO_CFG)
    #define BT_GPIO4_SIO_HYST_EN        (* (reg8 *) BT_GPIO4__SIO_HYST_EN)
    #define BT_GPIO4_SIO_REG_HIFREQ     (* (reg8 *) BT_GPIO4__SIO_REG_HIFREQ)
    #define BT_GPIO4_SIO_CFG            (* (reg8 *) BT_GPIO4__SIO_CFG)
    #define BT_GPIO4_SIO_DIFF           (* (reg8 *) BT_GPIO4__SIO_DIFF)
#endif /* (BT_GPIO4__SIO_CFG) */

/* Interrupt Registers */
#if defined(BT_GPIO4__INTSTAT)
    #define BT_GPIO4_INTSTAT            (* (reg8 *) BT_GPIO4__INTSTAT)
    #define BT_GPIO4_SNAP               (* (reg8 *) BT_GPIO4__SNAP)
    
	#define BT_GPIO4_0_INTTYPE_REG 		(* (reg8 *) BT_GPIO4__0__INTTYPE)
#endif /* (BT_GPIO4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BT_GPIO4_H */


/* [] END OF FILE */
