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

#include "interrupts.h"

int current_lease = NO_LEASE;
int lease_time = 0;

//int current_lease = BT_UART_LEASE;
//int lease_time = ONE_SECOND_LEASE;

void BT_RECEIVE_ISR_Interrupt_InterruptCallback(void)
{
    if (current_lease == NO_LEASE || current_lease == BT_UART_LEASE || current_lease == USB_CDC_LEASE)
    {
        current_lease = BT_UART_LEASE;
        lease_time = ONE_SECOND_LEASE;
        xSemaphoreGiveFromISR(host_interrupt, NULL);
    }
    BT_UART_GetChar();
    BT_RECEIVE_ISR_ClearPending();
}
void ECG_ADC_EOC_ISR_Interrupt_InterruptCallback(void)
{   
     xSemaphoreGiveFromISR(transfer_complete, NULL);       
}

void USBUART_EP_3_ISR_EntryCallback(void)
{
    if (current_lease == NO_LEASE || current_lease == BT_UART_LEASE || current_lease == USB_CDC_LEASE)
    {
        current_lease = USB_CDC_LEASE;
        lease_time = ONE_SECOND_LEASE;
        xSemaphoreGiveFromISR(host_interrupt, NULL);
    }
}

void ECG_REF_ADC_EOC_ISR_Interrupt_InterruptCallback()
{
    int channel_num = ECG_MuxControl_P_Read();
    uint8 adc_ref_val = ECG_REF_ADC_GetResult8();  
    if (DAC_Enable[channel_num])
    {
        DAC_offsets [channel_num] = ((0.999*DAC_offsets[channel_num]) + ((0.001*(float)adc_ref_val) * 0.021));
    }
    
    float check_value = (DAC_new_offsets[channel_num] - DAC_offsets[channel_num]);
    if(check_value < 0) {
        check_value = -check_value;   
    }
    
    if( check_value > 0.02) {
        DAC_new_offsets[channel_num] = DAC_offsets[channel_num];
    }
}

void ECG_ADC_REF_DAC_SET_ISR_Interrupt_InterruptCallback()
{    
    int channel_num = ECG_MuxControl_P_Read();
    ECG_ADC_REF_DAC_SetValue((uint8_t)(DAC_new_offsets[channel_num] / 0.0161));
}
/* [] END OF FILE */
