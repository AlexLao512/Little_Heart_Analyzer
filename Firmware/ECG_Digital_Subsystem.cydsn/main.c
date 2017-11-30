/*  
 *  Little Heart Analyzer
 *  Copyright (C) 2017 Alex Lao, Christina Riczu, Thomas Phan, Emilie Corcoran
 *  
 *  Original project documentation at www.voltagedivide.com
 *  Original code repository at www.github.com/AlexLao512/Little_Heart_Analyzer
 *
 *  Notice: If you find this code useful please consider donating to,  
 *          or thanking the team that originally developed this project. 
 *          Do so by contacting lao.alex.512@gmail.com, donations or comments
 *          will be relayed to the original four team memebers. 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <project.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"

/*ISR includes*/
#include "interrupts.h"

/*Task Inclues*/
#include "custom_tasks.h"

#include "global_defines.h"

/* Declarations of the exception handlers for FreeRTOS */
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);

int main()
{   
    USBUART_Start(0,USBUART_5V_OPERATION);    
    USBUART_CDC_Init();
    ECG_ADC_Start();
    ECG_ADC_IRQ_Start();    
    ECG_ADC_Delay_Timer_Start();
    
    ECG_REF_ADC_Start();
    
    ECG_ADC_REF_DAC_Start();   
    ECG_RL_DRIVE_DAC_Start();
    ECG_REF_DRIVE_DAC_Start();
    
    ECG_REF_ADC_EOC_ISR_Start();
    ECG_ADC_EOC_ISR_Start();
    ECG_ADC_REF_DAC_SET_ISR_Start();
    
    BT_UART_Start();
    BT_RECEIVE_ISR_Start();
    
    ADC_DMA_Chan = ADC_DMA_DmaInitialize(ADC_DMA_BYTES_PER_BURST, ADC_DMA_REQUEST_PER_BURST, 
        HI16(ADC_DMA_SRC_BASE_PREF), HI16(ADC_DMA_DST_BASE));
    ADC_DMA_TD[0] = CyDmaTdAllocate();
    ADC_DMA_TD[1] = CyDmaTdAllocate();
    ADC_DMA_TD[2] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(ADC_DMA_TD[0], 512, ADC_DMA_TD[1], ADC_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR|TD_SWAP_EN);
    CyDmaTdSetConfiguration(ADC_DMA_TD[1], 512, ADC_DMA_TD[2], ADC_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR|TD_SWAP_EN);
    CyDmaTdSetConfiguration(ADC_DMA_TD[2], 512, ADC_DMA_TD[0], ADC_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR|TD_SWAP_EN);
    CyDmaTdSetAddress(ADC_DMA_TD[0], LO16((uint32)ECG_ADC_DEC_SAMP_PTR), LO16((uint32)recieve_buffer[0]));
    CyDmaTdSetAddress(ADC_DMA_TD[1], LO16((uint32)ECG_ADC_DEC_SAMP_PTR), LO16((uint32)recieve_buffer[1]));
    CyDmaTdSetAddress(ADC_DMA_TD[2], LO16((uint32)ECG_ADC_DEC_SAMP_PTR), LO16((uint32)recieve_buffer[2]));
    CyDmaChSetInitialTd(ADC_DMA_Chan, ADC_DMA_TD[0]);
    
    //initalize DAC offsets to 2.5v
    for (int i =0; i<8; i++)
    {
        DAC_offsets[i] = 0x9c;
        DAC_Enable[i] = 1;
    }
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    portBASE_TYPE taskCreated;      /* Return value from xTaskCreate */
	
	/* Initialize the OS vectors - make it ready to create the task, below */
    
    /* Handler for Cortex Supervisor Call (SVC, formerly SWI) - address 11 */
    CyIntSetSysVector( CORTEX_INTERRUPT_BASE + SVCall_IRQn,
        (cyisraddress)vPortSVCHandler );
    
    /* Handler for Cortex PendSV Call - address 14 */
	CyIntSetSysVector( CORTEX_INTERRUPT_BASE + PendSV_IRQn,
        (cyisraddress)xPortPendSVHandler );    
    
    /* Handler for Cortex SYSTICK - address 15 */
	CyIntSetSysVector( CORTEX_INTERRUPT_BASE + SysTick_IRQn,
        (cyisraddress)xPortSysTickHandler );
    while(USBUART_GetConfiguration() == 0);
    USBUART_EnableOutEP(3);

    //while(USBUART_CDCIsReady() == 0);
    //USBUART_PutChar(' ');
    
    //vTraceEnable(TRC_START_AWAIT_HOST); /* Start FreeRTOS Trace */
    //traceString chn = xTraceRegisterString("MyChannel");
    //vTracePrint(chn, "Trace Streaming Start!");
    //vTraceEnable(TRC_INIT); /* Start FreeRTOS Trace */
    
    
    uint16 current_value = 256;
    //populates the source array with data
    for (int i = 0; i < DMA_BUFFER_SIZE; i+=2)
    {
        source[i+1] = (uint8)current_value;
        source[i] = (uint8)(current_value >>8);
        current_value++;
    }     
    source[DMA_BUFFER_SIZE-1] = 0xEE;
    source[DMA_BUFFER_SIZE-2] = 0xEE;    
    
    
    vSemaphoreCreateBinary(transfer_complete);
    vSemaphoreCreateBinary(host_interrupt);
    xSemaphoreTake(transfer_complete, 0);
    xSemaphoreTake(host_interrupt, 0);
    raw_data_queue = xQueueCreate(num_buff-1 , sizeof(uint8 *)); 
    
    xTaskCreate (init_task, "init", configMINIMAL_STACK_SIZE + 200, 0, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate (host_input_task, "host_input", configMINIMAL_STACK_SIZE + 200, 0, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate( swap_buffer_task, "swap_buffer", configMINIMAL_STACK_SIZE + 200, 0, tskIDLE_PRIORITY +1, NULL );
    xTaskCreate( transmit_data_task, "transmit_data", configMINIMAL_STACK_SIZE + 200, 0, tskIDLE_PRIORITY +1, NULL );
    vTaskStartScheduler();
    while(1);
}         

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	/* The stack space has been execeeded for a task, considering allocating more. */
	taskDISABLE_INTERRUPTS();
	while(1);
}
/*---------------------------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* The heap space has been execeeded. */
	taskDISABLE_INTERRUPTS();
	while(1);
}

