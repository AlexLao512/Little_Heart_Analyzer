/*******************************************************************************
* File Name: ECG_ADC_Delay_Timer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_ECG_ADC_Delay_Timer_H)
#define CY_Timer_v2_60_ECG_ADC_Delay_Timer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ECG_ADC_Delay_Timer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define ECG_ADC_Delay_Timer_Resolution                 8u
#define ECG_ADC_Delay_Timer_UsingFixedFunction         0u
#define ECG_ADC_Delay_Timer_UsingHWCaptureCounter      0u
#define ECG_ADC_Delay_Timer_SoftwareCaptureMode        0u
#define ECG_ADC_Delay_Timer_SoftwareTriggerMode        0u
#define ECG_ADC_Delay_Timer_UsingHWEnable              1u
#define ECG_ADC_Delay_Timer_EnableTriggerMode          1u
#define ECG_ADC_Delay_Timer_InterruptOnCaptureCount    0u
#define ECG_ADC_Delay_Timer_RunModeUsed                1u
#define ECG_ADC_Delay_Timer_ControlRegRemoved          1u

#if defined(ECG_ADC_Delay_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (ECG_ADC_Delay_Timer_UsingFixedFunction)
    #define ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End ECG_ADC_Delay_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!ECG_ADC_Delay_Timer_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (ECG_ADC_Delay_Timer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}ECG_ADC_Delay_Timer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    ECG_ADC_Delay_Timer_Start(void) ;
void    ECG_ADC_Delay_Timer_Stop(void) ;

void    ECG_ADC_Delay_Timer_SetInterruptMode(uint8 interruptMode) ;
uint8   ECG_ADC_Delay_Timer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define ECG_ADC_Delay_Timer_GetInterruptSource() ECG_ADC_Delay_Timer_ReadStatusRegister()

#if(!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED)
    uint8   ECG_ADC_Delay_Timer_ReadControlRegister(void) ;
    void    ECG_ADC_Delay_Timer_WriteControlRegister(uint8 control) ;
#endif /* (!ECG_ADC_Delay_Timer_UDB_CONTROL_REG_REMOVED) */

uint8  ECG_ADC_Delay_Timer_ReadPeriod(void) ;
void    ECG_ADC_Delay_Timer_WritePeriod(uint8 period) ;
uint8  ECG_ADC_Delay_Timer_ReadCounter(void) ;
void    ECG_ADC_Delay_Timer_WriteCounter(uint8 counter) ;
uint8  ECG_ADC_Delay_Timer_ReadCapture(void) ;
void    ECG_ADC_Delay_Timer_SoftwareCapture(void) ;

#if(!ECG_ADC_Delay_Timer_UsingFixedFunction) /* UDB Prototypes */
    #if (ECG_ADC_Delay_Timer_SoftwareCaptureMode)
        void    ECG_ADC_Delay_Timer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!ECG_ADC_Delay_Timer_UsingFixedFunction) */

    #if (ECG_ADC_Delay_Timer_SoftwareTriggerMode)
        void    ECG_ADC_Delay_Timer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (ECG_ADC_Delay_Timer_SoftwareTriggerMode) */

    #if (ECG_ADC_Delay_Timer_EnableTriggerMode)
        void    ECG_ADC_Delay_Timer_EnableTrigger(void) ;
        void    ECG_ADC_Delay_Timer_DisableTrigger(void) ;
    #endif /* (ECG_ADC_Delay_Timer_EnableTriggerMode) */


    #if(ECG_ADC_Delay_Timer_InterruptOnCaptureCount)
        void    ECG_ADC_Delay_Timer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (ECG_ADC_Delay_Timer_InterruptOnCaptureCount) */

    #if (ECG_ADC_Delay_Timer_UsingHWCaptureCounter)
        void    ECG_ADC_Delay_Timer_SetCaptureCount(uint8 captureCount) ;
        uint8   ECG_ADC_Delay_Timer_ReadCaptureCount(void) ;
    #endif /* (ECG_ADC_Delay_Timer_UsingHWCaptureCounter) */

    void ECG_ADC_Delay_Timer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void ECG_ADC_Delay_Timer_Init(void)          ;
