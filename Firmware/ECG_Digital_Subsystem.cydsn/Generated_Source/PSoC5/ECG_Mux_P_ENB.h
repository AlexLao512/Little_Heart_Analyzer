/*******************************************************************************
* File Name: ECG_Mux_P_ENB.h  
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

#if !defined(CY_PINS_ECG_Mux_P_ENB_H) /* Pins ECG_Mux_P_ENB_H */
#define CY_PINS_ECG_Mux_P_ENB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ECG_Mux_P_ENB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ECG_Mux_P_ENB__PORT == 15 && ((ECG_Mux_P_ENB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ECG_Mux_P_ENB_Write(uint8 value);
void    ECG_Mux_P_ENB_SetDriveMode(uint8 mode);
uint8   ECG_Mux_P_ENB_ReadDataReg(void);
uint8   ECG_Mux_P_ENB_Read(void);
void    ECG_Mux_P_ENB_SetInterruptMode(uint16 position, uint16 mode);
uint8   ECG_Mux_P_ENB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ECG_Mux_P_ENB_SetDriveMode() function.
     *  @{
     */
        #define ECG_Mux_P_ENB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ECG_Mux_P_ENB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ECG_Mux_P_ENB_DM_RES_UP          PIN_DM_RES_UP
        #define ECG_Mux_P_ENB_DM_RES_DWN         PIN_DM_RES_DWN
        #define ECG_Mux_P_ENB_DM_OD_LO           PIN_DM_OD_LO
        #define ECG_Mux_P_ENB_DM_OD_HI           PIN_DM_OD_HI
        #define ECG_Mux_P_ENB_DM_STRONG          PIN_DM_STRONG
        #define ECG_Mux_P_ENB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ECG_Mux_P_ENB_MASK               ECG_Mux_P_ENB__MASK
#define ECG_Mux_P_ENB_SHIFT              ECG_Mux_P_ENB__SHIFT
#define ECG_Mux_P_ENB_WIDTH              1u

/* Interrupt constants */
#if defined(ECG_Mux_P_ENB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ECG_Mux_P_ENB_SetInterruptMode() function.
     *  @{
     */
        #define ECG_Mux_P_ENB_INTR_NONE      (uint16)(0x0000u)
        #define ECG_Mux_P_ENB_INTR_RISING    (uint16)(0x0001u)
        #define ECG_Mux_P_ENB_INTR_FALLING   (uint16)(0x0002u)
        #define ECG_Mux_P_ENB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ECG_Mux_P_ENB_INTR_MASK      (0x01u) 
#endif /* (ECG_Mux_P_ENB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ECG_Mux_P_ENB_PS                     (* (reg8 *) ECG_Mux_P_ENB__PS)
/* Data Register */
#define ECG_Mux_P_ENB_DR                     (* (reg8 *) ECG_Mux_P_ENB__DR)
/* Port Number */
#define ECG_Mux_P_ENB_PRT_NUM                (* (reg8 *) ECG_Mux_P_ENB__PRT) 
/* Connect to Analog Globals */                                                  
#define ECG_Mux_P_ENB_AG                     (* (reg8 *) ECG_Mux_P_ENB__AG)                       
/* Analog MUX bux enable */
#define ECG_Mux_P_ENB_AMUX                   (* (reg8 *) ECG_Mux_P_ENB__AMUX) 
/* Bidirectional Enable */                                                        
#define ECG_Mux_P_ENB_BIE                    (* (reg8 *) ECG_Mux_P_ENB__BIE)
/* Bit-mask for Aliased Register Access */
#define ECG_Mux_P_ENB_BIT_MASK               (* (reg8 *) ECG_Mux_P_ENB__BIT_MASK)
/* Bypass Enable */
#define ECG_Mux_P_ENB_BYP                    (* (reg8 *) ECG_Mux_P_ENB__BYP)
/* Port wide control signals */                                                   
#define ECG_Mux_P_ENB_CTL                    (* (reg8 *) ECG_Mux_P_ENB__CTL)
/* Drive Modes */
#define ECG_Mux_P_ENB_DM0                    (* (reg8 *) ECG_Mux_P_ENB__DM0) 
#define ECG_Mux_P_ENB_DM1                    (* (reg8 *) ECG_Mux_P_ENB__DM1)
#define ECG_Mux_P_ENB_DM2                    (* (reg8 *) ECG_Mux_P_ENB__DM2) 
/* Input Buffer Disable Override */
#define ECG_Mux_P_ENB_INP_DIS                (* (reg8 *) ECG_Mux_P_ENB__INP_DIS)
/* LCD Common or Segment Drive */
#define ECG_Mux_P_ENB_LCD_COM_SEG            (* (reg8 *) ECG_Mux_P_ENB__LCD_COM_SEG)
/* Enable Segment LCD */
#define ECG_Mux_P_ENB_LCD_EN                 (* (reg8 *) ECG_Mux_P_ENB__LCD_EN)
/* Slew Rate Control */
#define ECG_Mux_P_ENB_SLW                    (* (reg8 *) ECG_Mux_P_ENB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ECG_Mux_P_ENB_PRTDSI__CAPS_SEL       (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ECG_Mux_P_ENB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ECG_Mux_P_ENB_PRTDSI__OE_SEL0        (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__OE_SEL0) 
#define ECG_Mux_P_ENB_PRTDSI__OE_SEL1        (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ECG_Mux_P_ENB_PRTDSI__OUT_SEL0       (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__OUT_SEL0) 
#define ECG_Mux_P_ENB_PRTDSI__OUT_SEL1       (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ECG_Mux_P_ENB_PRTDSI__SYNC_OUT       (* (reg8 *) ECG_Mux_P_ENB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ECG_Mux_P_ENB__SIO_CFG)
    #define ECG_Mux_P_ENB_SIO_HYST_EN        (* (reg8 *) ECG_Mux_P_ENB__SIO_HYST_EN)
    #define ECG_Mux_P_ENB_SIO_REG_HIFREQ     (* (reg8 *) ECG_Mux_P_ENB__SIO_REG_HIFREQ)
    #define ECG_Mux_P_ENB_SIO_CFG            (* (reg8 *) ECG_Mux_P_ENB__SIO_CFG)
    #define ECG_Mux_P_ENB_SIO_DIFF           (* (reg8 *) ECG_Mux_P_ENB__SIO_DIFF)
#endif /* (ECG_Mux_P_ENB__SIO_CFG) */

/* Interrupt Registers */
#if defined(ECG_Mux_P_ENB__INTSTAT)
    #define ECG_Mux_P_ENB_INTSTAT            (* (reg8 *) ECG_Mux_P_ENB__INTSTAT)
    #define ECG_Mux_P_ENB_SNAP               (* (reg8 *) ECG_Mux_P_ENB__SNAP)
    
	#define ECG_Mux_P_ENB_0_INTTYPE_REG 		(* (reg8 *) ECG_Mux_P_ENB__0__INTTYPE)
#endif /* (ECG_Mux_P_ENB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ECG_Mux_P_ENB_H */


/* [] END OF FILE */
