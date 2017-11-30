/*******************************************************************************
* File Name: BT_UART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_BT_UART_H)
#define CY_UART_BT_UART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define BT_UART_RX_ENABLED                     (1u)
#define BT_UART_TX_ENABLED                     (1u)
#define BT_UART_HD_ENABLED                     (0u)
#define BT_UART_RX_INTERRUPT_ENABLED           (0u)
#define BT_UART_TX_INTERRUPT_ENABLED           (0u)
#define BT_UART_INTERNAL_CLOCK_USED            (1u)
#define BT_UART_RXHW_ADDRESS_ENABLED           (0u)
#define BT_UART_OVER_SAMPLE_COUNT              (8u)
#define BT_UART_PARITY_TYPE                    (0u)
#define BT_UART_PARITY_TYPE_SW                 (0u)
#define BT_UART_BREAK_DETECT                   (0u)
#define BT_UART_BREAK_BITS_TX                  (13u)
#define BT_UART_BREAK_BITS_RX                  (13u)
#define BT_UART_TXCLKGEN_DP                    (1u)
#define BT_UART_USE23POLLING                   (1u)
#define BT_UART_FLOW_CONTROL                   (1u)
#define BT_UART_CLK_FREQ                       (1u)
#define BT_UART_TX_BUFFER_SIZE                 (4u)
#define BT_UART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define BT_UART_CONTROL_REG_REMOVED            (0u)
#else
    #define BT_UART_CONTROL_REG_REMOVED            (1u)
#endif /* End BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct BT_UART_backupStruct_
{
    uint8 enableState;

    #if(BT_UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End BT_UART_CONTROL_REG_REMOVED */

} BT_UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void BT_UART_Start(void) ;
void BT_UART_Stop(void) ;
uint8 BT_UART_ReadControlRegister(void) ;
void BT_UART_WriteControlRegister(uint8 control) ;

void BT_UART_Init(void) ;
void BT_UART_Enable(void) ;
void BT_UART_SaveConfig(void) ;
void BT_UART_RestoreConfig(void) ;
void BT_UART_Sleep(void) ;
void BT_UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) )

    #if (BT_UART_RX_INTERRUPT_ENABLED)
        #define BT_UART_EnableRxInt()  CyIntEnable (BT_UART_RX_VECT_NUM)
        #define BT_UART_DisableRxInt() CyIntDisable(BT_UART_RX_VECT_NUM)
        CY_ISR_PROTO(BT_UART_RXISR);
    #endif /* BT_UART_RX_INTERRUPT_ENABLED */

    void BT_UART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void BT_UART_SetRxAddress1(uint8 address) ;
    void BT_UART_SetRxAddress2(uint8 address) ;

    void  BT_UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 BT_UART_ReadRxData(void) ;
    uint8 BT_UART_ReadRxStatus(void) ;
    uint8 BT_UART_GetChar(void) ;
    uint16 BT_UART_GetByte(void) ;
    uint8 BT_UART_GetRxBufferSize(void)
                                                            ;
    void BT_UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define BT_UART_GetRxInterruptSource   BT_UART_ReadRxStatus

#endif /* End (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(BT_UART_TX_ENABLED || BT_UART_HD_ENABLED)

    #if(BT_UART_TX_INTERRUPT_ENABLED)
        #define BT_UART_EnableTxInt()  CyIntEnable (BT_UART_TX_VECT_NUM)
        #define BT_UART_DisableTxInt() CyIntDisable(BT_UART_TX_VECT_NUM)
        #define BT_UART_SetPendingTxInt() CyIntSetPending(BT_UART_TX_VECT_NUM)
        #define BT_UART_ClearPendingTxInt() CyIntClearPending(BT_UART_TX_VECT_NUM)
        CY_ISR_PROTO(BT_UART_TXISR);
    #endif /* BT_UART_TX_INTERRUPT_ENABLED */

    void BT_UART_SetTxInterruptMode(uint8 intSrc) ;
    void BT_UART_WriteTxData(uint8 txDataByte) ;
    uint8 BT_UART_ReadTxStatus(void) ;
    void BT_UART_PutChar(uint8 txDataByte) ;
    void BT_UART_PutString(const char8 string[]) ;
    void BT_UART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void BT_UART_PutCRLF(uint8 txDataByte) ;
    void BT_UART_ClearTxBuffer(void) ;
    void BT_UART_SetTxAddressMode(uint8 addressMode) ;
    void BT_UART_SendBreak(uint8 retMode) ;
    uint8 BT_UART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define BT_UART_PutStringConst         BT_UART_PutString
    #define BT_UART_PutArrayConst          BT_UART_PutArray
    #define BT_UART_GetTxInterruptSource   BT_UART_ReadTxStatus

