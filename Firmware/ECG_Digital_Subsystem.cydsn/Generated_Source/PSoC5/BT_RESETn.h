/*******************************************************************************
* File Name: BT_RESETn.h  
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

#if !defined(CY_PINS_BT_RESETn_H) /* Pins BT_RESETn_H */
#define CY_PINS_BT_RESETn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BT_RESETn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BT_RESETn__PORT == 15 && ((BT_RESETn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BT_RESETn_Write(uint8 value);
void    BT_RESETn_SetDriveMode(uint8 mode);
uint8   BT_RESETn_ReadDataReg(void);
uint8   BT_RESETn_Read(void);
void    BT_RESETn_SetInterruptMode(uint16 position, uint16 mode);
uint8   BT_RESETn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BT_RESETn_SetDriveMode() function.
     *  @{
     */
        #define BT_RESETn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BT_RESETn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BT_RESETn_DM_RES_UP          PIN_DM_RES_UP
        #define BT_RESETn_DM_RES_DWN         PIN_DM_RES_DWN
        #define BT_RESETn_DM_OD_LO           PIN_DM_OD_LO
        #define BT_RESETn_DM_OD_HI           PIN_DM_OD_HI
        #define BT_RESETn_DM_STRONG          PIN_DM_STRONG
        #define BT_RESETn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BT_RESETn_MASK               BT_RESETn__MASK
#define BT_RESETn_SHIFT              BT_RESETn__SHIFT
#define BT_RESETn_WIDTH              1u

/* Interrupt constants */
#if defined(BT_RESETn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BT_RESETn_SetInterruptMode() function.
     *  @{
     */
        #define BT_RESETn_INTR_NONE      (uint16)(0x0000u)
        #define BT_RESETn_INTR_RISING    (uint16)(0x0001u)
        #define BT_RESETn_INTR_FALLING   (uint16)(0x0002u)
        #define BT_RESETn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BT_RESETn_INTR_MASK      (0x01u) 
#endif /* (BT_RESETn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BT_RESETn_PS                     (* (reg8 *) BT_RESETn__PS)
/* Data Register */
#define BT_RESETn_DR                     (* (reg8 *) BT_RESETn__DR)
/* Port Number */
#define BT_RESETn_PRT_NUM                (* (reg8 *) BT_RESETn__PRT) 
/* Connect to Analog Globals */                                                  
#define BT_RESETn_AG                     (* (reg8 *) BT_RESETn__AG)                       
/* Analog MUX bux enable */
#define BT_RESETn_AMUX                   (* (reg8 *) BT_RESETn__AMUX) 
/* Bidirectional Enable */                                                        
#define BT_RESETn_BIE                    (* (reg8 *) BT_RESETn__BIE)
/* Bit-mask for Aliased Register Access */
#define BT_RESETn_BIT_MASK               (* (reg8 *) BT_RESETn__BIT_MASK)
/* Bypass Enable */
#define BT_RESETn_BYP                    (* (reg8 *) BT_RESETn__BYP)
/* Port wide control signals */                                                   
#define BT_RESETn_CTL                    (* (reg8 *) BT_RESETn__CTL)
/* Drive Modes */
#define BT_RESETn_DM0                    (* (reg8 *) BT_RESETn__DM0) 
#define BT_RESETn_DM1                    (* (reg8 *) BT_RESETn__DM1)
#define BT_RESETn_DM2                    (* (reg8 *) BT_RESETn__DM2) 
/* Input Buffer Disable Override */
#define BT_RESETn_INP_DIS                (* (reg8 *) BT_RESETn__INP_DIS)
/* LCD Common or Segment Drive */
#define BT_RESETn_LCD_COM_SEG            (* (reg8 *) BT_RESETn__LCD_COM_SEG)
/* Enable Segment LCD */
#define BT_RESETn_LCD_EN                 (* (reg8 *) BT_RESETn__LCD_EN)
/* Slew Rate Control */
#define BT_RESETn_SLW                    (* (reg8 *) BT_RESETn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BT_RESETn_PRTDSI__CAPS_SEL       (* (reg8 *) BT_RESETn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BT_RESETn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BT_RESETn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BT_RESETn_PRTDSI__OE_SEL0        (* (reg8 *) BT_RESETn__PRTDSI__OE_SEL0) 
#define BT_RESETn_PRTDSI__OE_SEL1        (* (reg8 *) BT_RESETn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BT_RESETn_PRTDSI__OUT_SEL0       (* (reg8 *) BT_RESETn__PRTDSI__OUT_SEL0) 
#define BT_RESETn_PRTDSI__OUT_SEL1       (* (reg8 *) BT_RESETn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BT_RESETn_PRTDSI__SYNC_OUT       (* (reg8 *) BT_RESETn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BT_RESETn__SIO_CFG)
    #define BT_RESETn_SIO_HYST_EN        (* (reg8 *) BT_RESETn__SIO_HYST_EN)
    #define BT_RESETn_SIO_REG_HIFREQ     (* (reg8 *) BT_RESETn__SIO_REG_HIFREQ)
    #define BT_RESETn_SIO_CFG            (* (reg8 *) BT_RESETn__SIO_CFG)
    #define BT_RESETn_SIO_DIFF           (* (reg8 *) BT_RESETn__SIO_DIFF)
#endif /* (BT_RESETn__SIO_CFG) */

/* Interrupt Registers */
#if defined(BT_RESETn__INTSTAT)
    #define BT_RESETn_INTSTAT            (* (reg8 *) BT_RESETn__INTSTAT)
    #define BT_RESETn_SNAP               (* (reg8 *) BT_RESETn__SNAP)
    
	#define BT_RESETn_0_INTTYPE_REG 		(* (reg8 *) BT_RESETn__0__INTTYPE)
#endif /* (BT_RESETn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BT_RESETn_H */


/* [] END OF FILE */
