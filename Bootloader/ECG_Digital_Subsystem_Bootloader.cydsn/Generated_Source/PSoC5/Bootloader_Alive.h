/*******************************************************************************
* File Name: Bootloader_Alive.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Bootloader_Alive_H)
#define CY_CLOCK_Bootloader_Alive_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Bootloader_Alive_Start(void) ;
void Bootloader_Alive_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Bootloader_Alive_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Bootloader_Alive_StandbyPower(uint8 state) ;
void Bootloader_Alive_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Bootloader_Alive_GetDividerRegister(void) ;
void Bootloader_Alive_SetModeRegister(uint8 modeBitMask) ;
void Bootloader_Alive_ClearModeRegister(uint8 modeBitMask) ;
uint8 Bootloader_Alive_GetModeRegister(void) ;
void Bootloader_Alive_SetSourceRegister(uint8 clkSource) ;
uint8 Bootloader_Alive_GetSourceRegister(void) ;
#if defined(Bootloader_Alive__CFG3)
void Bootloader_Alive_SetPhaseRegister(uint8 clkPhase) ;
uint8 Bootloader_Alive_GetPhaseRegister(void) ;
#endif /* defined(Bootloader_Alive__CFG3) */

#define Bootloader_Alive_Enable()                       Bootloader_Alive_Start()
#define Bootloader_Alive_Disable()                      Bootloader_Alive_Stop()
#define Bootloader_Alive_SetDivider(clkDivider)         Bootloader_Alive_SetDividerRegister(clkDivider, 1u)
#define Bootloader_Alive_SetDividerValue(clkDivider)    Bootloader_Alive_SetDividerRegister((clkDivider) - 1u, 1u)
#define Bootloader_Alive_SetMode(clkMode)               Bootloader_Alive_SetModeRegister(clkMode)
#define Bootloader_Alive_SetSource(clkSource)           Bootloader_Alive_SetSourceRegister(clkSource)
#if defined(Bootloader_Alive__CFG3)
#define Bootloader_Alive_SetPhase(clkPhase)             Bootloader_Alive_SetPhaseRegister(clkPhase)
#define Bootloader_Alive_SetPhaseValue(clkPhase)        Bootloader_Alive_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Bootloader_Alive__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Bootloader_Alive_CLKEN              (* (reg8 *) Bootloader_Alive__PM_ACT_CFG)
#define Bootloader_Alive_CLKEN_PTR          ((reg8 *) Bootloader_Alive__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Bootloader_Alive_CLKSTBY            (* (reg8 *) Bootloader_Alive__PM_STBY_CFG)
#define Bootloader_Alive_CLKSTBY_PTR        ((reg8 *) Bootloader_Alive__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Bootloader_Alive_DIV_LSB            (* (reg8 *) Bootloader_Alive__CFG0)
#define Bootloader_Alive_DIV_LSB_PTR        ((reg8 *) Bootloader_Alive__CFG0)
#define Bootloader_Alive_DIV_PTR            ((reg16 *) Bootloader_Alive__CFG0)

/* Clock MSB divider configuration register. */
#define Bootloader_Alive_DIV_MSB            (* (reg8 *) Bootloader_Alive__CFG1)
#define Bootloader_Alive_DIV_MSB_PTR        ((reg8 *) Bootloader_Alive__CFG1)

/* Mode and source configuration register */
#define Bootloader_Alive_MOD_SRC            (* (reg8 *) Bootloader_Alive__CFG2)
#define Bootloader_Alive_MOD_SRC_PTR        ((reg8 *) Bootloader_Alive__CFG2)

#if defined(Bootloader_Alive__CFG3)
/* Analog clock phase configuration register */
#define Bootloader_Alive_PHASE              (* (reg8 *) Bootloader_Alive__CFG3)
#define Bootloader_Alive_PHASE_PTR          ((reg8 *) Bootloader_Alive__CFG3)
#endif /* defined(Bootloader_Alive__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Bootloader_Alive_CLKEN_MASK         Bootloader_Alive__PM_ACT_MSK
#define Bootloader_Alive_CLKSTBY_MASK       Bootloader_Alive__PM_STBY_MSK

/* CFG2 field masks */
#define Bootloader_Alive_SRC_SEL_MSK        Bootloader_Alive__CFG2_SRC_SEL_MASK
#define Bootloader_Alive_MODE_MASK          (~(Bootloader_Alive_SRC_SEL_MSK))

#if defined(Bootloader_Alive__CFG3)
/* CFG3 phase mask */
#define Bootloader_Alive_PHASE_MASK         Bootloader_Alive__CFG3_PHASE_DLY_MASK
#endif /* defined(Bootloader_Alive__CFG3) */

#endif /* CY_CLOCK_Bootloader_Alive_H */


/* [] END OF FILE */