#endif /* End BT_UART_TX_ENABLED || BT_UART_HD_ENABLED */

#if(BT_UART_HD_ENABLED)
    void BT_UART_LoadRxConfig(void) ;
    void BT_UART_LoadTxConfig(void) ;
#endif /* End BT_UART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BT_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    BT_UART_CyBtldrCommStart(void) CYSMALL ;
    void    BT_UART_CyBtldrCommStop(void) CYSMALL ;
    void    BT_UART_CyBtldrCommReset(void) CYSMALL ;
    cystatus BT_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus BT_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BT_UART)
        #define CyBtldrCommStart    BT_UART_CyBtldrCommStart
        #define CyBtldrCommStop     BT_UART_CyBtldrCommStop
        #define CyBtldrCommReset    BT_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    BT_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     BT_UART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BT_UART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define BT_UART_BYTE2BYTE_TIME_OUT (25u)
    #define BT_UART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define BT_UART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define BT_UART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define BT_UART_SET_SPACE      (0x00u)
#define BT_UART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (BT_UART_TX_ENABLED) || (BT_UART_HD_ENABLED) )
    #if(BT_UART_TX_INTERRUPT_ENABLED)
        #define BT_UART_TX_VECT_NUM            (uint8)BT_UART_TXInternalInterrupt__INTC_NUMBER
        #define BT_UART_TX_PRIOR_NUM           (uint8)BT_UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BT_UART_TX_INTERRUPT_ENABLED */

    #define BT_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define BT_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define BT_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(BT_UART_TX_ENABLED)
        #define BT_UART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (BT_UART_HD_ENABLED) */
        #define BT_UART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (BT_UART_TX_ENABLED) */

    #define BT_UART_TX_STS_COMPLETE            (uint8)(0x01u << BT_UART_TX_STS_COMPLETE_SHIFT)
    #define BT_UART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << BT_UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define BT_UART_TX_STS_FIFO_FULL           (uint8)(0x01u << BT_UART_TX_STS_FIFO_FULL_SHIFT)
    #define BT_UART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << BT_UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (BT_UART_TX_ENABLED) || (BT_UART_HD_ENABLED)*/

#if( (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) )
    #if(BT_UART_RX_INTERRUPT_ENABLED)
        #define BT_UART_RX_VECT_NUM            (uint8)BT_UART_RXInternalInterrupt__INTC_NUMBER
        #define BT_UART_RX_PRIOR_NUM           (uint8)BT_UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BT_UART_RX_INTERRUPT_ENABLED */
    #define BT_UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define BT_UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define BT_UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define BT_UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define BT_UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define BT_UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define BT_UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define BT_UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define BT_UART_RX_STS_MRKSPC           (uint8)(0x01u << BT_UART_RX_STS_MRKSPC_SHIFT)
    #define BT_UART_RX_STS_BREAK            (uint8)(0x01u << BT_UART_RX_STS_BREAK_SHIFT)
    #define BT_UART_RX_STS_PAR_ERROR        (uint8)(0x01u << BT_UART_RX_STS_PAR_ERROR_SHIFT)
    #define BT_UART_RX_STS_STOP_ERROR       (uint8)(0x01u << BT_UART_RX_STS_STOP_ERROR_SHIFT)
    #define BT_UART_RX_STS_OVERRUN          (uint8)(0x01u << BT_UART_RX_STS_OVERRUN_SHIFT)
    #define BT_UART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << BT_UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define BT_UART_RX_STS_ADDR_MATCH       (uint8)(0x01u << BT_UART_RX_STS_ADDR_MATCH_SHIFT)
    #define BT_UART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << BT_UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define BT_UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) */

