/*******************************************************************************
* File Name: Timer_Clock_Out.h  
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

#if !defined(CY_PINS_Timer_Clock_Out_H) /* Pins Timer_Clock_Out_H */
#define CY_PINS_Timer_Clock_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Timer_Clock_Out_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Timer_Clock_Out__PORT == 15 && ((Timer_Clock_Out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Timer_Clock_Out_Write(uint8 value);
void    Timer_Clock_Out_SetDriveMode(uint8 mode);
uint8   Timer_Clock_Out_ReadDataReg(void);
uint8   Timer_Clock_Out_Read(void);
void    Timer_Clock_Out_SetInterruptMode(uint16 position, uint16 mode);
uint8   Timer_Clock_Out_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Timer_Clock_Out_SetDriveMode() function.
     *  @{
     */
        #define Timer_Clock_Out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Timer_Clock_Out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Timer_Clock_Out_DM_RES_UP          PIN_DM_RES_UP
        #define Timer_Clock_Out_DM_RES_DWN         PIN_DM_RES_DWN
        #define Timer_Clock_Out_DM_OD_LO           PIN_DM_OD_LO
        #define Timer_Clock_Out_DM_OD_HI           PIN_DM_OD_HI
        #define Timer_Clock_Out_DM_STRONG          PIN_DM_STRONG
        #define Timer_Clock_Out_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Timer_Clock_Out_MASK               Timer_Clock_Out__MASK
#define Timer_Clock_Out_SHIFT              Timer_Clock_Out__SHIFT
#define Timer_Clock_Out_WIDTH              1u

/* Interrupt constants */
#if defined(Timer_Clock_Out__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Timer_Clock_Out_SetInterruptMode() function.
     *  @{
     */
        #define Timer_Clock_Out_INTR_NONE      (uint16)(0x0000u)
        #define Timer_Clock_Out_INTR_RISING    (uint16)(0x0001u)
        #define Timer_Clock_Out_INTR_FALLING   (uint16)(0x0002u)
        #define Timer_Clock_Out_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Timer_Clock_Out_INTR_MASK      (0x01u) 
#endif /* (Timer_Clock_Out__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Timer_Clock_Out_PS                     (* (reg8 *) Timer_Clock_Out__PS)
/* Data Register */
#define Timer_Clock_Out_DR                     (* (reg8 *) Timer_Clock_Out__DR)
/* Port Number */
#define Timer_Clock_Out_PRT_NUM                (* (reg8 *) Timer_Clock_Out__PRT) 
/* Connect to Analog Globals */                                                  
#define Timer_Clock_Out_AG                     (* (reg8 *) Timer_Clock_Out__AG)                       
/* Analog MUX bux enable */
#define Timer_Clock_Out_AMUX                   (* (reg8 *) Timer_Clock_Out__AMUX) 
/* Bidirectional Enable */                                                        
#define Timer_Clock_Out_BIE                    (* (reg8 *) Timer_Clock_Out__BIE)
/* Bit-mask for Aliased Register Access */
#define Timer_Clock_Out_BIT_MASK               (* (reg8 *) Timer_Clock_Out__BIT_MASK)
/* Bypass Enable */
#define Timer_Clock_Out_BYP                    (* (reg8 *) Timer_Clock_Out__BYP)
/* Port wide control signals */                                                   
#define Timer_Clock_Out_CTL                    (* (reg8 *) Timer_Clock_Out__CTL)
/* Drive Modes */
#define Timer_Clock_Out_DM0                    (* (reg8 *) Timer_Clock_Out__DM0) 
#define Timer_Clock_Out_DM1                    (* (reg8 *) Timer_Clock_Out__DM1)
#define Timer_Clock_Out_DM2                    (* (reg8 *) Timer_Clock_Out__DM2) 
/* Input Buffer Disable Override */
#define Timer_Clock_Out_INP_DIS                (* (reg8 *) Timer_Clock_Out__INP_DIS)
/* LCD Common or Segment Drive */
#define Timer_Clock_Out_LCD_COM_SEG            (* (reg8 *) Timer_Clock_Out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Timer_Clock_Out_LCD_EN                 (* (reg8 *) Timer_Clock_Out__LCD_EN)
/* Slew Rate Control */
#define Timer_Clock_Out_SLW                    (* (reg8 *) Timer_Clock_Out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Timer_Clock_Out_PRTDSI__CAPS_SEL       (* (reg8 *) Timer_Clock_Out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Timer_Clock_Out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Timer_Clock_Out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Timer_Clock_Out_PRTDSI__OE_SEL0        (* (reg8 *) Timer_Clock_Out__PRTDSI__OE_SEL0) 
#define Timer_Clock_Out_PRTDSI__OE_SEL1        (* (reg8 *) Timer_Clock_Out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Timer_Clock_Out_PRTDSI__OUT_SEL0       (* (reg8 *) Timer_Clock_Out__PRTDSI__OUT_SEL0) 
#define Timer_Clock_Out_PRTDSI__OUT_SEL1       (* (reg8 *) Timer_Clock_Out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Timer_Clock_Out_PRTDSI__SYNC_OUT       (* (reg8 *) Timer_Clock_Out__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Timer_Clock_Out__SIO_CFG)
    #define Timer_Clock_Out_SIO_HYST_EN        (* (reg8 *) Timer_Clock_Out__SIO_HYST_EN)
    #define Timer_Clock_Out_SIO_REG_HIFREQ     (* (reg8 *) Timer_Clock_Out__SIO_REG_HIFREQ)
    #define Timer_Clock_Out_SIO_CFG            (* (reg8 *) Timer_Clock_Out__SIO_CFG)
    #define Timer_Clock_Out_SIO_DIFF           (* (reg8 *) Timer_Clock_Out__SIO_DIFF)
#endif /* (Timer_Clock_Out__SIO_CFG) */

/* Interrupt Registers */
#if defined(Timer_Clock_Out__INTSTAT)
    #define Timer_Clock_Out_INTSTAT            (* (reg8 *) Timer_Clock_Out__INTSTAT)
    #define Timer_Clock_Out_SNAP               (* (reg8 *) Timer_Clock_Out__SNAP)
    
	#define Timer_Clock_Out_0_INTTYPE_REG 		(* (reg8 *) Timer_Clock_Out__0__INTTYPE)
#endif /* (Timer_Clock_Out__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Timer_Clock_Out_H */


/* [] END OF FILE */
