//###########################################################################
// FILE:   F2837xD_hwbist.c
// TITLE:  C28 Driver for the HWBIST module.
//###########################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//###########################################################################

//*****************************************************************************
//! \addtogroup hwbist_api_c28 C28 HWBIST API Drivers
//! @{
//*****************************************************************************

#include "F2837xD_device.h"
#include "F2837xD_Hwbist_defines.h"

//////*****************************************************************************
//////
////// Always locate the NMI handler in RAM
//////
//////*****************************************************************************
//#pragma CODE_SECTION(F2837xD_HWBist_NmiHandler, "ramfuncs");

//*****************************************************************************
//
// Prototypes for the assembly functions located in F2837xD_hwbistcontext.s
//
//*****************************************************************************
extern void HWBISTASMSelfTestRun(void);         // C-callable HWBIST Assembly
                                                // Start Function
extern void HWBISTASMResetHandler(void);        // Address of HWBIST Reset
                                                // Routine (not C-callable)

//*****************************************************************************
//! Initializes the HWBIST module with default values.
//!
//! \param ulMicroInterval specifies the test micro interval. Valid values are
//!        TBD - TBD for Soprano F2837xD devices.
//! \param ulCoverage specifies the test coverage. Valid values are
//!        HWBIST_CONFIG_COV_95PERCENT and HWBIST_CONFIG_COV_99PERCENT.
//! \param ucShiftCLock specifies the scan chain shift clock divisor.
//!
//! \return None.
//*****************************************************************************
void HWBISTSelfTestInit(unsigned long ulMicroInterval,
                       unsigned long ulCoverage,
                       unsigned long ucShiftClock)
{
    EALLOW;

    //NOP_SEQUENCE();
    // Soft Reset the HWBIST Controller to put it in a known state
    HWBISTSoftReset();
    EALLOW;
    // Test micro interval
    HwbistRegs.CSTCGCR1 = ulMicroInterval;

    // Macro interval (always 1 for Soprano devices)
    HwbistRegs.CSTCGCR2.all = 0x00000001;

    // Coverage: 01:00 -> 00 - 99% coverage, 01 - 95% coverage
    HwbistRegs.CSTCGCR6.all = ulCoverage;

    // Restart test
    HwbistRegs.CSTCGCR5.all = 0x0000000a;

    // CSTCGCR7 configuration 07:00 - max chain length of 19 in Soprano
    // Shift Clock = DIV1 [0:0]
    if(ulCoverage == 0){
    	HwbistRegs.CSTCGCR7.all = 0x00010F13;
   	    // CSTCSADDR configuration
   	    HwbistRegs.CSTCSADDR.all = 0x4F4C4272;
    }
    else{
   		HwbistRegs.CSTCGCR7.all = 0x00000013;
   	    // CSTCSADDR configuration
   	    HwbistRegs.CSTCSADDR.all = 0x4E340000;
    }
    // CSTCGCR8 configuration
    HwbistRegs.CSTCGCR8.all = 0x00000032;

    // CSTCPCNT configuration
    HwbistRegs.CSTCPCNT.all = 0x012C06A4;



    //NOP_SEQUENCE();

    // Configuration complete
    HwbistRegs.CSTCCONFIG.all = 0x0000000a;

    // Return address after HWBIST reset (address of assembly routine)
    HwbistRegs.CSTCRET = (unsigned long)&HWBISTASMResetHandler;

    HWBISTShiftClockSet(ucShiftClock);

    EDIS;
}

//*****************************************************************************
//! Starts a HWBIST self-test run.  This will run one micro-interval.
//!
//! \return true on test completion, false otherwise.
//*****************************************************************************
int HWBISTSelfTestMicroRun(void)
{
    // Run the self-test assembly routine
    // A HWBIST self-test micro interval will run and return back here
    // after a HWBIST triggered CPU core reset
    HWBISTASMSelfTestRun();

    // Check for HWBIST test completion flags
    if(HwbistRegs.CSTCGSTAT.all)
    {
        // Finished HWBIST test run cycle
        // Call HWBISTResultGet() to retrieve the test result
        return(1);
    }

    // HWBIST test not complete
    // The user should continue to call this function until it returns 1
    return(0);
}