void ECG_ADC_Delay_Timer_Enable(void)        ;
void ECG_ADC_Delay_Timer_SaveConfig(void)    ;
void ECG_ADC_Delay_Timer_RestoreConfig(void) ;
void ECG_ADC_Delay_Timer_Sleep(void)         ;
void ECG_ADC_Delay_Timer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define ECG_ADC_Delay_Timer__B_TIMER__CM_NONE 0
#define ECG_ADC_Delay_Timer__B_TIMER__CM_RISINGEDGE 1
#define ECG_ADC_Delay_Timer__B_TIMER__CM_FALLINGEDGE 2
#define ECG_ADC_Delay_Timer__B_TIMER__CM_EITHEREDGE 3
#define ECG_ADC_Delay_Timer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define ECG_ADC_Delay_Timer__B_TIMER__TM_NONE 0x00u
#define ECG_ADC_Delay_Timer__B_TIMER__TM_RISINGEDGE 0x04u
#define ECG_ADC_Delay_Timer__B_TIMER__TM_FALLINGEDGE 0x08u
#define ECG_ADC_Delay_Timer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define ECG_ADC_Delay_Timer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define ECG_ADC_Delay_Timer_INIT_PERIOD             19u
#define ECG_ADC_Delay_Timer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << ECG_ADC_Delay_Timer_CTRL_CAP_MODE_SHIFT))
#define ECG_ADC_Delay_Timer_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << ECG_ADC_Delay_Timer_CTRL_TRIG_MODE_SHIFT))
#if (ECG_ADC_Delay_Timer_UsingFixedFunction)
    #define ECG_ADC_Delay_Timer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define ECG_ADC_Delay_Timer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << ECG_ADC_Delay_Timer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (ECG_ADC_Delay_Timer_UsingFixedFunction) */