/* Control Register definitions */
#define BT_UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define BT_UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define BT_UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define BT_UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define BT_UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define BT_UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define BT_UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define BT_UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define BT_UART_CTRL_HD_SEND               (uint8)(0x01u << BT_UART_CTRL_HD_SEND_SHIFT)
#define BT_UART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << BT_UART_CTRL_HD_SEND_BREAK_SHIFT)
#define BT_UART_CTRL_MARK                  (uint8)(0x01u << BT_UART_CTRL_MARK_SHIFT)
#define BT_UART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << BT_UART_CTRL_PARITY_TYPE0_SHIFT)
#define BT_UART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << BT_UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define BT_UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define BT_UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define BT_UART_SEND_BREAK                         (0x00u)
#define BT_UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define BT_UART_REINIT                             (0x02u)
#define BT_UART_SEND_WAIT_REINIT                   (0x03u)

#define BT_UART_OVER_SAMPLE_8                      (8u)
#define BT_UART_OVER_SAMPLE_16                     (16u)

#define BT_UART_BIT_CENTER                         (BT_UART_OVER_SAMPLE_COUNT - 2u)

#define BT_UART_FIFO_LENGTH                        (4u)
#define BT_UART_NUMBER_OF_START_BIT                (1u)
#define BT_UART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define BT_UART_TXBITCTR_BREAKBITS8X   ((BT_UART_BREAK_BITS_TX * BT_UART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define BT_UART_TXBITCTR_BREAKBITS ((BT_UART_BREAK_BITS_TX * BT_UART_OVER_SAMPLE_COUNT) - 1u)

#define BT_UART_HALF_BIT_COUNT   \
                            (((BT_UART_OVER_SAMPLE_COUNT / 2u) + (BT_UART_USE23POLLING * 1u)) - 2u)
#if (BT_UART_OVER_SAMPLE_COUNT == BT_UART_OVER_SAMPLE_8)
    #define BT_UART_HD_TXBITCTR_INIT   (((BT_UART_BREAK_BITS_TX + \
                            BT_UART_NUMBER_OF_START_BIT) * BT_UART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define BT_UART_RXBITCTR_INIT  ((((BT_UART_BREAK_BITS_RX + BT_UART_NUMBER_OF_START_BIT) \
                            * BT_UART_OVER_SAMPLE_COUNT) + BT_UART_HALF_BIT_COUNT) - 1u)

#else /* BT_UART_OVER_SAMPLE_COUNT == BT_UART_OVER_SAMPLE_16 */
    #define BT_UART_HD_TXBITCTR_INIT   ((8u * BT_UART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define BT_UART_RXBITCTR_INIT      (((7u * BT_UART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      BT_UART_HALF_BIT_COUNT)
#endif /* End BT_UART_OVER_SAMPLE_COUNT */

#define BT_UART_HD_RXBITCTR_INIT                   BT_UART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 BT_UART_initVar;
#if (BT_UART_TX_INTERRUPT_ENABLED && BT_UART_TX_ENABLED)
    extern volatile uint8 BT_UART_txBuffer[BT_UART_TX_BUFFER_SIZE];
    extern volatile uint8 BT_UART_txBufferRead;
    extern uint8 BT_UART_txBufferWrite;