//*****************************************************************************
//! Runs a complete HWBIST test.  This function runs until the HWBIST test cycle
//! completes with a status value.  For ease of use, this function also
//! returns a pass or fail value indicating the pass or fail state of the
//! HWBIST test.
//!
//! \return true if the CPU logic passed MISR checks, false if the CPU logic
//!         failed MISR checks.
//*****************************************************************************
int HWBISTSelfTestFullRun()
{
    // Run back-to-back micro tests until test completes
    while(!HWBISTSelfTestMicroRun());

    // Return simple (true/false) test result
    return HWBISTResultBasicGet();
}

//*****************************************************************************
//! Restarts the HWBIST test state.
//!
//! \return None.
//*****************************************************************************
void HWBISTSelfTestRestart(void)
{
    EALLOW;
    HwbistRegs.CSTCGCR5.bit.RESTART = 0xA;      // RESTART
    EDIS;
}

//*****************************************************************************
//! SoftResets the HWBIST test state.
//!
//! \return None.
//*****************************************************************************
void HWBISTSoftReset(void)
{
    EALLOW;
    HwbistRegs.CSTCGCR5.all = 0x80000000;					// Soft Reset HWBIST Registers to make sure we aren't in a unexpected state
    HwbistRegs.CSTCGCR5.all = 0x00000000;					// Clear the HWBIST Soft Reset Bit
    EDIS;
}

//*****************************************************************************
//! Injects a logic error to test the HWBIST module.
//!
//! \param ulLogicError is used to inject a specific logic error. Set this
//!        to a non-zero number to inject a logic error.  Set to zero to
//!        disable logic error injection.
//!
//! \return None.
//*****************************************************************************
void HWBISTTestLogicSet(unsigned long ulLogicError)
{
    EALLOW;
    HwbistRegs.CSTCTEST.all |= (ulLogicError & 0xFFFFF) << 12;
    EDIS;
}

//*****************************************************************************
//! Injects a NMI error to test the HWBIST module.
//!
//! \param bEnable is used to set the NMI error mode.  Set this to true to
//!        inject a NMI error, set to false to disable NMI error injection.
//!
//! \return None.
//*****************************************************************************
void HWBISTTestNmiSet(int bEnable)
{
    EALLOW;

    if(bEnable)
    {
        HwbistRegs.CSTCTEST.all = 0x00000A00;
    }
    else
    {
        HwbistRegs.CSTCTEST.all = 0x00000000;
    }

    EDIS;
}

//*****************************************************************************
//! Injects a timeout error to test the HWBIST module.
//!
//! \param bEnable is used to set the timeout error mode.  Set this to true to
//!        inject a timeout error, set to false to disable NMI error injection.
//!
//! \return None.
//*****************************************************************************
void HWBISTTestTimeoutSet(int bEnable)
{
    EALLOW;

    if(bEnable)
    {
        HwbistRegs.CSTCTEST.all = 0x000A000;
    }
    else
    {
        HwbistRegs.CSTCTEST.all = 0x00000000;
    }

    EDIS;
}

//*****************************************************************************
//! Sets the HWBIST scan chain shift clock divider.
//!
//! \param ucShiftClock is the shift clock divider to use.  Valid values are
//!        HWBIST_CONFIG_SHIFTCLOCKDIV_1, HWBIST_CONFIG_SHIFTCLOCKDIV_2, and
//!        HWBIST_CONFIG_SHIFTCLOCKDIV_4.
//!
//! \return None.
//*****************************************************************************
void HWBISTShiftClockSet(unsigned long ucShiftClock)
{
    EALLOW;
    HwbistRegs.CSTCGCR7.all = (ucShiftClock  & 0x000C0000);
    EDIS;
}

