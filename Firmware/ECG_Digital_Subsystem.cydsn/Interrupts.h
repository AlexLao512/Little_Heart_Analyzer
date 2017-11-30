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
 *          will be relayed to the original four team members. 
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

//The includes for this system's Interrupts
//Include this file in files to enable their callback
#include "FreeRTOS.h"    
#include "semphr.h"
#define ECG_ADC_EOC_ISR_INTERRUPT_INTERRUPT_CALLBACK 1
#define USBUART_EP_3_ISR_ENTRY_CALLBACK 1
#define ECG_REF_ADC_EOC_ISR_INTERRUPT_INTERRUPT_CALLBACK 1
#define ECG_ADC_REF_DAC_SET_ISR_INTERRUPT_INTERRUPT_CALLBACK 1
#define BT_RECEIVE_ISR_INTERRUPT_INTERRUPT_CALLBACK 1
#define NO_LEASE 0
#define USB_CDC_LEASE 1
#define BT_UART_LEASE 2
#define ONE_SECOND_LEASE 33 //the lease will be decremented by the transmit task, which runs once every 32ms

volatile float DAC_offsets[8];
volatile float DAC_new_offsets[8];
volatile int DAC_Enable[8];
extern int current_lease;
extern int lease_time;

SemaphoreHandle_t transfer_complete;
SemaphoreHandle_t host_interrupt;
void ECG_ADC_EOC_ISR_Interrupt_InterruptCallback(void); 
void USBUART_EP_3_ISR_EntryCallback(void);
void ECG_REF_ADC_EOC_ISR_Interrupt_InterruptCallback();
void ECG_ADC_REF_DAC_SET_ISR_Interrupt_InterruptCallback();
void BT_RECEIVE_ISR_Interrupt_InterruptCallback();
/* [] END OF FILE */