#endif /* (BT_UART_TX_INTERRUPT_ENABLED && BT_UART_TX_ENABLED) */
#if (BT_UART_RX_INTERRUPT_ENABLED && (BT_UART_RX_ENABLED || BT_UART_HD_ENABLED))
    extern uint8 BT_UART_errorStatus;
    extern volatile uint8 BT_UART_rxBuffer[BT_UART_RX_BUFFER_SIZE];
    extern volatile uint8 BT_UART_rxBufferRead;
    extern volatile uint8 BT_UART_rxBufferWrite;
    extern volatile uint8 BT_UART_rxBufferLoopDetect;
    extern volatile uint8 BT_UART_rxBufferOverflow;
    #if (BT_UART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 BT_UART_rxAddressMode;
        extern volatile uint8 BT_UART_rxAddressDetected;
    #endif /* (BT_UART_RXHW_ADDRESS_ENABLED) */
#endif /* (BT_UART_RX_INTERRUPT_ENABLED && (BT_UART_RX_ENABLED || BT_UART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define BT_UART__B_UART__AM_SW_BYTE_BYTE 1
#define BT_UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define BT_UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define BT_UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define BT_UART__B_UART__AM_NONE 0

#define BT_UART__B_UART__NONE_REVB 0
#define BT_UART__B_UART__EVEN_REVB 1
#define BT_UART__B_UART__ODD_REVB 2
#define BT_UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define BT_UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define BT_UART_NUMBER_OF_STOP_BITS    (1u)

#if (BT_UART_RXHW_ADDRESS_ENABLED)
    #define BT_UART_RX_ADDRESS_MODE    (0u)
    #define BT_UART_RX_HW_ADDRESS1     (0u)
    #define BT_UART_RX_HW_ADDRESS2     (0u)
#endif /* (BT_UART_RXHW_ADDRESS_ENABLED) */

#define BT_UART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << BT_UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << BT_UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << BT_UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << BT_UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << BT_UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << BT_UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << BT_UART_RX_STS_OVERRUN_SHIFT))

