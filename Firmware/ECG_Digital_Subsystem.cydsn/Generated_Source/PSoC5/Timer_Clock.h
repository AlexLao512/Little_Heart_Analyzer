/*******************************************************************************
* File Name: Timer_Clock.h
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

#if !defined(CY_CLOCK_Timer_Clock_H)
#define CY_CLOCK_Timer_Clock_H

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

void Timer_Clock_Start(void) ;
void Timer_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Timer_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Timer_Clock_StandbyPower(uint8 state) ;
void Timer_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Timer_Clock_GetDividerRegister(void) ;
void Timer_Clock_SetModeRegister(uint8 modeBitMask) ;
void Timer_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 Timer_Clock_GetModeRegister(void) ;
void Timer_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 Timer_Clock_GetSourceRegister(void) ;
#if defined(Timer_Clock__CFG3)
void Timer_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 Timer_Clock_GetPhaseRegister(void) ;
#endif /* defined(Timer_Clock__CFG3) */

#define Timer_Clock_Enable()                       Timer_Clock_Start()
#define Timer_Clock_Disable()                      Timer_Clock_Stop()
#define Timer_Clock_SetDivider(clkDivider)         Timer_Clock_SetDividerRegister(clkDivider, 1u)
#define Timer_Clock_SetDividerValue(clkDivider)    Timer_Clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define Timer_Clock_SetMode(clkMode)               Timer_Clock_SetModeRegister(clkMode)
#define Timer_Clock_SetSource(clkSource)           Timer_Clock_SetSourceRegister(clkSource)
#if defined(Timer_Clock__CFG3)
#define Timer_Clock_SetPhase(clkPhase)             Timer_Clock_SetPhaseRegister(clkPhase)
#define Timer_Clock_SetPhaseValue(clkPhase)        Timer_Clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Timer_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Timer_Clock_CLKEN              (* (reg8 *) Timer_Clock__PM_ACT_CFG)
#define Timer_Clock_CLKEN_PTR          ((reg8 *) Timer_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Timer_Clock_CLKSTBY            (* (reg8 *) Timer_Clock__PM_STBY_CFG)
#define Timer_Clock_CLKSTBY_PTR        ((reg8 *) Timer_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Timer_Clock_DIV_LSB            (* (reg8 *) Timer_Clock__CFG0)
#define Timer_Clock_DIV_LSB_PTR        ((reg8 *) Timer_Clock__CFG0)
#define Timer_Clock_DIV_PTR            ((reg16 *) Timer_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define Timer_Clock_DIV_MSB            (* (reg8 *) Timer_Clock__CFG1)
#define Timer_Clock_DIV_MSB_PTR        ((reg8 *) Timer_Clock__CFG1)

/* Mode and source configuration register */
#define Timer_Clock_MOD_SRC            (* (reg8 *) Timer_Clock__CFG2)
#define Timer_Clock_MOD_SRC_PTR        ((reg8 *) Timer_Clock__CFG2)

#if defined(Timer_Clock__CFG3)
/* Analog clock phase configuration register */
#define Timer_Clock_PHASE              (* (reg8 *) Timer_Clock__CFG3)
#define Timer_Clock_PHASE_PTR          ((reg8 *) Timer_Clock__CFG3)
#endif /* defined(Timer_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Timer_Clock_CLKEN_MASK         Timer_Clock__PM_ACT_MSK
#define Timer_Clock_CLKSTBY_MASK       Timer_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define Timer_Clock_SRC_SEL_MSK        Timer_Clock__CFG2_SRC_SEL_MASK
#define Timer_Clock_MODE_MASK          (~(Timer_Clock_SRC_SEL_MSK))

#if defined(Timer_Clock__CFG3)
/* CFG3 phase mask */
#define Timer_Clock_PHASE_MASK         Timer_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(Timer_Clock__CFG3) */

#endif /* CY_CLOCK_Timer_Clock_H */


/* [] END OF FILE */
