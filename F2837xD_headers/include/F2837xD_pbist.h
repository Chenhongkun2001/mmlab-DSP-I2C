//###########################################################################
//
// FILE:   F2837x_PBIST.h
//
// TITLE:  F2837x Device PBIST Register Definitions.
//
// BUILD:  CUSTOMER RELEASE
//
//###########################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//###########################################################################

#ifndef F2837x_PBIST_H
#define F2837x_PBIST_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// PBIST Individual Register Bit Definitions:

struct PACT_BITS {                                    // bit descriptions
    Uint16  ENABLE:1;                                 // 0 Enable clocks to PBIST 
    Uint16  rsvd1:15;                                 // 15:1 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union PACT_REG {
    Uint32  all;  
    struct  PACT_BITS  bit;  
};

struct OVERRIDE_BITS {                                // bit descriptions
    Uint16  RINFO_MEM_OVER:1;                         // 0 ROM Memory Information Override 
    Uint16  rsvd1:2;                                  // 2:1 Reserved 
    Uint16  ALGO_OVER:1;                              // 3 ROM Algorithm Override 
    Uint16  rsvd2:12;                                 // 15:4 Reserved 
    Uint16  rsvd3:16;                                 // 31:16 Reserved 
};

union OVERRIDE_REG {
    Uint32  all;  
    struct  OVERRIDE_BITS  bit;  
};

struct DLRT_BITS {                                    // bit descriptions
    Uint16  rsvd1:2;                                  // 1:0 Reserved 
    Uint16  ROM_TEST:1;                               // 2 ROM-based testing 
    Uint16  TCK_GATED:1;                              // 3 TCK gated 
    Uint16  CONFIG_ACC:1;                             // 4 Config Access 
    Uint16  rsvd2:4;                                  // 8:5 Reserved 
    Uint16  GO_NOGO_TEST:1;                           // 9 GO/ NO-GO Testing 
    Uint16  rsvd3:6;                                  // 15:10 Reserved 
    Uint16  rsvd4:16;                                 // 31:16 Reserved 
};

union DLRT_REG {
    Uint32  all;  
    struct  DLRT_BITS  bit;  
};

struct RAMT_BITS {                                    // bit descriptions
    Uint16  rsvd1:16;                                 // 15:0 Reserved 
    Uint16  RDS:8;                                    // 23:16 Return Data Select 
    Uint16  RGS:8;                                    // 31:24 RAM Group Select 
};

union RAMT_REG {
    Uint32  all;  
    struct  RAMT_BITS  bit;  
};

struct STR_BITS {                                     // bit descriptions
    Uint16  rsvd1:1;                                  // 0:0 Reserved 
    Uint16  RESUME:1;                                 // 1 Resume / Emulation Read 
    Uint16  STOP:1;                                   // 2 Stops PBIST testing 
    Uint16  rsvd2:13;                                 // 15:3 Reserved 
    Uint16  rsvd3:16;                                 // 31:16 Reserved 
};

union STR_REG {
    Uint32  all;  
    struct  STR_BITS  bit;  
};

#if defined(CPU1)
struct PBIST_REGS {
    Uint16                  rsvd1[352];               // Reserved 
    union   RAMT_REG        RAMT;                     // RAM Configuration Register 
    Uint16                  rsvd2[2];                 // Reserved 
    union   DLRT_REG        DLRT;                     // PBIST Data Logger Register 
    Uint16                  rsvd3[6];                 // Reserved 
    union   STR_REG         STR;                      // Program Control Register 
    Uint16                  rsvd4[18];                // Reserved 
    union   PACT_REG        PACT;                     // PBIST Activate Register 
    Uint16                  rsvd5[6];                 // Reserved 
    union   OVERRIDE_REG    OVERRIDE;                 // PBIST Override Register 
    Uint16                  rsvd6[6];                 // Reserved 
    Uint32                  FSRF0;                    // Fail Status - Port 0 
    Uint16                  rsvd7[2];                 // Reserved 
    Uint32                  FSRF1;                    // Fail Status - Port 1 
    Uint16                  rsvd8[2];                 // Reserved 
    Uint32                  FSRC0;                    // Fail Status Count - Port 0 
    Uint16                  rsvd9[2];                 // Reserved 
    Uint32                  FSRC1;                    // Fail Status Count - Port 1 
    Uint16                  rsvd10[38];               // Reserved 
    Uint32                  ALGO;                     // PBIST Algorithm 
    Uint16                  rsvd11[2];                // Reserved 
    Uint32                  RINFOL;                   // RAM Info Mask Register Lower 
    Uint16                  rsvd12[2];                // Reserved 
    Uint32                  RINFOU;                   // RAM Info Mask Register Higher 
    Uint16                  rsvd13[24];               // Reserved 
};
#endif

//---------------------------------------------------------------------------
// PBIST External References & Function Declarations:
//

#if defined(CPU1)
extern volatile struct PBIST_REGS PbistRegs;
#endif

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_PBIST_H definition
//===========================================================================
// End of file.
//===========================================================================
