/******************************************************************************
*
* Register Bit Structured header file for CPUTIMER
*
* Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
* NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
* CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
*
******************************************************************************
*/
#ifndef __F2837xD_CPUTIMER_H__
#define __F2837xD_CPUTIMER_H__

#ifdef __cplusplus 
extern "C" {
#endif 


//---------------------------------------------------------------------------
// CPUTIMER Individual Register Bit Definitions:

struct TIM_BITS {                       // bits description
    Uint16 LSW:16;                      // 15:0 CPU-Timer Counter Registers
    Uint16 MSW:16;                      // 31:16 CPU-Timer Counter Registers High
};

union TIM_REG {
    Uint32  all;
    struct  TIM_BITS  bit;
};

struct PRD_BITS {                       // bits description
    Uint16 LSW:16;                      // 15:0 CPU-Timer Period Registers
    Uint16 MSW:16;                      // 31:16 CPU-Timer Period Registers High
};

union PRD_REG {
    Uint32  all;
    struct  PRD_BITS  bit;
};

struct TCR_BITS {                       // bits description
    Uint16 rsvd1:4;                     // 3:0 Reserved
    Uint16 TSS:1;                       // 4 CPU-Timer stop status bit.
    Uint16 TRB:1;                       // 5 Timer reload 
    Uint16 rsvd2:4;                     // 9:6 Reserved
    Uint16 SOFT:1;                      // 10 Emulation modes 
    Uint16 FREE:1;                      // 11 Emulation modes 
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 TIE:1;                       // 14 CPU-Timer Interrupt Enable.
    Uint16 TIF:1;                       // 15 CPU-Timer Interrupt Flag. 
};

union TCR_REG {
    Uint16  all;
    struct  TCR_BITS  bit;
};

struct TPR_BITS {                       // bits description
    Uint16 TDDR:8;                      // 7:0 CPU-Timer Divide-Down.
    Uint16 PSC:8;                       // 15:8 CPU-Timer Prescale Counter.
};

union TPR_REG {
    Uint16  all;
    struct  TPR_BITS  bit;
};

struct TPRH_BITS {                      // bits description
    Uint16 TDDRH:8;                     // 7:0 CPU-Timer Divide-Down.
    Uint16 PSCH:8;                      // 15:8 CPU-Timer Prescale Counter.
};

union TPRH_REG {
    Uint16  all;
    struct  TPRH_BITS  bit;
};

struct CPUTIMER_REGS {
    union   TIM_REG                          TIM;                          // CPU-Timer, Counter Register
    union   PRD_REG                          PRD;                          // CPU-Timer, Period Register
    union   TCR_REG                          TCR;                          // CPU-Timer, Control Register
    Uint16                                   rsvd1;                        // Reserved
    union   TPR_REG                          TPR;                          // CPU-Timer, Prescale Register
    union   TPRH_REG                         TPRH;                         // CPU-Timer, Prescale Register High
};

//---------------------------------------------------------------------------
// CPUTIMER External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct CPUTIMER_REGS CpuTimer0Regs;
extern volatile struct CPUTIMER_REGS CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS CpuTimer2Regs;
#endif
#ifdef CPU2
extern volatile struct CPUTIMER_REGS CpuTimer0Regs;
extern volatile struct CPUTIMER_REGS CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS CpuTimer2Regs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
