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

/* Declaration of NVIC base vector for FreeRTOS exception handling */
#define CORTEX_INTERRUPT_BASE          (16)

#define num_buff 3

/* Defines for ADC_DMA */
#define ADC_DMA_BYTES_PER_BURST 2
#define ADC_DMA_REQUEST_PER_BURST 1
#define ADC_DMA_SRC_BASE_PREF (CYDEV_PERIPH_BASE)
#define ADC_DMA_SRC_BASE_SRAM (CYDEV_SRAM_BASE)
#define ADC_DMA_DST_BASE (CYDEV_SRAM_BASE)
#define DMA_BUFFER_SIZE 512

/* Defines for DAC_DMA */
#define DAC_DMA_BYTES_PER_BURST 1
#define DAC_DMA_REQUEST_PER_BURST 1
#define DAC_DMA_SRC_BASE (CYDEV_SRAM_BASE)
#define DAC_DMA_DST_BASE (CYDEV_PERIPH_BASE)

uint8 source[DMA_BUFFER_SIZE]; //8 channels X 2 bytes X 22 rounds of samples
uint8 recieve_buffer[num_buff][DMA_BUFFER_SIZE];
/* Variable declarations for ADC_DMA */
uint8 ADC_DMA_Chan;
uint8 ADC_DMA_TD[3];

/* Variable declarations for DAC_DMA */
uint8 DAC_DMA_Chan;
uint8 DAC_DMA_TD[1];


/* [] END OF FILE */