//*****************************************************************************
//! Gets the HWBIST controller status register value.
//!
//! \return The HWBIST status register value.  To interpret the values, check
//!         the individual bits in the returned value.  Valid bit field values
//!         are HWBIST_RESULT_BISTDONE, HWBIST_RESULT_BISTDONE,
//!         HWBIST_RESULT_BISTFAIL, HWBIST_RESULT_INTCMPF, and
//!         HWBIST_RESULT_TOFAIL.
//*****************************************************************************
unsigned long HWBISTResultGet(void)
{
    return HwbistRegs.CSTCGSTAT.all;
}

//*****************************************************************************
//! Gets the basic status of the HWBIST test.  This function interprets the
//! status flags and MISR value and returns a simple pass or fail indicating
//! if the CPU core passed or failed the test.
//!
//! \return true if the CPU logic passed MISR checks, false if the CPU logic
//!         failed MISR checks.
//*****************************************************************************
int HWBISTResultBasicGet(void)
{
    unsigned long ulBistResult = HWBISTResultGet();

    if(((ulBistResult & HWBIST_RESULT_BISTDONE) > 0) &&
       ((ulBistResult & HWBIST_RESULT_TOFAIL) == 0) &&
       ((ulBistResult & HWBIST_RESULT_INTCMPF) == 0) &&
       ((ulBistResult & HWBIST_RESULT_BISTFAIL) == 0) &&
       ((ulBistResult & HWBIST_RESULT_NMI) == 0))
    {
        // BIST test flags show that the test controller
        // did not detect any errors, but we still have to
        // check the MISR value
        if(HWBISTCompareMisr(HWBISTMisrGet(), HWBISTMisrGoldenGet()))
        {
            // MISR comparison passed
            return(1);
        }
    }

    // Test not complete or HWBIST failure
    return(0);
}

//*****************************************************************************
//! Gets the HWBIST test MISR value
//!
//! \return The MISR value.  Note that the value is returned as a tMisr type.
//!         Use the HWBISTCompareMisr(...) function to compare tMisr types.
//*****************************************************************************
tMisr HWBISTMisrGet(void)
{
    tMisr mResult;
    mResult.Misr0 = HwbistRegs.CSTCMISR0;
    mResult.Misr1 = HwbistRegs.CSTCMISR1;
    mResult.Misr2 = HwbistRegs.CSTCMISR2;
    mResult.Misr3 = HwbistRegs.CSTCMISR3;
    mResult.Misr4 = HwbistRegs.CSTCMISR4;
    mResult.Misr5 = HwbistRegs.CSTCMISR5;
    mResult.Misr6 = HwbistRegs.CSTCMISR6;
    mResult.Misr7 = HwbistRegs.CSTCMISR7;
    mResult.Misr8 = HwbistRegs.CSTCMISR8;
    mResult.Misr9 = HwbistRegs.CSTCMISR9;
    mResult.Misr10 = HwbistRegs.CSTCMISR10;
    mResult.Misr11 = HwbistRegs.CSTCMISR11;
    mResult.Misr12 = HwbistRegs.CSTCMISR12;
    mResult.Misr13 = HwbistRegs.CSTCMISR13;
    mResult.Misr14 = HwbistRegs.CSTCMISR14;
    mResult.Misr15 = HwbistRegs.CSTCMISR15;
    return(mResult);
}