#define BT_UART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << BT_UART_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << BT_UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << BT_UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << BT_UART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BT_UART_CONTROL_REG \
                            (* (reg8 *) BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define BT_UART_CONTROL_PTR \
                            (  (reg8 *) BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BT_UART_TX_ENABLED)
    #define BT_UART_TXDATA_REG          (* (reg8 *) BT_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define BT_UART_TXDATA_PTR          (  (reg8 *) BT_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define BT_UART_TXDATA_AUX_CTL_REG  (* (reg8 *) BT_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BT_UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) BT_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BT_UART_TXSTATUS_REG        (* (reg8 *) BT_UART_BUART_sTX_TxSts__STATUS_REG)
    #define BT_UART_TXSTATUS_PTR        (  (reg8 *) BT_UART_BUART_sTX_TxSts__STATUS_REG)
    #define BT_UART_TXSTATUS_MASK_REG   (* (reg8 *) BT_UART_BUART_sTX_TxSts__MASK_REG)
    #define BT_UART_TXSTATUS_MASK_PTR   (  (reg8 *) BT_UART_BUART_sTX_TxSts__MASK_REG)
    #define BT_UART_TXSTATUS_ACTL_REG   (* (reg8 *) BT_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define BT_UART_TXSTATUS_ACTL_PTR   (  (reg8 *) BT_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(BT_UART_TXCLKGEN_DP)
        #define BT_UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BT_UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BT_UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define BT_UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define BT_UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BT_UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BT_UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BT_UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BT_UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define BT_UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) BT_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* BT_UART_TXCLKGEN_DP */

#endif /* End BT_UART_TX_ENABLED */

#if(BT_UART_HD_ENABLED)

    #define BT_UART_TXDATA_REG             (* (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define BT_UART_TXDATA_PTR             (  (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define BT_UART_TXDATA_AUX_CTL_REG     (* (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define BT_UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BT_UART_TXSTATUS_REG           (* (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BT_UART_TXSTATUS_PTR           (  (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BT_UART_TXSTATUS_MASK_REG      (* (reg8 *) BT_UART_BUART_sRX_RxSts__MASK_REG )
    #define BT_UART_TXSTATUS_MASK_PTR      (  (reg8 *) BT_UART_BUART_sRX_RxSts__MASK_REG )
    #define BT_UART_TXSTATUS_ACTL_REG      (* (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BT_UART_TXSTATUS_ACTL_PTR      (  (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End BT_UART_HD_ENABLED */

#if( (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) )
    #define BT_UART_RXDATA_REG             (* (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define BT_UART_RXDATA_PTR             (  (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define BT_UART_RXADDRESS1_REG         (* (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define BT_UART_RXADDRESS1_PTR         (  (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define BT_UART_RXADDRESS2_REG         (* (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define BT_UART_RXADDRESS2_PTR         (  (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define BT_UART_RXDATA_AUX_CTL_REG     (* (reg8 *) BT_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BT_UART_RXBITCTR_PERIOD_REG    (* (reg8 *) BT_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BT_UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) BT_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BT_UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BT_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BT_UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BT_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BT_UART_RXBITCTR_COUNTER_REG   (* (reg8 *) BT_UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define BT_UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) BT_UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define BT_UART_RXSTATUS_REG           (* (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BT_UART_RXSTATUS_PTR           (  (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BT_UART_RXSTATUS_MASK_REG      (* (reg8 *) BT_UART_BUART_sRX_RxSts__MASK_REG )
    #define BT_UART_RXSTATUS_MASK_PTR      (  (reg8 *) BT_UART_BUART_sRX_RxSts__MASK_REG )
    #define BT_UART_RXSTATUS_ACTL_REG      (* (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BT_UART_RXSTATUS_ACTL_PTR      (  (reg8 *) BT_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) */

#if(BT_UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define BT_UART_INTCLOCK_CLKEN_REG     (* (reg8 *) BT_UART_IntClock__PM_ACT_CFG)
    #define BT_UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) BT_UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define BT_UART_INTCLOCK_CLKEN_MASK    BT_UART_IntClock__PM_ACT_MSK
#endif /* End BT_UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(BT_UART_TX_ENABLED)
    #define BT_UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End BT_UART_TX_ENABLED */

#if(BT_UART_HD_ENABLED)
    #define BT_UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End BT_UART_HD_ENABLED */

#if( (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) )
    #define BT_UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define BT_UART_WAIT_1_MS      BT_UART_BL_CHK_DELAY_MS   

#define BT_UART_TXBUFFERSIZE   BT_UART_TX_BUFFER_SIZE
#define BT_UART_RXBUFFERSIZE   BT_UART_RX_BUFFER_SIZE

#if (BT_UART_RXHW_ADDRESS_ENABLED)
    #define BT_UART_RXADDRESSMODE  BT_UART_RX_ADDRESS_MODE
    #define BT_UART_RXHWADDRESS1   BT_UART_RX_HW_ADDRESS1
    #define BT_UART_RXHWADDRESS2   BT_UART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define BT_UART_RXAddressMode  BT_UART_RXADDRESSMODE
#endif /* (BT_UART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define BT_UART_initvar                    BT_UART_initVar

#define BT_UART_RX_Enabled                 BT_UART_RX_ENABLED
#define BT_UART_TX_Enabled                 BT_UART_TX_ENABLED
#define BT_UART_HD_Enabled                 BT_UART_HD_ENABLED
#define BT_UART_RX_IntInterruptEnabled     BT_UART_RX_INTERRUPT_ENABLED
#define BT_UART_TX_IntInterruptEnabled     BT_UART_TX_INTERRUPT_ENABLED
#define BT_UART_InternalClockUsed          BT_UART_INTERNAL_CLOCK_USED
#define BT_UART_RXHW_Address_Enabled       BT_UART_RXHW_ADDRESS_ENABLED
#define BT_UART_OverSampleCount            BT_UART_OVER_SAMPLE_COUNT
#define BT_UART_ParityType                 BT_UART_PARITY_TYPE

#if( BT_UART_TX_ENABLED && (BT_UART_TXBUFFERSIZE > BT_UART_FIFO_LENGTH))
    #define BT_UART_TXBUFFER               BT_UART_txBuffer
    #define BT_UART_TXBUFFERREAD           BT_UART_txBufferRead
    #define BT_UART_TXBUFFERWRITE          BT_UART_txBufferWrite
#endif /* End BT_UART_TX_ENABLED */
#if( ( BT_UART_RX_ENABLED || BT_UART_HD_ENABLED ) && \
     (BT_UART_RXBUFFERSIZE > BT_UART_FIFO_LENGTH) )
    #define BT_UART_RXBUFFER               BT_UART_rxBuffer
    #define BT_UART_RXBUFFERREAD           BT_UART_rxBufferRead
    #define BT_UART_RXBUFFERWRITE          BT_UART_rxBufferWrite
    #define BT_UART_RXBUFFERLOOPDETECT     BT_UART_rxBufferLoopDetect
    #define BT_UART_RXBUFFER_OVERFLOW      BT_UART_rxBufferOverflow
