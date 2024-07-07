/******************************************************************************
*
* Register Bit Structured header file for INPUT_XBAR
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
#ifndef __F2837xD_INPUT_XBAR_H__
#define __F2837xD_INPUT_XBAR_H__

#ifdef __cplusplus 
extern "C" {
#endif 


//---------------------------------------------------------------------------
// INPUT_XBAR Individual Register Bit Definitions:

struct INPUTSELECTLOCK_BITS {           // bits description
    Uint16 INPUT1SELECT:1;              // 0 Lock bit for INPUT1SEL Register
    Uint16 INPUT2SELECT:1;              // 1 Lock bit for INPUT2SEL Register
    Uint16 INPUT3SELECT:1;              // 2 Lock bit for INPUT3SEL Register
    Uint16 INPUT4SELECT:1;              // 3 Lock bit for INPUT4SEL Register
    Uint16 INPUT5SELECT:1;              // 4 Lock bit for INPUT5SEL Register
    Uint16 INPUT6SELECT:1;              // 5 Lock bit for INPUT7SEL Register
    Uint16 INPUT7SELECT:1;              // 6 Lock bit for INPUT8SEL Register
    Uint16 INPUT8SELECT:1;              // 7 Lock bit for INPUT9SEL Register
    Uint16 INPUT9SELECT:1;              // 8 Lock bit for INPUT10SEL Register
    Uint16 INPUT10SELECT:1;             // 9 Lock bit for INPUT11SEL Register
    Uint16 INPUT11SELECT:1;             // 10 Lock bit for INPUT11SEL Register
    Uint16 INPUT12SELECT:1;             // 11 Lock bit for INPUT12SEL Register
    Uint16 INPUT13SELECT:1;             // 12 Lock bit for INPUT13SEL Register
    Uint16 INPUT14SELECT:1;             // 13 Lock bit for INPUT14SEL Register
    Uint16 INPUT15SELECT:1;             // 14 Lock bit for INPUT15SEL Register
    Uint16 INPUT16SELECT:1;             // 15 Lock bit for INPUT16SEL Register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union INPUTSELECTLOCK_REG {
    Uint32  all;
    struct  INPUTSELECTLOCK_BITS  bit;
};

struct TRIGLATCH1_BITS {                // bits description
    Uint16 CMPSS1_CTRIPL:1;             // 0 Input Latch for CMPSS1.CTRIPL Signal
    Uint16 CMPSS1_CTRIPH:1;             // 1 Input Latch for CMPSS1.CTRIPH Signal
    Uint16 CMPSS2_CTRIPL:1;             // 2 Input Latch for CMPSS2.CTRIPL Signal
    Uint16 CMPSS2_CTRIPH:1;             // 3 Input Latch for CMPSS2.CTRIPH Signal
    Uint16 CMPSS3_CTRIPL:1;             // 4 Input Latch for CMPSS3.CTRIPL Signal
    Uint16 CMPSS3_CTRIPH:1;             // 5 Input Latch for CMPSS3.CTRIPH Signal
    Uint16 CMPSS4_CTRIPL:1;             // 6 Input Latch for CMPSS4.CTRIPL Signal
    Uint16 CMPSS4_CTRIPH:1;             // 7 Input Latch for CMPSS4.CTRIPH Signal
    Uint16 CMPSS5_CTRIPL:1;             // 8 Input Latch for CMPSS5.CTRIPL Signal
    Uint16 CMPSS5_CTRIPH:1;             // 9 Input Latch for CMPSS5.CTRIPH Signal
    Uint16 CMPSS6_CTRIPL:1;             // 10 Input Latch for CMPSS6.CTRIPL Signal
    Uint16 CMPSS6_CTRIPH:1;             // 11 Input Latch for CMPSS6.CTRIPH Signal
    Uint16 CMPSS7_CTRIPL:1;             // 12 Input Latch for CMPSS7.CTRIPL Signal
    Uint16 CMPSS7_CTRIPH:1;             // 13 Input Latch for CMPSS7.CTRIPH Signal
    Uint16 CMPSS8_CTRIPL:1;             // 14 Input Latch for CMPSS8.CTRIPL Signal
    Uint16 CMPSS8_CTRIPH:1;             // 15 Input Latch for CMPSS8.CTRIPH Signal
    Uint16 CMPSS1_CTRIPOUTL:1;          // 16 Input Latch for CMPSS1.CTRIPOUTL Signal
    Uint16 CMPSS1_CTRIPOUTH:1;          // 17 Input Latch for CMPSS1.CTRIPOUTH Signal
    Uint16 CMPSS2_CTRIPOUTL:1;          // 18 Input Latch for CMPSS2.CTRIPOUTL Signal
    Uint16 CMPSS2_CTRIPOUTH:1;          // 19 Input Latch for CMPSS2.CTRIPOUTH Signal
    Uint16 CMPSS3_CTRIPOUTL:1;          // 20 Input Latch for CMPSS3.CTRIPOUTL Signal
    Uint16 CMPSS3_CTRIPOUTH:1;          // 21 Input Latch for CMPSS3.CTRIPOUTH Signal
    Uint16 CMPSS4_CTRIPOUTL:1;          // 22 Input Latch for CMPSS4.CTRIPOUTL Signal
    Uint16 CMPSS4_CTRIPOUTH:1;          // 23 Input Latch for CMPSS4.CTRIPOUTH Signal
    Uint16 CMPSS5_CTRIPOUTL:1;          // 24 Input Latch for CMPSS5.CTRIPOUTL Signal
    Uint16 CMPSS5_CTRIPOUTH:1;          // 25 Input Latch for CMPSS5.CTRIPOUTH Signal
    Uint16 CMPSS6_CTRIPOUTL:1;          // 26 Input Latch for CMPSS6.CTRIPOUTL Signal
    Uint16 CMPSS6_CTRIPOUTH:1;          // 27 Input Latch for CMPSS6.CTRIPOUTH Signal
    Uint16 CMPSS7_CTRIPOUTL:1;          // 28 Input Latch for CMPSS7.CTRIPOUTL Signal
    Uint16 CMPSS7_CTRIPOUTH:1;          // 29 Input Latch for CMPSS7.CTRIPOUTH Signal
    Uint16 CMPSS8_CTRIPOUTL:1;          // 30 Input Latch for CMPSS8.CTRIPOUTL Signal
    Uint16 CMPSS8_CTRIPOUTH:1;          // 31 Input Latch for CMPSS8.CTRIPOUTH Signal
};

union TRIGLATCH1_REG {
    Uint32  all;
    struct  TRIGLATCH1_BITS  bit;
};

struct TRIGLATCH2_BITS {                // bits description
    Uint16 INPUT1:1;                    // 0 Input Latch for INPUT1 Signal
    Uint16 INPUT2:1;                    // 1 Input Latch for INPUT2 Signal
    Uint16 INPUT3:1;                    // 2 Input Latch for INPUT3 Signal
    Uint16 INPUT4:1;                    // 3 Input Latch for INPUT4 Signal
    Uint16 INPUT5:1;                    // 4 Input Latch for INPUT5 Signal
    Uint16 INPUT7:1;                    // 5 Input Latch for INPUT7 Signal
    Uint16 ADCSOCA:1;                   // 6 Input Latch for ADCSOCA Signal
    Uint16 ADCSOCB:1;                   // 7 Input Latch for ADCSOCB Signal
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:1;                     // 13 Reserved
    Uint16 rsvd7:1;                     // 14 Reserved
    Uint16 rsvd8:1;                     // 15 Reserved
    Uint16 ECAP1_OUT:1;                 // 16 Input Latch for ECAP1.OUT Signal
    Uint16 ECAP2_OUT:1;                 // 17 Input Latch for ECAP2.OUT Signal
    Uint16 ECAP3_OUT:1;                 // 18 Input Latch for ECAP3.OUT Signal
    Uint16 ECAP4_OUT:1;                 // 19 Input Latch for ECAP4.OUT Signal
    Uint16 ECAP5_OUT:1;                 // 20 Input Latch for ECAP5.OUT Signal
    Uint16 ECAP6_OUT:1;                 // 21 Input Latch for ECAP6.OUT Signal
    Uint16 EXTSYNCOUT:1;                // 22 Input Latch for EXTSYNCOUT Signal
    Uint16 ADCAEVT1:1;                  // 23 Input Latch for ADCAEVT1 Signal
    Uint16 ADCAEVT2:1;                  // 24 Input Latch for ADCAEVT2 Signal
    Uint16 ADCAEVT3:1;                  // 25 Input Latch for ADCAEVT3 Signal
    Uint16 ADCAEVT4:1;                  // 26 Input Latch for ADCAEVT4 Signal
    Uint16 ADCBEVT1:1;                  // 27 Input Latch for ADCBEVT1 Signal
    Uint16 ADCBEVT2:1;                  // 28 Input Latch for ADCBEVT2 Signal
    Uint16 ADCBEVT3:1;                  // 29 Input Latch for ADCBEVT3 Signal
    Uint16 ADCBEVT4:1;                  // 30 Input Latch for ADCBEVT4 Signal
    Uint16 ADCCEVT1:1;                  // 31 Input Latch for ADCCEVT1 Signal
};

union TRIGLATCH2_REG {
    Uint32  all;
    struct  TRIGLATCH2_BITS  bit;
};

struct TRIGLATCH3_BITS {                // bits description
    Uint16 ADCCEVT2:1;                  // 0 Input Latch for ADCCEVT2 Signal
    Uint16 ADCCEVT3:1;                  // 1 Input Latch for ADCCEVT3 Signal
    Uint16 ADCCEVT4:1;                  // 2 Input Latch for ADCCEVT4 Signal
    Uint16 ADCDEVT1:1;                  // 3 Input Latch for ADCDEVT1 Signal
    Uint16 ADCDEVT2:1;                  // 4 Input Latch for ADCDEVT2 Signal
    Uint16 ADCDEVT3:1;                  // 5 Input Latch for ADCDEVT3 Signal
    Uint16 ADCDEVT4:1;                  // 6 Input Latch for ADCDEVT4 Signal
    Uint16 SD1FLT1_COMPL:1;             // 7 Input Latch for SD1FLT1.COMPL Signal
    Uint16 SD1FLT1_COMPH:1;             // 8 Input Latch for SD1FLT1.COMPH Signal
    Uint16 SD1FLT2_COMPL:1;             // 9 Input Latch for SD1FLT2.COMPL Signal
    Uint16 SD1FLT2_COMPH:1;             // 10 Input Latch for SD1FLT2.COMPH Signal
    Uint16 SD1FLT3_COMPL:1;             // 11 Input Latch for SD1FLT3.COMPL Signal
    Uint16 SD1FLT3_COMPH:1;             // 12 Input Latch for SD1FLT3.COMPH Signal
    Uint16 SD1FLT4_COMPL:1;             // 13 Input Latch for SD1FLT4.COMPL Signal
    Uint16 SD1FLT4_COMPH:1;             // 14 Input Latch for SD1FLT4.COMPH Signal
    Uint16 SD2FLT1_COMPL:1;             // 15 Input Latch for SD2FLT1.COMPL Signal
    Uint16 SD2FLT1_COMPH:1;             // 16 Input Latch for SD2FLT1.COMPH Signal
    Uint16 SD2FLT2_COMPL:1;             // 17 Input Latch for SD2FLT2.COMPL Signal
    Uint16 SD2FLT2_COMPH:1;             // 18 Input Latch for SD2FLT2.COMPH Signal
    Uint16 SD2FLT3_COMPL:1;             // 19 Input Latch for SD2FLT3.COMPL Signal
    Uint16 SD2FLT3_COMPH:1;             // 20 Input Latch for SD2FLT3.COMPH Signal
    Uint16 SD2FLT4_COMPL:1;             // 21 Input Latch for SD2FLT4.COMPL Signal
    Uint16 SD2FLT4_COMPH:1;             // 22 Input Latch for SD2FLT4.COMPH Signal
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union TRIGLATCH3_REG {
    Uint32  all;
    struct  TRIGLATCH3_BITS  bit;
};

struct TRIGLATCHCLR1_BITS {             // bits description
    Uint16 CMPSS1_CTRIPL:1;             // 0 Input Latch Clear for CMPSS1.CTRIPL Signal
    Uint16 CMPSS1_CTRIPH:1;             // 1 Input Latch Clear for CMPSS1.CTRIPH Signal
    Uint16 CMPSS2_CTRIPL:1;             // 2 Input Latch Clear for CMPSS2.CTRIPL Signal
    Uint16 CMPSS2_CTRIPH:1;             // 3 Input Latch Clear for CMPSS2.CTRIPH Signal
    Uint16 CMPSS3_CTRIPL:1;             // 4 Input Latch Clear for CMPSS3.CTRIPL Signal
    Uint16 CMPSS3_CTRIPH:1;             // 5 Input Latch Clear for CMPSS3.CTRIPH Signal
    Uint16 CMPSS4_CTRIPL:1;             // 6 Input Latch Clear for CMPSS4.CTRIPL Signal
    Uint16 CMPSS4_CTRIPH:1;             // 7 Input Latch Clear for CMPSS4.CTRIPH Signal
    Uint16 CMPSS5_CTRIPL:1;             // 8 Input Latch Clear for CMPSS5.CTRIPL Signal
    Uint16 CMPSS5_CTRIPH:1;             // 9 Input Latch Clear for CMPSS5.CTRIPH Signal
    Uint16 CMPSS6_CTRIPL:1;             // 10 Input Latch Clear for CMPSS6.CTRIPL Signal
    Uint16 CMPSS6_CTRIPH:1;             // 11 Input Latch Clear for CMPSS6.CTRIPH Signal
    Uint16 CMPSS7_CTRIPL:1;             // 12 Input Latch Clear for CMPSS7.CTRIPL Signal
    Uint16 CMPSS7_CTRIPH:1;             // 13 Input Latch Clear for CMPSS7.CTRIPH Signal
    Uint16 CMPSS8_CTRIPL:1;             // 14 Input Latch Clear for CMPSS8.CTRIPL Signal
    Uint16 CMPSS8_CTRIPH:1;             // 15 Input Latch Clear for CMPSS8.CTRIPH Signal
    Uint16 CMPSS1_CTRIPOUTL:1;          // 16 Input Latch Clear for CMPSS1.CTRIPOUTL Signal
    Uint16 CMPSS1_CTRIPOUTH:1;          // 17 Input Latch Clear for CMPSS1.CTRIPOUTH Signal
    Uint16 CMPSS2_CTRIPOUTL:1;          // 18 Input Latch Clear for CMPSS2.CTRIPOUTL Signal
    Uint16 CMPSS2_CTRIPOUTH:1;          // 19 Input Latch Clear for CMPSS2.CTRIPOUTH Signal
    Uint16 CMPSS3_CTRIPOUTL:1;          // 20 Input Latch Clear for CMPSS3.CTRIPOUTL Signal
    Uint16 CMPSS3_CTRIPOUTH:1;          // 21 Input Latch Clear for CMPSS3.CTRIPOUTH Signal
    Uint16 CMPSS4_CTRIPOUTL:1;          // 22 Input Latch Clear for CMPSS4.CTRIPOUTL Signal
    Uint16 CMPSS4_CTRIPOUTH:1;          // 23 Input Latch Clear for CMPSS4.CTRIPOUTH Signal
    Uint16 CMPSS5_CTRIPOUTL:1;          // 24 Input Latch Clear for CMPSS5.CTRIPOUTL Signal
    Uint16 CMPSS5_CTRIPOUTH:1;          // 25 Input Latch Clear for CMPSS5.CTRIPOUTH Signal
    Uint16 CMPSS6_CTRIPOUTL:1;          // 26 Input Latch Clear for CMPSS6.CTRIPOUTL Signal
    Uint16 CMPSS6_CTRIPOUTH:1;          // 27 Input Latch Clear for CMPSS6.CTRIPOUTH Signal
    Uint16 CMPSS7_CTRIPOUTL:1;          // 28 Input Latch Clear for CMPSS7.CTRIPOUTL Signal
    Uint16 CMPSS7_CTRIPOUTH:1;          // 29 Input Latch Clear for CMPSS7.CTRIPOUTH Signal
    Uint16 CMPSS8_CTRIPOUTL:1;          // 30 Input Latch Clear for CMPSS8.CTRIPOUTL Signal
    Uint16 CMPSS8_CTRIPOUTH:1;          // 31 Input Latch Clear for CMPSS8.CTRIPOUTH Signal
};

union TRIGLATCHCLR1_REG {
    Uint32  all;
    struct  TRIGLATCHCLR1_BITS  bit;
};

struct TRIGLATCHCLR2_BITS {             // bits description
    Uint16 INPUT1:1;                    // 0 Input Latch Clear for INPUT1 Signal
    Uint16 INPUT2:1;                    // 1 Input Latch Clear for INPUT2 Signal
    Uint16 INPUT3:1;                    // 2 Input Latch Clear for INPUT3 Signal
    Uint16 INPUT4:1;                    // 3 Input Latch Clear for INPUT4 Signal
    Uint16 INPUT5:1;                    // 4 Input Latch Clear for INPUT5 Signal
    Uint16 INPUT7:1;                    // 5 Input Latch Clear for INPUT7 Signal
    Uint16 ADCSOCA:1;                   // 6 Input Latch Clear for ADCSOCA Signal
    Uint16 ADCSOCB:1;                   // 7 Input Latch Clear for ADCSOCB Signal
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:1;                     // 13 Reserved
    Uint16 rsvd7:1;                     // 14 Reserved
    Uint16 rsvd8:1;                     // 15 Reserved
    Uint16 ECAP1_OUT:1;                 // 16 Input Latch Clear for ECAP1.OUT Signal
    Uint16 ECAP2_OUT:1;                 // 17 Input Latch Clear for ECAP2.OUT Signal
    Uint16 ECAP3_OUT:1;                 // 18 Input Latch Clear for ECAP3.OUT Signal
    Uint16 ECAP4_OUT:1;                 // 19 Input Latch Clear for ECAP4.OUT Signal
    Uint16 ECAP5_OUT:1;                 // 20 Input Latch Clear for ECAP5.OUT Signal
    Uint16 ECAP6_OUT:1;                 // 21 Input Latch Clear for ECAP6.OUT Signal
    Uint16 EXTSYNCOUT:1;                // 22 Input Latch Clear for EXTSYNCOUT Signal
    Uint16 ADCAEVT1:1;                  // 23 Input Latch Clear for ADCAEVT1 Signal
    Uint16 ADCAEVT2:1;                  // 24 Input Latch Clear for ADCAEVT2 Signal
    Uint16 ADCAEVT3:1;                  // 25 Input Latch Clear for ADCAEVT3 Signal
    Uint16 ADCAEVT4:1;                  // 26 Input Latch Clear for ADCAEVT4 Signal
    Uint16 ADCBEVT1:1;                  // 27 Input Latch Clear for ADCBEVT1 Signal
    Uint16 ADCBEVT2:1;                  // 28 Input Latch Clear for ADCBEVT2 Signal
    Uint16 ADCBEVT3:1;                  // 29 Input Latch Clear for ADCBEVT3 Signal
    Uint16 ADCBEVT4:1;                  // 30 Input Latch Clear for ADCBEVT4 Signal
    Uint16 ADCCEVT1:1;                  // 31 Input Latch Clear for ADCCEVT1 Signal
};

union TRIGLATCHCLR2_REG {
    Uint32  all;
    struct  TRIGLATCHCLR2_BITS  bit;
};

struct TRIGLATCHCLR3_BITS {             // bits description
    Uint16 ADCCEVT2:1;                  // 0 Input Latch Clear for ADCCEVT2 Signal
    Uint16 ADCCEVT3:1;                  // 1 Input Latch Clear for ADCCEVT3 Signal
    Uint16 ADCCEVT4:1;                  // 2 Input Latch Clear for ADCCEVT4 Signal
    Uint16 ADCDEVT1:1;                  // 3 Input Latch Clear for ADCDEVT1 Signal
    Uint16 ADCDEVT2:1;                  // 4 Input Latch Clear for ADCDEVT2 Signal
    Uint16 ADCDEVT3:1;                  // 5 Input Latch Clear for ADCDEVT3 Signal
    Uint16 ADCDEVT4:1;                  // 6 Input Latch Clear for ADCDEVT4 Signal
    Uint16 SD1FLT1_COMPL:1;             // 7 Input Latch Clear for SD1FLT1.COMPL Signal
    Uint16 SD1FLT1_COMPH:1;             // 8 Input Latch Clear for SD1FLT1.COMPH Signal
    Uint16 SD1FLT2_COMPL:1;             // 9 Input Latch Clear for SD1FLT2.COMPL Signal
    Uint16 SD1FLT2_COMPH:1;             // 10 Input Latch Clear for SD1FLT2.COMPH Signal
    Uint16 SD1FLT3_COMPL:1;             // 11 Input Latch Clear for SD1FLT3.COMPL Signal
    Uint16 SD1FLT3_COMPH:1;             // 12 Input Latch Clear for SD1FLT3.COMPH Signal
    Uint16 SD1FLT4_COMPL:1;             // 13 Input Latch Clear for SD1FLT4.COMPL Signal
    Uint16 SD1FLT4_COMPH:1;             // 14 Input Latch Clear for SD1FLT4.COMPH Signal
    Uint16 SD2FLT1_COMPL:1;             // 15 Input Latch Clear for SD2FLT1.COMPL Signal
    Uint16 SD2FLT1_COMPH:1;             // 16 Input Latch Clear for SD2FLT1.COMPH Signal
    Uint16 SD2FLT2_COMPL:1;             // 17 Input Latch Clear for SD2FLT2.COMPL Signal
    Uint16 SD2FLT2_COMPH:1;             // 18 Input Latch Clear for SD2FLT2.COMPH Signal
    Uint16 SD2FLT3_COMPL:1;             // 19 Input Latch Clear for SD2FLT3.COMPL Signal
    Uint16 SD2FLT3_COMPH:1;             // 20 Input Latch Clear for SD2FLT3.COMPH Signal
    Uint16 SD2FLT4_COMPL:1;             // 21 Input Latch Clear for SD2FLT4.COMPL Signal
    Uint16 SD2FLT4_COMPH:1;             // 22 Input Latch Clear for SD2FLT4.COMPH Signal
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union TRIGLATCHCLR3_REG {
    Uint32  all;
    struct  TRIGLATCHCLR3_BITS  bit;
};

struct INPUT_XBAR_REGS {
    Uint16                                   INPUT1SELECT;                 // INPUT1 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT2SELECT;                 // INPUT2 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT3SELECT;                 // INPUT3 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT4SELECT;                 // INPUT4 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT5SELECT;                 // INPUT5 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT6SELECT;                 // INPUT6 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT7SELECT;                 // INPUT7 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT8SELECT;                 // INPUT8 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT9SELECT;                 // INPUT9 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT10SELECT;                // INPUT10 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT11SELECT;                // INPUT11 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT12SELECT;                // INPUT12 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT13SELECT;                // INPUT13 Input Select Register (GPIO0 to x)
    Uint16                                   INPUT14SELECT;                // INPUT14 Input Select Register (GPIO0 to x)
    Uint16                                   rsvd1[16];                    // Reserved
    union   INPUTSELECTLOCK_REG              INPUTSELECTLOCK;              // Input Select Lock Register
    union   TRIGLATCH1_REG                   TRIGLATCH1;                   // X-Bar Input Latch Register 1
    union   TRIGLATCH2_REG                   TRIGLATCH2;                   // X-Bar Input Latch Register 2
    union   TRIGLATCH3_REG                   TRIGLATCH3;                   // X-Bar Input Latch Register 3
    Uint16                                   rsvd2[2];                     // Reserved
    union   TRIGLATCHCLR1_REG                TRIGLATCHCLR1;                // X-Bar Input Latch Clear Register 1
    union   TRIGLATCHCLR2_REG                TRIGLATCHCLR2;                // X-Bar Input Latch Clear Register 2
    union   TRIGLATCHCLR3_REG                TRIGLATCHCLR3;                // X-Bar Input Latch Clear Register 3
};

//---------------------------------------------------------------------------
// INPUT_XBAR External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct INPUT_XBAR_REGS InputXbarRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