//*****************************************************************************
//! Gets the HWBIST Golden MISR value from ROM.  This function returns either
//! the 95% coverage value or the 99% coverage value depending on the
//! selected test coverage.
//!
//! \return The MISR value.  Note that the value is returned as a tMisr type.
//!         Use the HWBISTCompareMisr(...) function to compare tMisr types.
//*****************************************************************************
tMisr HWBISTMisrGoldenGet(void)
{
    tMisr mResult;

    // Read golden MISR from ROM based on current configuration
    switch(HwbistRegs.CSTCGCR6.bit.COV)
    {
    case HWBIST_CONFIG_COV_95PERCENT:
        mResult.Misr0 = (HWBIST_95PERCENT_MISR0);
        mResult.Misr1 = (HWBIST_95PERCENT_MISR1);
        mResult.Misr2 = (HWBIST_95PERCENT_MISR2);
        mResult.Misr3 = (HWBIST_95PERCENT_MISR3);
        mResult.Misr4 = (HWBIST_95PERCENT_MISR4);
        mResult.Misr5 = (HWBIST_95PERCENT_MISR5);
        mResult.Misr6 = (HWBIST_95PERCENT_MISR6);
        mResult.Misr7 = (HWBIST_95PERCENT_MISR7);
        mResult.Misr8 = (HWBIST_95PERCENT_MISR8);
        mResult.Misr9 = (HWBIST_95PERCENT_MISR9);
        mResult.Misr10 = (HWBIST_95PERCENT_MISR10);
        mResult.Misr11 = (HWBIST_95PERCENT_MISR11);
        mResult.Misr12 = (HWBIST_95PERCENT_MISR12);
        mResult.Misr13 = (HWBIST_95PERCENT_MISR13);
        mResult.Misr14 = (HWBIST_95PERCENT_MISR14);
        mResult.Misr15 = (HWBIST_95PERCENT_MISR15);
        break;
    case HWBIST_CONFIG_COV_99PERCENT:
        mResult.Misr0 = (HWBIST_99PERCENT_MISR0);
        mResult.Misr1 = (HWBIST_99PERCENT_MISR1);
        mResult.Misr2 = (HWBIST_99PERCENT_MISR2);
        mResult.Misr3 = (HWBIST_99PERCENT_MISR3);
        mResult.Misr4 = (HWBIST_99PERCENT_MISR4);
        mResult.Misr5 = (HWBIST_99PERCENT_MISR5);
        mResult.Misr6 = (HWBIST_99PERCENT_MISR6);
        mResult.Misr7 = (HWBIST_99PERCENT_MISR7);
        mResult.Misr8 = (HWBIST_99PERCENT_MISR8);
        mResult.Misr9 = (HWBIST_99PERCENT_MISR9);
        mResult.Misr10 = (HWBIST_99PERCENT_MISR10);
        mResult.Misr11 = (HWBIST_99PERCENT_MISR11);
        mResult.Misr12 = (HWBIST_99PERCENT_MISR12);
        mResult.Misr13 = (HWBIST_99PERCENT_MISR13);
        mResult.Misr14 = (HWBIST_99PERCENT_MISR14);
        mResult.Misr15 = (HWBIST_99PERCENT_MISR15);
        break;
 /*   case HWBIST_CONFIG_COV_95PERCENT_DEV:
            mResult.Misr0 = *(unsigned long*)(HWBIST_95PERCENT_MISR0);
            mResult.Misr1 = *(unsigned long*)(HWBIST_95PERCENT_MISR1);
            mResult.Misr2 = *(unsigned long*)(HWBIST_95PERCENT_MISR2);
            mResult.Misr3 = *(unsigned long*)(HWBIST_95PERCENT_MISR3);
            mResult.Misr4 = *(unsigned long*)(HWBIST_95PERCENT_MISR4);
            mResult.Misr5 = *(unsigned long*)(HWBIST_95PERCENT_MISR5);
            mResult.Misr6 = *(unsigned long*)(HWBIST_95PERCENT_MISR6);
            mResult.Misr7 = *(unsigned long*)(HWBIST_95PERCENT_MISR7);
            mResult.Misr8 = *(unsigned long*)(HWBIST_95PERCENT_MISR8);
            mResult.Misr9 = *(unsigned long*)(HWBIST_95PERCENT_MISR9);
            mResult.Misr10 = *(unsigned long*)(HWBIST_95PERCENT_MISR10);
            mResult.Misr11 = *(unsigned long*)(HWBIST_95PERCENT_MISR11);
            mResult.Misr12 = *(unsigned long*)(HWBIST_95PERCENT_MISR12);
            mResult.Misr13 = *(unsigned long*)(HWBIST_95PERCENT_MISR13);
            mResult.Misr14 = *(unsigned long*)(HWBIST_95PERCENT_MISR14);
            mResult.Misr15 = *(unsigned long*)(HWBIST_95PERCENT_MISR15);
            break;
        case HWBIST_CONFIG_COV_99PERCENT_DEV:
            mResult.Misr0 = *(unsigned long*)(HWBIST_99PERCENT_MISR0);
            mResult.Misr1 = *(unsigned long*)(HWBIST_99PERCENT_MISR1);
            mResult.Misr2 = *(unsigned long*)(HWBIST_99PERCENT_MISR2);
            mResult.Misr3 = *(unsigned long*)(HWBIST_99PERCENT_MISR3);
            mResult.Misr4 = *(unsigned long*)(HWBIST_99PERCENT_MISR4);
            mResult.Misr5 = *(unsigned long*)(HWBIST_99PERCENT_MISR5);
            mResult.Misr6 = *(unsigned long*)(HWBIST_99PERCENT_MISR6);
            mResult.Misr7 = *(unsigned long*)(HWBIST_99PERCENT_MISR7);
            mResult.Misr8 = *(unsigned long*)(HWBIST_99PERCENT_MISR8);
            mResult.Misr9 = *(unsigned long*)(HWBIST_99PERCENT_MISR9);
            mResult.Misr10 = *(unsigned long*)(HWBIST_99PERCENT_MISR10);
            mResult.Misr11 = *(unsigned long*)(HWBIST_99PERCENT_MISR11);
            mResult.Misr12 = *(unsigned long*)(HWBIST_99PERCENT_MISR12);
            mResult.Misr13 = *(unsigned long*)(HWBIST_99PERCENT_MISR13);
            mResult.Misr14 = *(unsigned long*)(HWBIST_99PERCENT_MISR14);
            mResult.Misr15 = *(unsigned long*)(HWBIST_99PERCENT_MISR15);
            break;*/
        default:
            // Unrecognized value
            mResult.Misr0 = 0;
            mResult.Misr1 = 0;
            mResult.Misr2 = 0;
            mResult.Misr3 = 0;
            mResult.Misr4 = 0;
            mResult.Misr5 = 0;
            mResult.Misr6 = 0;
            mResult.Misr7 = 0;
            mResult.Misr8 = 0;
            mResult.Misr9 = 0;
            mResult.Misr10 = 0;
            mResult.Misr11 = 0;
            mResult.Misr12 = 0;
            mResult.Misr13 = 0;
            mResult.Misr14 = 0;
            mResult.Misr15 = 0;
            break;
    }

    return(mResult);
}

