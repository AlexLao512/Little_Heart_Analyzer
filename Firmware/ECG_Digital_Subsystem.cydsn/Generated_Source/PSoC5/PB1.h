/*******************************************************************************
* File Name: PB1.h  
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

#if !defined(CY_PINS_PB1_H) /* Pins PB1_H */
#define CY_PINS_PB1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PB1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PB1__PORT == 15 && ((PB1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PB1_Write(uint8 value);
void    PB1_SetDriveMode(uint8 mode);
uint8   PB1_ReadDataReg(void);
uint8   PB1_Read(void);
void    PB1_SetInterruptMode(uint16 position, uint16 mode);
uint8   PB1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PB1_SetDriveMode() function.
     *  @{
     */
        #define PB1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PB1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PB1_DM_RES_UP          PIN_DM_RES_UP
        #define PB1_DM_RES_DWN         PIN_DM_RES_DWN
        #define PB1_DM_OD_LO           PIN_DM_OD_LO
        #define PB1_DM_OD_HI           PIN_DM_OD_HI
        #define PB1_DM_STRONG          PIN_DM_STRONG
        #define PB1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PB1_MASK               PB1__MASK
#define PB1_SHIFT              PB1__SHIFT
#define PB1_WIDTH              1u

/* Interrupt constants */
#if defined(PB1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PB1_SetInterruptMode() function.
     *  @{
     */
        #define PB1_INTR_NONE      (uint16)(0x0000u)
        #define PB1_INTR_RISING    (uint16)(0x0001u)
        #define PB1_INTR_FALLING   (uint16)(0x0002u)
        #define PB1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PB1_INTR_MASK      (0x01u) 
#endif /* (PB1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PB1_PS                     (* (reg8 *) PB1__PS)
/* Data Register */
#define PB1_DR                     (* (reg8 *) PB1__DR)
/* Port Number */
#define PB1_PRT_NUM                (* (reg8 *) PB1__PRT) 
/* Connect to Analog Globals */                                                  
#define PB1_AG                     (* (reg8 *) PB1__AG)                       
/* Analog MUX bux enable */
#define PB1_AMUX                   (* (reg8 *) PB1__AMUX) 
/* Bidirectional Enable */                                                        
#define PB1_BIE                    (* (reg8 *) PB1__BIE)
/* Bit-mask for Aliased Register Access */
#define PB1_BIT_MASK               (* (reg8 *) PB1__BIT_MASK)
/* Bypass Enable */
#define PB1_BYP                    (* (reg8 *) PB1__BYP)
/* Port wide control signals */                                                   
#define PB1_CTL                    (* (reg8 *) PB1__CTL)
/* Drive Modes */
#define PB1_DM0                    (* (reg8 *) PB1__DM0) 
#define PB1_DM1                    (* (reg8 *) PB1__DM1)
#define PB1_DM2                    (* (reg8 *) PB1__DM2) 
/* Input Buffer Disable Override */
#define PB1_INP_DIS                (* (reg8 *) PB1__INP_DIS)
/* LCD Common or Segment Drive */
#define PB1_LCD_COM_SEG            (* (reg8 *) PB1__LCD_COM_SEG)
/* Enable Segment LCD */
#define PB1_LCD_EN                 (* (reg8 *) PB1__LCD_EN)
/* Slew Rate Control */
#define PB1_SLW                    (* (reg8 *) PB1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PB1_PRTDSI__CAPS_SEL       (* (reg8 *) PB1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PB1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PB1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PB1_PRTDSI__OE_SEL0        (* (reg8 *) PB1__PRTDSI__OE_SEL0) 
#define PB1_PRTDSI__OE_SEL1        (* (reg8 *) PB1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PB1_PRTDSI__OUT_SEL0       (* (reg8 *) PB1__PRTDSI__OUT_SEL0) 
#define PB1_PRTDSI__OUT_SEL1       (* (reg8 *) PB1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PB1_PRTDSI__SYNC_OUT       (* (reg8 *) PB1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PB1__SIO_CFG)
    #define PB1_SIO_HYST_EN        (* (reg8 *) PB1__SIO_HYST_EN)
    #define PB1_SIO_REG_HIFREQ     (* (reg8 *) PB1__SIO_REG_HIFREQ)
    #define PB1_SIO_CFG            (* (reg8 *) PB1__SIO_CFG)
    #define PB1_SIO_DIFF           (* (reg8 *) PB1__SIO_DIFF)
#endif /* (PB1__SIO_CFG) */

/* Interrupt Registers */
#if defined(PB1__INTSTAT)
    #define PB1_INTSTAT            (* (reg8 *) PB1__INTSTAT)
    #define PB1_SNAP               (* (reg8 *) PB1__SNAP)
    
	#define PB1_0_INTTYPE_REG 		(* (reg8 *) PB1__0__INTTYPE)
#endif /* (PB1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PB1_H */


/* [] END OF FILE */
