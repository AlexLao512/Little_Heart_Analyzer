/*******************************************************************************
* File Name: ECG_MuxControl_N.h  
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

#if !defined(CY_PINS_ECG_MuxControl_N_H) /* Pins ECG_MuxControl_N_H */
#define CY_PINS_ECG_MuxControl_N_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ECG_MuxControl_N_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ECG_MuxControl_N__PORT == 15 && ((ECG_MuxControl_N__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ECG_MuxControl_N_Write(uint8 value);
void    ECG_MuxControl_N_SetDriveMode(uint8 mode);
uint8   ECG_MuxControl_N_ReadDataReg(void);
uint8   ECG_MuxControl_N_Read(void);
void    ECG_MuxControl_N_SetInterruptMode(uint16 position, uint16 mode);
uint8   ECG_MuxControl_N_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ECG_MuxControl_N_SetDriveMode() function.
     *  @{
     */
        #define ECG_MuxControl_N_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ECG_MuxControl_N_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ECG_MuxControl_N_DM_RES_UP          PIN_DM_RES_UP
        #define ECG_MuxControl_N_DM_RES_DWN         PIN_DM_RES_DWN
        #define ECG_MuxControl_N_DM_OD_LO           PIN_DM_OD_LO
        #define ECG_MuxControl_N_DM_OD_HI           PIN_DM_OD_HI
        #define ECG_MuxControl_N_DM_STRONG          PIN_DM_STRONG
        #define ECG_MuxControl_N_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ECG_MuxControl_N_MASK               ECG_MuxControl_N__MASK
#define ECG_MuxControl_N_SHIFT              ECG_MuxControl_N__SHIFT
#define ECG_MuxControl_N_WIDTH              3u

/* Interrupt constants */
#if defined(ECG_MuxControl_N__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ECG_MuxControl_N_SetInterruptMode() function.
     *  @{
     */
        #define ECG_MuxControl_N_INTR_NONE      (uint16)(0x0000u)
        #define ECG_MuxControl_N_INTR_RISING    (uint16)(0x0001u)
        #define ECG_MuxControl_N_INTR_FALLING   (uint16)(0x0002u)
        #define ECG_MuxControl_N_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ECG_MuxControl_N_INTR_MASK      (0x01u) 
#endif /* (ECG_MuxControl_N__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ECG_MuxControl_N_PS                     (* (reg8 *) ECG_MuxControl_N__PS)
/* Data Register */
#define ECG_MuxControl_N_DR                     (* (reg8 *) ECG_MuxControl_N__DR)
/* Port Number */
#define ECG_MuxControl_N_PRT_NUM                (* (reg8 *) ECG_MuxControl_N__PRT) 
/* Connect to Analog Globals */                                                  
#define ECG_MuxControl_N_AG                     (* (reg8 *) ECG_MuxControl_N__AG)                       
/* Analog MUX bux enable */
#define ECG_MuxControl_N_AMUX                   (* (reg8 *) ECG_MuxControl_N__AMUX) 
/* Bidirectional Enable */                                                        
#define ECG_MuxControl_N_BIE                    (* (reg8 *) ECG_MuxControl_N__BIE)
/* Bit-mask for Aliased Register Access */
#define ECG_MuxControl_N_BIT_MASK               (* (reg8 *) ECG_MuxControl_N__BIT_MASK)
/* Bypass Enable */
#define ECG_MuxControl_N_BYP                    (* (reg8 *) ECG_MuxControl_N__BYP)
/* Port wide control signals */                                                   
#define ECG_MuxControl_N_CTL                    (* (reg8 *) ECG_MuxControl_N__CTL)
/* Drive Modes */
#define ECG_MuxControl_N_DM0                    (* (reg8 *) ECG_MuxControl_N__DM0) 
#define ECG_MuxControl_N_DM1                    (* (reg8 *) ECG_MuxControl_N__DM1)
#define ECG_MuxControl_N_DM2                    (* (reg8 *) ECG_MuxControl_N__DM2) 
/* Input Buffer Disable Override */
#define ECG_MuxControl_N_INP_DIS                (* (reg8 *) ECG_MuxControl_N__INP_DIS)
/* LCD Common or Segment Drive */
#define ECG_MuxControl_N_LCD_COM_SEG            (* (reg8 *) ECG_MuxControl_N__LCD_COM_SEG)
/* Enable Segment LCD */
#define ECG_MuxControl_N_LCD_EN                 (* (reg8 *) ECG_MuxControl_N__LCD_EN)
/* Slew Rate Control */
#define ECG_MuxControl_N_SLW                    (* (reg8 *) ECG_MuxControl_N__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ECG_MuxControl_N_PRTDSI__CAPS_SEL       (* (reg8 *) ECG_MuxControl_N__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ECG_MuxControl_N_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ECG_MuxControl_N__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ECG_MuxControl_N_PRTDSI__OE_SEL0        (* (reg8 *) ECG_MuxControl_N__PRTDSI__OE_SEL0) 
#define ECG_MuxControl_N_PRTDSI__OE_SEL1        (* (reg8 *) ECG_MuxControl_N__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ECG_MuxControl_N_PRTDSI__OUT_SEL0       (* (reg8 *) ECG_MuxControl_N__PRTDSI__OUT_SEL0) 
#define ECG_MuxControl_N_PRTDSI__OUT_SEL1       (* (reg8 *) ECG_MuxControl_N__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ECG_MuxControl_N_PRTDSI__SYNC_OUT       (* (reg8 *) ECG_MuxControl_N__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ECG_MuxControl_N__SIO_CFG)
    #define ECG_MuxControl_N_SIO_HYST_EN        (* (reg8 *) ECG_MuxControl_N__SIO_HYST_EN)
    #define ECG_MuxControl_N_SIO_REG_HIFREQ     (* (reg8 *) ECG_MuxControl_N__SIO_REG_HIFREQ)
    #define ECG_MuxControl_N_SIO_CFG            (* (reg8 *) ECG_MuxControl_N__SIO_CFG)
    #define ECG_MuxControl_N_SIO_DIFF           (* (reg8 *) ECG_MuxControl_N__SIO_DIFF)
#endif /* (ECG_MuxControl_N__SIO_CFG) */

/* Interrupt Registers */
#if defined(ECG_MuxControl_N__INTSTAT)
    #define ECG_MuxControl_N_INTSTAT            (* (reg8 *) ECG_MuxControl_N__INTSTAT)
    #define ECG_MuxControl_N_SNAP               (* (reg8 *) ECG_MuxControl_N__SNAP)
    
	#define ECG_MuxControl_N_0_INTTYPE_REG 		(* (reg8 *) ECG_MuxControl_N__0__INTTYPE)
	#define ECG_MuxControl_N_1_INTTYPE_REG 		(* (reg8 *) ECG_MuxControl_N__1__INTTYPE)
	#define ECG_MuxControl_N_2_INTTYPE_REG 		(* (reg8 *) ECG_MuxControl_N__2__INTTYPE)
#endif /* (ECG_MuxControl_N__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ECG_MuxControl_N_H */


/* [] END OF FILE */
