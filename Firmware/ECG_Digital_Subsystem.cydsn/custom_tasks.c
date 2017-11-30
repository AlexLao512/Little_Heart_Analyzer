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

#include "FreeRTOS.h"    
#include "semphr.h"
#include "task.h"
#include "queue.h"

#include "global_defines.h"
#include "custom_tasks.h"

//128 sample sine table
uint16 sine_table[] = {
2048,2148,2248,2348,2447,2545,2642,2737,
2831,2923,3013,3100,3185,3267,3346,3423,
3495,3565,3630,3692,3750,3804,3853,3898,
3939,3975,4007,4034,4056,4073,4085,4093,
4095,4093,4085,4073,4056,4034,4007,3975,
3939,3898,3853,3804,3750,3692,3630,3565,
3495,3423,3346,3267,3185,3100,3013,2923,
2831,2737,2642,2545,2447,2348,2248,2148,
2048,1947,1847,1747,1648,1550,1453,1358,
1264,1172,1082,995,910,828,749,672,
600,530,465,403,345,291,242,197,
156,120,88,61,39,22,10,2,
0,2,10,22,39,61,88,120,
156,197,242,291,345,403,465,530,
600,672,749,828,910,995,1082,1172,
1264,1358,1453,1550,1648,1747,1847,1947
};

void vApplicationIdleHook( void )
{
    //CyPmAltAct(PM_ALT_ACT_TIME_NONE,PM_ALT_ACT_SRC_NONE);
}


void init_task (void * pvParameters) 
{
    while (1)
    {
        if (ECG_MuxControl_P_Read() == 1)
        {
            CyDmaChEnable(ADC_DMA_Chan, 1);
            //vTaskDelete does not work becuase our malloc implementation does not support memory deallocation
            vTaskSuspend(NULL);
        }
    }
}

void host_input_task (void * pvParameters) 
{
    typedef enum {IDLE, COMMAND_BEGIN, DAC_COMMAND1,DAC_COMMAND2} receive_state;
    char receive;
    volatile uint8 * buffer;
    receive_state state = IDLE;
    int arg1, arg2;
    
    while(1)
    {
        if (xSemaphoreTake(host_interrupt, portMAX_DELAY ))
        {
            if(current_lease == USB_CDC_LEASE)
            {
                for(int timeout_counter = 0; timeout_counter < USB_UART_TIMEOUT_COUNT; timeout_counter++)
                {
                    if (USBUART_DataIsReady())
                    {
                        receive = USBUART_GetChar();
                        break;
                    }
                }                
            }
            else if(current_lease == BT_UART_LEASE)
            {
                //receive = BT_UART_GetChar();
            }
            
            switch(state)
            {
                case IDLE: 
                    if(receive == 'c') state = COMMAND_BEGIN; 
                    break;
                case COMMAND_BEGIN:
                    state = IDLE;
                    if(receive == 'd') state = DAC_COMMAND1; 
                    if(receive == 'c') state = COMMAND_BEGIN; 
                    break;
                case DAC_COMMAND1: //accepts the chars 0-7 or ints 0-7
                    if ( receive < 8) 
                    {
                        //accept 0-7
                        arg1 = (uint8) receive;
                        state = DAC_COMMAND2;
                    }
                    else if  (receive >=48 && receive <= 55)
                    {
                        //accept '0' - '7'
                        arg1 = (uint8) (receive-48);
                        state = DAC_COMMAND2;
                    }
                    else
                        state = IDLE;
                    break;
                case DAC_COMMAND2:
                    if (receive == '0' || receive == 0)
                    {
                        DAC_Enable[arg1] = 0;
                    }
                    else
                    {
                        DAC_Enable[arg1] = 1;
                    }
                    //do something with arg1 and arg2
                    state = IDLE;
                    break;
               default: state = IDLE; break;     
            }
        }
    }
}
void swap_buffer_task (void *pvParameters){
    //float adc_ref_voltage = 2.3;
    char debug_message[] = "host_interrupt\n";
    uint8 buff_index = 0;
    uint8 * activeBuffer = recieve_buffer[buff_index];
    uint8 * popBuffer;
    ////added for testing////
    volatile uint16 packet_num = 0;
    volatile uint16 sample_num = 0;
    volatile uint16 sine_num = 0;
    ////added for testing////
    int i,j;
    while(1) {  
        if (xSemaphoreTake(transfer_complete, portMAX_DELAY )) { 
            //NEED TO FIX PROPERLY, THIS IS A HACK
            USBUART_EnableOutEP(3); // if there is no usb device the endpoint gets disabled for some reason
            //LED0_Write(~LED0_Read()); //toggle LED0 at ~16hz
            //temp = USBUART_GetChar();
            
            //opperates on the data 1 round of samples at a time
            for (i = 0; i <DMA_BUFFER_SIZE; i+=16)
            { 

                for (j=0; j <16; j+=2)
                {
                    //do some operation
                    //currently a placeholder
                }
                sample_num++;
                sine_num = (sine_num + 1);
            }
            packet_num++;
            sample_num = 0;
            xQueueSend(raw_data_queue, &activeBuffer, 0);
            /*if (xQueueSend(raw_data_queue, &activeBuffer, 0))
            {
                xQueueReceive(raw_data_queue,  &popBuffer, 0);
                xQueueSend(raw_data_queue, &activeBuffer, 0);
            }*/
            buff_index = (buff_index + 1) % num_buff;
            activeBuffer = recieve_buffer[buff_index];        
        }
    }    
}

void transmit_data_task (void *pvParameters){
    uint8 * activeBuffer;
    uint8 send_header[] = {0xff, 0xff, 0xda};
    int i, timeout_counter;
    while(1)
    {
        xQueueReceive(raw_data_queue,  &activeBuffer, portMAX_DELAY); 
        if(current_lease != NO_LEASE)
        {
            if(current_lease ==USB_CDC_LEASE)
            {
                for(timeout_counter = 0; timeout_counter < USB_UART_TIMEOUT_COUNT; timeout_counter++)
                {
                    if (USBUART_CDCIsReady())
                    {
                        USBUART_PutData(send_header, 3); 
                        break;
                    }
                }
               
                for( i =0; i < DMA_BUFFER_SIZE ; i+=64)
                {
                    //tries a constant ammount of times to use the usbuart before giving up
                    for(timeout_counter = 0; timeout_counter < USB_UART_TIMEOUT_COUNT; timeout_counter++)
                    {
                        if (USBUART_CDCIsReady())
                        {
                            USBUART_PutData(&activeBuffer[i], 64);
                            break;
                        }
                    }
                }
            }
            else if (current_lease == BT_UART_LEASE)
            {
                BT_UART_PutArray(send_header, 3);
                for( i =0; i < DMA_BUFFER_SIZE ; i+=64)
                {
                    BT_UART_PutArray(&activeBuffer[i], 64);
                }
            }
        }
                    
        if (lease_time == 0)//check to see if lease has expired
        {
            current_lease = NO_LEASE;
            //current_lease = BT_UART_LEASE;
            //lease_time = ONE_SECOND_LEASE;
        }
        else
        {
            lease_time--;
        }
    }
}
/* [] END OF FILE */
