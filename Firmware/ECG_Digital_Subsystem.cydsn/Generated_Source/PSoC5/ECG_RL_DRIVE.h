/*******************************************************************************
* File Name: ECG_RL_DRIVE.h  
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

#if !defined(CY_PINS_ECG_RL_DRIVE_H) /* Pins ECG_RL_DRIVE_H */
#define CY_PINS_ECG_RL_DRIVE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ECG_RL_DRIVE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ECG_RL_DRIVE__PORT == 15 && ((ECG_RL_DRIVE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ECG_RL_DRIVE_Write(uint8 value);
void    ECG_RL_DRIVE_SetDriveMode(uint8 mode);
uint8   ECG_RL_DRIVE_ReadDataReg(void);
uint8   ECG_RL_DRIVE_Read(void);
void    ECG_RL_DRIVE_SetInterruptMode(uint16 position, uint16 mode);
uint8   ECG_RL_DRIVE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ECG_RL_DRIVE_SetDriveMode() function.
     *  @{
     */
        #define ECG_RL_DRIVE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ECG_RL_DRIVE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ECG_RL_DRIVE_DM_RES_UP          PIN_DM_RES_UP
        #define ECG_RL_DRIVE_DM_RES_DWN         PIN_DM_RES_DWN
        #define ECG_RL_DRIVE_DM_OD_LO           PIN_DM_OD_LO
        #define ECG_RL_DRIVE_DM_OD_HI           PIN_DM_OD_HI
        #define ECG_RL_DRIVE_DM_STRONG          PIN_DM_STRONG
        #define ECG_RL_DRIVE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ECG_RL_DRIVE_MASK               ECG_RL_DRIVE__MASK
#define ECG_RL_DRIVE_SHIFT              ECG_RL_DRIVE__SHIFT
#define ECG_RL_DRIVE_WIDTH              1u

/* Interrupt constants */
#if defined(ECG_RL_DRIVE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ECG_RL_DRIVE_SetInterruptMode() function.
     *  @{
     */
        #define ECG_RL_DRIVE_INTR_NONE      (uint16)(0x0000u)
        #define ECG_RL_DRIVE_INTR_RISING    (uint16)(0x0001u)
        #define ECG_RL_DRIVE_INTR_FALLING   (uint16)(0x0002u)
        #define ECG_RL_DRIVE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ECG_RL_DRIVE_INTR_MASK      (0x01u) 
#endif /* (ECG_RL_DRIVE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ECG_RL_DRIVE_PS                     (* (reg8 *) ECG_RL_DRIVE__PS)
/* Data Register */
#define ECG_RL_DRIVE_DR                     (* (reg8 *) ECG_RL_DRIVE__DR)
/* Port Number */
#define ECG_RL_DRIVE_PRT_NUM                (* (reg8 *) ECG_RL_DRIVE__PRT) 
/* Connect to Analog Globals */                                                  
#define ECG_RL_DRIVE_AG                     (* (reg8 *) ECG_RL_DRIVE__AG)                       
/* Analog MUX bux enable */
#define ECG_RL_DRIVE_AMUX                   (* (reg8 *) ECG_RL_DRIVE__AMUX) 
/* Bidirectional Enable */                                                        
#define ECG_RL_DRIVE_BIE                    (* (reg8 *) ECG_RL_DRIVE__BIE)
/* Bit-mask for Aliased Register Access */
#define ECG_RL_DRIVE_BIT_MASK               (* (reg8 *) ECG_RL_DRIVE__BIT_MASK)
/* Bypass Enable */
#define ECG_RL_DRIVE_BYP                    (* (reg8 *) ECG_RL_DRIVE__BYP)
/* Port wide control signals */                                                   
#define ECG_RL_DRIVE_CTL                    (* (reg8 *) ECG_RL_DRIVE__CTL)
/* Drive Modes */
#define ECG_RL_DRIVE_DM0                    (* (reg8 *) ECG_RL_DRIVE__DM0) 
#define ECG_RL_DRIVE_DM1                    (* (reg8 *) ECG_RL_DRIVE__DM1)
#define ECG_RL_DRIVE_DM2                    (* (reg8 *) ECG_RL_DRIVE__DM2) 
/* Input Buffer Disable Override */
#define ECG_RL_DRIVE_INP_DIS                (* (reg8 *) ECG_RL_DRIVE__INP_DIS)
/* LCD Common or Segment Drive */
#define ECG_RL_DRIVE_LCD_COM_SEG            (* (reg8 *) ECG_RL_DRIVE__LCD_COM_SEG)
/* Enable Segment LCD */
#define ECG_RL_DRIVE_LCD_EN                 (* (reg8 *) ECG_RL_DRIVE__LCD_EN)
/* Slew Rate Control */
#define ECG_RL_DRIVE_SLW                    (* (reg8 *) ECG_RL_DRIVE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ECG_RL_DRIVE_PRTDSI__CAPS_SEL       (* (reg8 *) ECG_RL_DRIVE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ECG_RL_DRIVE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ECG_RL_DRIVE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ECG_RL_DRIVE_PRTDSI__OE_SEL0        (* (reg8 *) ECG_RL_DRIVE__PRTDSI__OE_SEL0) 
#define ECG_RL_DRIVE_PRTDSI__OE_SEL1        (* (reg8 *) ECG_RL_DRIVE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ECG_RL_DRIVE_PRTDSI__OUT_SEL0       (* (reg8 *) ECG_RL_DRIVE__PRTDSI__OUT_SEL0) 
#define ECG_RL_DRIVE_PRTDSI__OUT_SEL1       (* (reg8 *) ECG_RL_DRIVE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ECG_RL_DRIVE_PRTDSI__SYNC_OUT       (* (reg8 *) ECG_RL_DRIVE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ECG_RL_DRIVE__SIO_CFG)
    #define ECG_RL_DRIVE_SIO_HYST_EN        (* (reg8 *) ECG_RL_DRIVE__SIO_HYST_EN)
    #define ECG_RL_DRIVE_SIO_REG_HIFREQ     (* (reg8 *) ECG_RL_DRIVE__SIO_REG_HIFREQ)
    #define ECG_RL_DRIVE_SIO_CFG            (* (reg8 *) ECG_RL_DRIVE__SIO_CFG)
    #define ECG_RL_DRIVE_SIO_DIFF           (* (reg8 *) ECG_RL_DRIVE__SIO_DIFF)
#endif /* (ECG_RL_DRIVE__SIO_CFG) */

/* Interrupt Registers */
#if defined(ECG_RL_DRIVE__INTSTAT)
    #define ECG_RL_DRIVE_INTSTAT            (* (reg8 *) ECG_RL_DRIVE__INTSTAT)
    #define ECG_RL_DRIVE_SNAP               (* (reg8 *) ECG_RL_DRIVE__SNAP)
    
	#define ECG_RL_DRIVE_0_INTTYPE_REG 		(* (reg8 *) ECG_RL_DRIVE__0__INTTYPE)
#endif /* (ECG_RL_DRIVE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ECG_RL_DRIVE_H */


/* [] END OF FILE */