//*****************************************************************************
//! Compares two MISR values for equality.
//!
//! \param m1 The first MISR value.
//! \param m2 The second MISR value.
//!
//! \return true if the MISR values match, false otherwise.
//*****************************************************************************
int HWBISTCompareMisr(tMisr m1, tMisr m2)
{
    if((m1.Misr0 == m2.Misr0) &&
       (m1.Misr1 == m2.Misr1) &&
       (m1.Misr2 == m2.Misr2) &&
       (m1.Misr3 == m2.Misr3) &&
       (m1.Misr4 == m2.Misr4) &&
       (m1.Misr5 == m2.Misr5) &&
       (m1.Misr6 == m2.Misr6) &&
       (m1.Misr7 == m2.Misr7) &&
       (m1.Misr8 == m2.Misr8) &&
       (m1.Misr9 == m2.Misr9) &&
       (m1.Misr10 == m2.Misr10) &&
       (m1.Misr11 == m2.Misr11) &&
       (m1.Misr12 == m2.Misr12) &&
       (m1.Misr13 == m2.Misr13) &&
       (m1.Misr14 == m2.Misr14) &&
       (m1.Misr15 == m2.Misr15))
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

void HWBISTSemEn(unsigned long ulCoreEn) {
	EALLOW;
	HwbistRegs.CSTCSEM.all = ulCoreEn;
	EDIS;
}


//*****************************************************************************
//
//! \internal
//! Block of NOPs.
//
//*****************************************************************************
#define NOP_SEQUENCE() \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");    \
    asm(" NOP");

//*****************************************************************************
// Close the Doxygen group.
//! @}
//*****************************************************************************