#endif /* End BT_UART_RX_ENABLED */

#ifdef BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BT_UART_CONTROL                BT_UART_CONTROL_REG
#endif /* End BT_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BT_UART_TX_ENABLED)
    #define BT_UART_TXDATA                 BT_UART_TXDATA_REG
    #define BT_UART_TXSTATUS               BT_UART_TXSTATUS_REG
    #define BT_UART_TXSTATUS_MASK          BT_UART_TXSTATUS_MASK_REG
    #define BT_UART_TXSTATUS_ACTL          BT_UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(BT_UART_TXCLKGEN_DP)
        #define BT_UART_TXBITCLKGEN_CTR        BT_UART_TXBITCLKGEN_CTR_REG
        #define BT_UART_TXBITCLKTX_COMPLETE    BT_UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define BT_UART_TXBITCTR_PERIOD        BT_UART_TXBITCTR_PERIOD_REG
        #define BT_UART_TXBITCTR_CONTROL       BT_UART_TXBITCTR_CONTROL_REG
        #define BT_UART_TXBITCTR_COUNTER       BT_UART_TXBITCTR_COUNTER_REG
    #endif /* BT_UART_TXCLKGEN_DP */
#endif /* End BT_UART_TX_ENABLED */

#if(BT_UART_HD_ENABLED)
    #define BT_UART_TXDATA                 BT_UART_TXDATA_REG
    #define BT_UART_TXSTATUS               BT_UART_TXSTATUS_REG
    #define BT_UART_TXSTATUS_MASK          BT_UART_TXSTATUS_MASK_REG
    #define BT_UART_TXSTATUS_ACTL          BT_UART_TXSTATUS_ACTL_REG
#endif /* End BT_UART_HD_ENABLED */

#if( (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) )
    #define BT_UART_RXDATA                 BT_UART_RXDATA_REG
    #define BT_UART_RXADDRESS1             BT_UART_RXADDRESS1_REG
    #define BT_UART_RXADDRESS2             BT_UART_RXADDRESS2_REG
    #define BT_UART_RXBITCTR_PERIOD        BT_UART_RXBITCTR_PERIOD_REG
    #define BT_UART_RXBITCTR_CONTROL       BT_UART_RXBITCTR_CONTROL_REG
    #define BT_UART_RXBITCTR_COUNTER       BT_UART_RXBITCTR_COUNTER_REG
    #define BT_UART_RXSTATUS               BT_UART_RXSTATUS_REG
    #define BT_UART_RXSTATUS_MASK          BT_UART_RXSTATUS_MASK_REG
    #define BT_UART_RXSTATUS_ACTL          BT_UART_RXSTATUS_ACTL_REG
#endif /* End  (BT_UART_RX_ENABLED) || (BT_UART_HD_ENABLED) */

#if(BT_UART_INTERNAL_CLOCK_USED)
    #define BT_UART_INTCLOCK_CLKEN         BT_UART_INTCLOCK_CLKEN_REG
#endif /* End BT_UART_INTERNAL_CLOCK_USED */

#define BT_UART_WAIT_FOR_COMLETE_REINIT    BT_UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_BT_UART_H */


/* [] END OF FILE */
