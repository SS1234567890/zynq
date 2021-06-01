/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"


int main()
{
	u32 data ;
    init_platform();
    char addr = 0x50 ;				// eeprom 设备地址 ;
    char data_arry[2] = {0x0 ,0x5a };
    print("Hello World SW \n\r");
    printf("IIC \n");
//    data = Xil_In32(0xFF03001C);
//    printf("addr : %x, value : %x \n",0xFF03001C,data) ;
//    data = Xil_In32(0xFF03002C);
//    printf("addr : %x, value : %x \n",0xFF03002C,data) ;
    data = 0x324e ;			 			//设置时钟频率100k
    Xil_Out32(0xFF030000, data) ;
//    data = Xil_In32(0xFF030000);
//    printf("addr : %x, value : %x \n",0xFF030000,data) ;
//    Xil_Out32(0xFF030014, 0x2) ;
//    Xil_Out32(0xFF03000C, data_arry[0]) ;
//    Xil_Out32(0xFF03000C, data_arry[1]) ;
//    Xil_Out32(0xFF030008, addr) ;
//    while(1)
//    {
//        data = Xil_In32(0xFF030010) ;
//        printf("addr : %x, value : %x \n",0xFF030010,data) ;
//        if(data == 0x1 )
//        {
//        	printf("wr done \n");
//        	break ;
//        }
//    }
//    Xil_Out32(0xFF030010,0x1);
//    data = Xil_In32(0xFF030010) ;
//    printf("addr : %x, value : %x \n",0xFF030010,data) ; // wirte end

    printf("read begin \n");

    data = Xil_In32(0xFF030000);
    printf("addr : %x, value : %x \n",0xFF030000,data) ;
    Xil_Out32(0xFF030014, 0x1) ;
    Xil_Out32(0xFF03000C, data_arry[0]) ;
    Xil_Out32(0xFF030008, addr) ;
    while(1)
       {
           data = Xil_In32(0xFF030010) ;
           printf("addr : %x, value : %x \n",0xFF030010,data) ;
           if(data == 0x1 )
           {
           	printf("wr done \n");
           	break ;
           }
       }
    data = 0x324f ;
    Xil_Out32(0xFF030000, data) ;
    data = Xil_In32(0xFF030000) ;
    printf("addr : %x, value : %x \n",0xFF030000,data) ;
    Xil_Out32(0xFF030014, 0x1) ;
    Xil_Out32(0xFF030008, addr) ;
    while (1)
    {
    	data = Xil_In32(0xFF030004) ;
    	printf("addr : %x, value : %x \n",0xFF030004,data) ;
    	data &= 0x20 ;
    	if(data == 0x20 )
    	{
        	data = Xil_In32(0xFF03000C) ;
        	printf("addr : %x, value : %x \n",0xFF03000c,data) ;
        	data = Xil_In32(0xFF030010) ;
        	printf("addr : %x, value : %x \n",0xFF030010,data) ;
        	if(data == 0x01)
        		break ;
    	}
    }
}
