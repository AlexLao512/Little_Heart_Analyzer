#include "trcRecorder.h"

#if (TRC_USE_TRACEALYZER_RECORDER == 1)
#if(TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)

#include "stdint.h"

#define BUFSIZE 64
	
typedef struct{
	uint32_t idx;
	uint8_t data[BUFSIZE];
}recBuf;

recBuf commandBuffer;

/**
  * @brief  CDC_Receive_FS
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  *           
  *         @note
  *         This function will block any OUT packet reception on USB endpoint 
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result 
  *         in receiving more data while previous ones are still not sent.
  *                 
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t CDC_Receive_FS (uint8_t* Buf, uint32_t *Len)
{
    
	for( uint32_t i=0;i<*Len;i++)
	{		
		commandBuffer.data[commandBuffer.idx]=Buf[i];
		commandBuffer.idx++;
	}	
  //USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  //USBD_CDC_ReceivePacket(&hUsbDeviceFS);	

    BT_UART_PutString("USB Trace Receive\r\n");
    for(uint32_t i=0; i < *Len; i++){
        while(USBUART_DataIsReady() == 0);
        Buf[i] = USBUART_GetChar();
    }
  return (0);
}
*/

/**
  * @brief  CDC_Transmit_FS
  *         Data send over USB IN endpoint are sent over CDC interface 
  *         through this function.           
  *         @note
  *         
  *                 
  * @param  Buf: Buffer of data to be send
  * @param  Len: Number of data to be send (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  //BT_UART_PutString("USB Trace Transmit\r\n");
  //int transmitOffset = 0;

  //int j;
  //BT_UART_PutArray(Buf,Len);
    for(int i=0; i<Len; i++){
        while(BT_UART_ReadTxStatus() == BT_UART_TX_STS_FIFO_FULL);
        BT_UART_PutChar(Buf[i]);
    }
    
  //while(transmitOffset < Len) {
      //while(!USBUART_CDCIsReady());
      //if(transmitOffset + 64 < Len) {
      //  USBUART_PutData(&Buf[transmitOffset], 64);
      //} else {
      //  USBUART_PutData(&Buf[transmitOffset], Len - transmitOffset);
      //}
      
      //transmitOffset += 64;
    //}

  return 0;
}

int32_t trcCDCReceive(void *data, uint32_t size, int32_t* NumBytes)
{
    //BT_UART_PutString("USB Attempt Read\r\n");
    //for(uint32_t j = 0; j < size; j++) {
        //while(USBUART_GetCount() == 0);
            //BT_UART_PutString("USB Trace Receive\r\n");
        //    while(USBUART_DataIsReady() == 0);
            //commandBuffer.data[commandBuffer.idx] = USBUART_GetChar();
            if(BT_UART_ReadRxStatus() == BT_UART_RX_STS_FIFO_NOTEMPTY){
                for(int i =0; i < size; i++){
                    while(BT_UART_ReadRxStatus() != BT_UART_RX_STS_FIFO_NOTEMPTY);
                    commandBuffer.data[commandBuffer.idx] = BT_UART_GetChar();
        	        commandBuffer.idx = commandBuffer.idx + 1;
                }
            }
    //}
    
	uint32_t i,diff;

	if(commandBuffer.idx>0)
	{
		if (size >= commandBuffer.idx) // more than what is stored, nr of bytes will be .idx
		{
			memcpy(data,commandBuffer.data, commandBuffer.idx);
			*NumBytes=commandBuffer.idx;
			commandBuffer.idx=0; // Make the buffer ready for a new command
		}
		else  //If some data in the buffer is not read
		{
			diff = commandBuffer.idx-size;
			memcpy(data,commandBuffer.data, size);
			for(i=0;i<diff;i++)
			{
				commandBuffer.data[i]=commandBuffer.data[i+size];
			}
			*NumBytes=size;
			commandBuffer.idx=diff;
		}
	}
	else
	{
		*NumBytes=0;
	}
	return 0;
}

int32_t trcCDCTransmit(void* data, uint32_t size, int32_t * noOfBytesSent )
{
	int32_t result;
	result=CDC_Transmit_FS(data,size);
	*noOfBytesSent=size;

	return result;
}

#endif	/*(TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)*/
#endif  /*(TRC_USE_TRACEALYZER_RECORDER == 1)*/