#define ECG_ADC_Delay_Timer_INIT_CAPTURE_COUNT      (2u)
#define ECG_ADC_Delay_Timer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << ECG_ADC_Delay_Timer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (ECG_ADC_Delay_Timer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define ECG_ADC_Delay_Timer_STATUS         (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define ECG_ADC_Delay_Timer_STATUS_MASK    (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__SR0 )
    #define ECG_ADC_Delay_Timer_CONTROL        (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__CFG0)
    #define ECG_ADC_Delay_Timer_CONTROL2       (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__CFG1)
    #define ECG_ADC_Delay_Timer_CONTROL2_PTR   ( (reg8 *) ECG_ADC_Delay_Timer_TimerHW__CFG1)
    #define ECG_ADC_Delay_Timer_RT1            (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__RT1)
    #define ECG_ADC_Delay_Timer_RT1_PTR        ( (reg8 *) ECG_ADC_Delay_Timer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define ECG_ADC_Delay_Timer_CONTROL3       (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__CFG2)
        #define ECG_ADC_Delay_Timer_CONTROL3_PTR   ( (reg8 *) ECG_ADC_Delay_Timer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ECG_ADC_Delay_Timer_GLOBAL_ENABLE  (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__PM_ACT_CFG)
    #define ECG_ADC_Delay_Timer_GLOBAL_STBY_ENABLE  (*(reg8 *) ECG_ADC_Delay_Timer_TimerHW__PM_STBY_CFG)

    #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg16 *) ECG_ADC_Delay_Timer_TimerHW__CAP0 )
    #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg16 *) ECG_ADC_Delay_Timer_TimerHW__CAP0 )
    #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg16 *) ECG_ADC_Delay_Timer_TimerHW__PER0 )
    #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg16 *) ECG_ADC_Delay_Timer_TimerHW__PER0 )
    #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg16 *) ECG_ADC_Delay_Timer_TimerHW__CNT_CMP0 )
    #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg16 *) ECG_ADC_Delay_Timer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define ECG_ADC_Delay_Timer_BLOCK_EN_MASK                     ECG_ADC_Delay_Timer_TimerHW__PM_ACT_MSK
    #define ECG_ADC_Delay_Timer_BLOCK_STBY_EN_MASK                ECG_ADC_Delay_Timer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define ECG_ADC_Delay_Timer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define ECG_ADC_Delay_Timer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define ECG_ADC_Delay_Timer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define ECG_ADC_Delay_Timer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define ECG_ADC_Delay_Timer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define ECG_ADC_Delay_Timer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ECG_ADC_Delay_Timer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define ECG_ADC_Delay_Timer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT                 0x01u
        #define ECG_ADC_Delay_Timer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define ECG_ADC_Delay_Timer_CTRL_RCOD_SHIFT        0x02u
        #define ECG_ADC_Delay_Timer_CTRL_ENBL_SHIFT        0x00u
        #define ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define ECG_ADC_Delay_Timer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define ECG_ADC_Delay_Timer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << ECG_ADC_Delay_Timer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define ECG_ADC_Delay_Timer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define ECG_ADC_Delay_Timer_CTRL_RCOD       ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_CTRL_RCOD_SHIFT))
        #define ECG_ADC_Delay_Timer_CTRL_ENBL       ((uint8)((uint8)0x80u << ECG_ADC_Delay_Timer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define ECG_ADC_Delay_Timer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define ECG_ADC_Delay_Timer_RT1_MASK                        ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_RT1_SHIFT))
    #define ECG_ADC_Delay_Timer_SYNC                            ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_RT1_SHIFT))
    #define ECG_ADC_Delay_Timer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define ECG_ADC_Delay_Timer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << ECG_ADC_Delay_Timer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define ECG_ADC_Delay_Timer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << ECG_ADC_Delay_Timer_SYNCDSI_SHIFT))

    #define ECG_ADC_Delay_Timer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT))
    #define ECG_ADC_Delay_Timer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT))
    #define ECG_ADC_Delay_Timer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << ECG_ADC_Delay_Timer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define ECG_ADC_Delay_Timer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK_SHIFT        (ECG_ADC_Delay_Timer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK_SHIFT   (ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define ECG_ADC_Delay_Timer_STATUS_TC                       ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_TC_SHIFT))
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define ECG_ADC_Delay_Timer_STATUS              (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define ECG_ADC_Delay_Timer_STATUS_MASK         (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define ECG_ADC_Delay_Timer_STATUS_AUX_CTRL     (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define ECG_ADC_Delay_Timer_CONTROL             (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(ECG_ADC_Delay_Timer_Resolution <= 8u) /* 8-bit Timer */
        #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(ECG_ADC_Delay_Timer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg16 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(ECG_ADC_Delay_Timer_Resolution <= 24u)/* 24-bit Timer */
        #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB         (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define ECG_ADC_Delay_Timer_CAPTURE_LSB_PTR       ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB          (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define ECG_ADC_Delay_Timer_PERIOD_LSB_PTR        ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB         (* (reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR       ((reg32 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define ECG_ADC_Delay_Timer_COUNTER_LSB_PTR_8BIT       ((reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (ECG_ADC_Delay_Timer_UsingHWCaptureCounter)
        #define ECG_ADC_Delay_Timer_CAP_COUNT              (*(reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define ECG_ADC_Delay_Timer_CAP_COUNT_PTR          ( (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define ECG_ADC_Delay_Timer_CAPTURE_COUNT_CTRL     (*(reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define ECG_ADC_Delay_Timer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) ECG_ADC_Delay_Timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (ECG_ADC_Delay_Timer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define ECG_ADC_Delay_Timer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define ECG_ADC_Delay_Timer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_CTRL_INTCNT_SHIFT))
    #define ECG_ADC_Delay_Timer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_CTRL_TRIG_MODE_SHIFT))
    #define ECG_ADC_Delay_Timer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_CTRL_TRIG_EN_SHIFT))
    #define ECG_ADC_Delay_Timer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << ECG_ADC_Delay_Timer_CTRL_CAP_MODE_SHIFT))
    #define ECG_ADC_Delay_Timer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define ECG_ADC_Delay_Timer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define ECG_ADC_Delay_Timer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK_SHIFT       ECG_ADC_Delay_Timer_STATUS_TC_SHIFT
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK_SHIFT  ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT
    #define ECG_ADC_Delay_Timer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define ECG_ADC_Delay_Timer_STATUS_FIFOFULL_INT_MASK_SHIFT ECG_ADC_Delay_Timer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_TC                      ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define ECG_ADC_Delay_Timer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << ECG_ADC_Delay_Timer_STATUS_FIFOFULL_SHIFT))

    #define ECG_ADC_Delay_Timer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define ECG_ADC_Delay_Timer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define ECG_ADC_Delay_Timer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define ECG_ADC_Delay_Timer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define ECG_ADC_Delay_Timer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define ECG_ADC_Delay_Timer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_ECG_ADC_Delay_Timer_H */


/* [] END OF FILE */
