/**
 * \file Cpu2_Main.c
 * \brief Main function definition for Cpu core 2 .
 *
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "Scu/Std/IfxScuWdt.h"
#include "Port\Std\IfxPort.h"
#include "main.h"
//#include "../Appli/BACK/demo_handler.h"

extern IfxCpu_mutexLock g_Asc0_Lock;

int core2_main (void)
{
	uint32_t tmpTick;

    IfxCpu_enableInterrupts();
    /*
     * !!WATCHDOG2 IS DISABLED HERE!!
     * Enable the watchdog in the demo if it is required and also service the watchdog periodically
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
    while (1)
    {
    	boolean flag = IfxCpu_acquireMutex(&g_Asc0_Lock);
    	if (flag){
    		printf("Cpu%d:%u Hz, Sys:%u Hz, Stm:%u Hz, Core:%04X,  %u\n",
    				IfxCpu_getCoreId(),
					SYSTEM_GetCpuClock(),
					SYSTEM_GetSysClock(),
					SYSTEM_GetStmClock(),
					__TRICORE_CORE__,
					schd_GetTick()
    		);

    		IfxCpu_releaseMutex(&g_Asc0_Lock);
    		IfxPort_togglePin(&MODULE_P33, 11);
    		//        	wait(100000);
    		tmpTick = schd_GetTick();
    		while((tmpTick+4*TEST_DELAY_MS) > schd_GetTick())
    		{
    			_nop();
    		}
    	}
/*
/*
    	if ( demo_idx == CORE_DEMO_INT) 	Core_DemoRun(0, 1);
    	else if ( demo_idx == CORE_DEMO_NO_INT) Core_DemoRun(0, 0);
*/
    }
    return (1);
}
