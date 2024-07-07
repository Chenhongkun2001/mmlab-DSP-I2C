//###########################################################################
//
// FILE:   sysctl.c
//
// TITLE:  Stellaris style wrapper driver for F2837x system control.
//
//###########################################################################
// $TI Release: 
// $Release Date: 
//###########################################################################

//*****************************************************************************
//
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

#include "F28x_Project.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \internal
//! Checks a peripheral identifier.
//!
//! \param ui32Peripheral is the peripheral identifier.
//!
//! This function determines if a peripheral identifier is valid.
//!
//! \return Returns \b true if the peripheral identifier is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static bool
_SysCtlPeripheralValid(uint32_t ui32Peripheral)
{
    return((ui32Peripheral == SYSCTL_PERIPH_CLA1) ||
           (ui32Peripheral == SYSCTL_PERIPH_DMA) ||
           (ui32Peripheral == SYSCTL_PERIPH_TIMER0) ||
           (ui32Peripheral == SYSCTL_PERIPH_TIMER1) ||
           (ui32Peripheral == SYSCTL_PERIPH_TIMER2) ||
           (ui32Peripheral == SYSCTL_PERIPH_HRPWM) ||
           (ui32Peripheral == SYSCTL_PERIPH_TBCLKSYNC) ||
           (ui32Peripheral == SYSCTL_PERIPH_GTBCLKSYNC) ||
           (ui32Peripheral == SYSCTL_PERIPH_EMIF1) ||
           (ui32Peripheral == SYSCTL_PERIPH_EMIF2) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM1) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM2) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM3) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM4) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM5) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM6) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM7) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM8) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM9) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM10) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM11) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM12) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP2) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP3) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP4) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP5) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP6) ||
           (ui32Peripheral == SYSCTL_PERIPH_EQEP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_EQEP2) ||
           (ui32Peripheral == SYSCTL_PERIPH_EQEP3) ||
           (ui32Peripheral == SYSCTL_PERIPH_SD1) ||
           (ui32Peripheral == SYSCTL_PERIPH_SD2) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI1) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI2) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI3) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI4) ||
           (ui32Peripheral == SYSCTL_PERIPH_SPI1) ||
           (ui32Peripheral == SYSCTL_PERIPH_SPI2) ||
           (ui32Peripheral == SYSCTL_PERIPH_SPI3) ||
           (ui32Peripheral == SYSCTL_PERIPH_I2C1) ||
           (ui32Peripheral == SYSCTL_PERIPH_I2C2) ||
           (ui32Peripheral == SYSCTL_PERIPH_CAN1) ||
           (ui32Peripheral == SYSCTL_PERIPH_CAN2) ||
           (ui32Peripheral == SYSCTL_PERIPH_MCBSP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_MCBSP2) ||
           (ui32Peripheral == SYSCTL_PERIPH_UPP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC1) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC2) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC3) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC4) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS1) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS2) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS3) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS4) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS5) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS6) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS7) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS8) ||
           (ui32Peripheral == SYSCTL_PERIPH_BUFFDAC1) ||
           (ui32Peripheral == SYSCTL_PERIPH_BUFFDAC2) ||
           (ui32Peripheral == SYSCTL_PERIPH_BUFFDAC3));
}
#endif



//*****************************************************************************
//
//! Determines if a peripheral is present.
//!
//! \param ui32Peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is present in the
//! device.  Each member of the family has a different peripheral
//! set; this function determines which peripherals are present on this device.
//!
//! \return Returns \b true if the specified peripheral is present and \b false
//! if it is not.
//
//*****************************************************************************
bool
SysCtlPeripheralPresent(uint32_t ui32Peripheral)
{

    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));


    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    if(HWREG(&(DevCfgRegs.DC0.all) + (2 * regIndex)) & (1 << bitIndex)){
        return true;
    }else{
        return false;
    }


}

//*****************************************************************************
//
//! Determines if a peripheral is ready.
//!
//! \param ui32Peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is ready to be
//! accessed.  The peripheral may be in a non-ready state if it is not enabled,
//! is being held in reset, or is in the process of becoming ready after being
//! enabled or taken out of reset.
//!
//! \note The ability to check for a peripheral being ready varies based on the
//! part in use.  Please consult the data sheet for the part you are
//! using to determine if this feature is available.
//!
//! \return Returns \b true if the specified peripheral is ready and \b false
//! if it is not.
//
//*****************************************************************************
bool
SysCtlPeripheralReady(uint32_t ui32Peripheral)
{

    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));


    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    // Is the peripheral there?
    if(HWREG((uint32_t)&(DevCfgRegs.DC0.all) + (2 * regIndex)) & ((uint32_t)1 << bitIndex)){
        // Is the peripheral enabled?
        if(HWREG((uint32_t)&(CpuSysRegs.PCLKCR0.all) + (2 * regIndex)) & ((uint32_t)1 << bitIndex)){
            // Is the peripheral in reset?
            if((HWREG((uint32_t)&(DevCfgRegs.SOFTPRES0.all) + (2 * regIndex)) & ((uint32_t)1 << bitIndex)) == 0){
                // No?  Ok cool
                return true;
            }
        }
    }else{
        return false;
    }

    return false;
}
//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param ui32Peripheral is the peripheral to reset.
//!
//! The f2837x devices do not have a means of resetting peripherals via
//! via software.  This is a dummy function that does nothing.
//!
//!
//! \return None.
//
//*****************************************************************************
void SysCtlPeripheralReset(uint32_t ui32Peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    EALLOW;

    HWREG((uint32_t)&(DevCfgRegs.SOFTPRES0.all) + (2 * regIndex)) |= ((uint32_t)1 << bitIndex);
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    HWREG((uint32_t)&(DevCfgRegs.SOFTPRES0.all) + (2 * regIndex)) &= ~((uint32_t)1 << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param ui32Peripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_UART_A, \b SYSCTL_PERIPH_UART_B, \b SYSCTL_PERIPH_UART_C,
//! \b SYSCTL_PERIPH_UART_D, \b SYSCTL_PERIPH_SPI_A, \b SYSCTL_PERIPH_SPI_B,
//! \b SYSCTL_PERIPH_SPI_C, \b SYSCTL_PERIPH_MCBSP_A, \b SYSCTL_PERIPH_MCBSP_B,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB_A
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(uint32_t ui32Peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;
    volatile uint32_t test1, test2, test3, test4;

    regIndex = (ui32Peripheral & SYSCTL_PERIPH_REG_M);
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    EALLOW;
    HWREG((uint32_t)&(CpuSysRegs.PCLKCR0.all) + (2 * regIndex)) |= ((uint32_t)1 << bitIndex);

    EDIS;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param ui32Peripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_UART_A, \b SYSCTL_PERIPH_UART_B, \b SYSCTL_PERIPH_UART_C,
//! \b SYSCTL_PERIPH_UART_D, \b SYSCTL_PERIPH_SPI_A, \b SYSCTL_PERIPH_SPI_B,
//! \b SYSCTL_PERIPH_SPI_C, \b SYSCTL_PERIPH_MCBSP_A, \b SYSCTL_PERIPH_MCBSP_B,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB_A
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(uint32_t ui32Peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    EALLOW;

    HWREG((uint32_t)&(CpuSysRegs.PCLKCR0.all) + (2 * regIndex)) &= ~((uint32_t)1 << bitIndex);

    EDIS;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a software reset of the entire device.  The
//! processor and all peripherals are reset and all device registers are
//! returned to their default values (with the exception of the reset cause
//! register, which maintains its current value but has the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlReset(void)
{
    //
    // Write an incorrect check value to the watchdog control register
    // This will cause a device reset
    //
    EALLOW;
    // Enable the watchdog
    HWREG(&(WdRegs.WDCR.all)) = 0x0028;
    // Write a bad check value
    HWREG(&(WdRegs.WDCR.all)) = 0xFFFF;
    EDIS;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
//! Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 5 cycles/loop + 9.
//!
//! \return None.
//
//*****************************************************************************
__asm(" .def _SysCtlDelay\n"
      " .sect \"ramfuncs\"\n"
      " .global  _SysCtlDelay\n"
      "_SysCtlDelay:\n"
      " SUB    ACC,#1\n"
      " BF     _SysCtlDelay,GEQ\n"
      " LRETR\n");


//*****************************************************************************
//
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock.
//!
//! \note Because of the many different clocking options available, this
//!  function cannot determine the clock speed of the processor.  This function
//!  should be modified to return the actual clock speed of the processor in
//!  your specific application.
//!
//! \return The processor clock rate.
//
//*****************************************************************************
uint32_t
SysCtlClockGet(uint32_t u32ClockIn)
{

    if((ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 0) ||
            (ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 2)){
        //10MHz Internal Clock
        u32ClockIn = 10000000;
    }

    //If the pll is enabled calculate its effect on the clock
//    if((HWREG(SYSCTL_SYSPLLCTL) &
//        (SYSCTL_SYSPLLCTL_SPLLEN | SYSCTL_SYSPLLCTL_SPLLCLKEN)) == 3)
    if(ClkCfgRegs.SYSPLLCTL1.bit.PLLEN && ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN)
    {
        //Calculate integer multiplier and fixed divide by 2
//        ulClockIn = ulClockIn *
//                    (HWREG(SYSCTL_SYSPLLMULT) & SYSCTL_SYSPLLMULT_SPLLIMULT_M);
        u32ClockIn = u32ClockIn * ClkCfgRegs.SYSPLLMULT.bit.IMULT;


        //Calculate fractional multiplier
//        switch((HWREG(SYSCTL_SYSPLLMULT) & SYSCTL_SYSPLLMULT_SPLLFMULT_M) >>
//                SYSCTL_SYSPLLMULT_SPLLFMULT_S)
        switch(ClkCfgRegs.SYSPLLMULT.bit.IMULT)
        {
        default:
        case 0:
            break;

        case 1:
            u32ClockIn += u32ClockIn / 4;
            break;

        case 2:
            u32ClockIn += u32ClockIn / 2;
            break;

        case 3:
            u32ClockIn += (u32ClockIn * 3) / 4;
            break;
        }
    }

    if(ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV != 0){
        u32ClockIn /= (2 * ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV);
    }

    return u32ClockIn;

}

//*****************************************************************************
//
//! Gets the low speed peripheral clock rate.
//!
//! This function determines the clock rate of the low speed peripherals.
//!
//! \note Because of the many different clocking options available, this
//!  function cannot determine the clock speed of the processor.  This function
//!  should be modified to return the actual clock speed of the processor in
//!  your specific application.
//!
//! \return The low speed peripheral clock rate.
//
//*****************************************************************************
uint32_t
SysCtlLowSpeedClockGet(uint32_t u32ClockIn)
{

    // Get the main system clock
    u32ClockIn = SysCtlClockGet(u32ClockIn);

    // Apply the divider to the main clock
    if(ClkCfgRegs.LOSPCP.bit.LSPCLKDIV != 0){
        u32ClockIn /= (2 * ClkCfgRegs.LOSPCP.bit.LSPCLKDIV);
    }

    return u32ClockIn;

}

//*****************************************************************************
//
//! Sets the clocking of the device.
//!
//! \param ui32Config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e ui32Config parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The system clock divider is chosen with one of the following values:
//! \b SYSCTL_SYSDIV_1, \b SYSCTL_SYSDIV_2, \b SYSCTL_SYSDIV_3, ...
//! \b SYSCTL_SYSDIV_64.
//!
//! The use of the PLL is chosen with either \b SYSCTL_USE_PLL or
//! \b SYSCTL_USE_OSC.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \b SYSCTL_XTAL_4MHZ, \b SYSCTL_XTAL_4_09MHZ, \b SYSCTL_XTAL_4_91MHZ,
//! \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_5_12MHZ, \b SYSCTL_XTAL_6MHZ,
//! \b SYSCTL_XTAL_6_14MHZ, \b SYSCTL_XTAL_7_37MHZ, \b SYSCTL_XTAL_8MHZ,
//! \b SYSCTL_XTAL_8_19MHZ, \b SYSCTL_XTAL_10MHZ, \b SYSCTL_XTAL_12MHZ,
//! \b SYSCTL_XTAL_12_2MHZ, \b SYSCTL_XTAL_13_5MHZ, \b SYSCTL_XTAL_14_3MHZ,
//! \b SYSCTL_XTAL_16MHZ, \b SYSCTL_XTAL_16_3MHZ, \b SYSCTL_XTAL_18MHZ,
//! \b SYSCTL_XTAL_20MHZ, \b SYSCTL_XTAL_24MHZ, or \b SYSCTL_XTAL_25MHz.
//! Values below \b SYSCTL_XTAL_5MHZ are not valid when the PLL is in
//! operation.
//!
//! The oscillator source is chosen with one of the following values:
//! \b SYSCTL_OSC_MAIN, \b SYSCTL_OSC_INT, \b SYSCTL_OSC_INT4,
//! \b SYSCTL_OSC_INT30, or \b SYSCTL_OSC_EXT32.  \b SYSCTL_OSC_EXT32 is only
//! available on devices with the hibernate module, and then only when the
//! hibernate module has been enabled.
//!
//! The internal and main oscillators are disabled with the
//! \b SYSCTL_INT_OSC_DIS and \b SYSCTL_MAIN_OSC_DIS flags, respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device is prevented by the hardware.
//!
//! To clock the system from an external source (such as an external crystal
//! oscillator), use \b SYSCTL_USE_OSC \b | \b SYSCTL_OSC_MAIN.  To clock the
//! system from the main oscillator, use \b SYSCTL_USE_OSC \b |
//! \b SYSCTL_OSC_MAIN.  To clock the system from the PLL, use
//! \b SYSCTL_USE_PLL \b | \b SYSCTL_OSC_MAIN, and select the appropriate
//! crystal with one of the \b SYSCTL_XTAL_xxx values.
//!
//! \note If selecting the PLL as the system clock source (that is, via
//! \b SYSCTL_USE_PLL), this function polls the PLL lock interrupt to
//! determine when the PLL has locked.  If an interrupt handler for the
//! system control interrupt is in place, and it responds to and clears the
//! PLL lock interrupt, this function delays until its timeout has occurred
//! instead of completing as soon as PLL lock is achieved.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClockSet(uint32_t ui32Config)
{
    uint16_t ui16TempDivsel;

    //Bypass PLL
    // Make sure the PLL is not running in limp mode
    if (ClkCfgRegs.MCDCR.bit.MCLKSTS != 0)
    {
       EALLOW;
       // OSCCLKSRC2 failure detected. PLL running in limp mode.
       // Re-enable missing clock logic.
       ClkCfgRegs.MCDCR.bit.MCLKCLR = 1;
       EDIS;
       // Replace this line with a call to an appropriate
       // SystemShutdown(); function.
      __asm("        ESTOP0");     // Uncomment for debugging purposes
    }

    //Ensure teh PLL is out of our clock tree
    EALLOW;
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
    ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
    EDIS;


    //Configure Oscillator
    EALLOW;
    switch (ui32Config & SYSCTL_OSCSRC_M)
    {
        default:
        case SYSCTL_OSCSRC_OSC2:
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;     // Turn on INTOSC2
            ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // Clk Src = INTOSC2
//          ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=1;        // Turn off XTALOSC
            break;

        case SYSCTL_OSCSRC_XTAL:
            ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=0;        // Turn on XTALOSC
            ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // Clk Src = XTAL
//          ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=1;     // Turn off INTOSC2
            break;

        case SYSCTL_OSCSRC_OSC1:
            ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // Clk Src = INTOSC1
//          ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=1;        // Turn off XTALOSC
//          ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=1;     // Turn off INTOSC2
            break;

    }
    EDIS;

    //Configure PLL if enabled
    if(ui32Config & SYSCTL_PLL_ENABLE)
        EALLOW;
        //modify dividers to maximum to reduce the inrush current
        ClkCfgRegs.SYSPLLMULT.bit.IMULT = (ui32Config & SYSCTL_IMULT_M) >> SYSCTL_IMULT_S;      //Setting integer multiplier
        ClkCfgRegs.SYSPLLMULT.bit.FMULT = (ui32Config & SYSCTL_FMULT_M) >> SYSCTL_FMULT_S;      //Setting fractional multiplier
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;                    //Enable SYSPLL
        EDIS;

        //Wait for the SYSPLL lock
        while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1)
        {
            // Uncomment to service the watchdog
            // ServiceDog();
        }

    //Configure Dividers
    //increase the freq. of operation in steps to avoid any VDD fluctuations
    ui16TempDivsel = 126/2;
    while(ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV != ((ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S))
    {
        EALLOW;
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = ui16TempDivsel;
        EDIS;
        ui16TempDivsel -= 1;
        if(ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV != ((ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S))
        {
            SysCtlDelay(15);
        }
    }

    //Enable PLLSYSCLK is fed from system PLL clock
    EALLOW;
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;
    EDIS;
}

//*****************************************************************************
//
//! Sets the clocking of the device.
//!
//! \param ui32Config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e ui32Config parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The system clock divider is chosen with one of the following values:
//! \b SYSCTL_SYSDIV_1, \b SYSCTL_SYSDIV_2, \b SYSCTL_SYSDIV_3, ...
//! \b SYSCTL_SYSDIV_64.
//!
//! The use of the PLL is chosen with either \b SYSCTL_USE_PLL or
//! \b SYSCTL_USE_OSC.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \b SYSCTL_XTAL_4MHZ, \b SYSCTL_XTAL_4_09MHZ, \b SYSCTL_XTAL_4_91MHZ,
//! \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_5_12MHZ, \b SYSCTL_XTAL_6MHZ,
//! \b SYSCTL_XTAL_6_14MHZ, \b SYSCTL_XTAL_7_37MHZ, \b SYSCTL_XTAL_8MHZ,
//! \b SYSCTL_XTAL_8_19MHZ, \b SYSCTL_XTAL_10MHZ, \b SYSCTL_XTAL_12MHZ,
//! \b SYSCTL_XTAL_12_2MHZ, \b SYSCTL_XTAL_13_5MHZ, \b SYSCTL_XTAL_14_3MHZ,
//! \b SYSCTL_XTAL_16MHZ, \b SYSCTL_XTAL_16_3MHZ, \b SYSCTL_XTAL_18MHZ,
//! \b SYSCTL_XTAL_20MHZ, \b SYSCTL_XTAL_24MHZ, or \b SYSCTL_XTAL_25MHz.
//! Values below \b SYSCTL_XTAL_5MHZ are not valid when the PLL is in
//! operation.
//!
//! The oscillator source is chosen with one of the following values:
//! \b SYSCTL_OSC_MAIN, \b SYSCTL_OSC_INT, \b SYSCTL_OSC_INT4,
//! \b SYSCTL_OSC_INT30, or \b SYSCTL_OSC_EXT32.  \b SYSCTL_OSC_EXT32 is only
//! available on devices with the hibernate module, and then only when the
//! hibernate module has been enabled.
//!
//! The internal and main oscillators are disabled with the
//! \b SYSCTL_INT_OSC_DIS and \b SYSCTL_MAIN_OSC_DIS flags, respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device is prevented by the hardware.
//!
//! To clock the system from an external source (such as an external crystal
//! oscillator), use \b SYSCTL_USE_OSC \b | \b SYSCTL_OSC_MAIN.  To clock the
//! system from the main oscillator, use \b SYSCTL_USE_OSC \b |
//! \b SYSCTL_OSC_MAIN.  To clock the system from the PLL, use
//! \b SYSCTL_USE_PLL \b | \b SYSCTL_OSC_MAIN, and select the appropriate
//! crystal with one of the \b SYSCTL_XTAL_xxx values.
//!
//! \note If selecting the PLL as the system clock source (that is, via
//! \b SYSCTL_USE_PLL), this function polls the PLL lock interrupt to
//! determine when the PLL has locked.  If an interrupt handler for the
//! system control interrupt is in place, and it responds to and clears the
//! PLL lock interrupt, this function delays until its timeout has occurred
//! instead of completing as soon as PLL lock is achieved.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlAuxClockSet(uint32_t ui32Config)
{
    uint16_t ui16TempDivsel;

    //Bypass PLL
    //Ensure teh PLL is out of our clock tree
    EALLOW;
    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 0;
    ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 0;
    EDIS;


    //Configure Oscillator
    EALLOW;
    switch (ui32Config & SYSCTL_OSCSRC_M)
    {
        default:
        case SYSCTL_OSCSRC_OSC2:
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;     // Turn on INTOSC2
            ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 0; // Clk Src = INTOSC2
            break;

        case SYSCTL_OSCSRC_XTAL:
            ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=0;        // Turn on XTALOSC
            ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 1; // Clk Src = XTAL
            break;

        case SYSCTL_OSCSRC_OSC1:
            ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 2; // Clk Src = INTOSC1
            break;

    }
    EDIS;

    //Configure PLL if enabled
    if(ui32Config & SYSCTL_PLL_ENABLE)
    {
        EALLOW;
        //modify dividers to maximum to reduce the inrush current
        ClkCfgRegs.AUXPLLMULT.bit.IMULT = (ui32Config & SYSCTL_IMULT_M) >> SYSCTL_IMULT_S;      //Setting integer multiplier
        ClkCfgRegs.AUXPLLMULT.bit.FMULT = (ui32Config & SYSCTL_FMULT_M) >> SYSCTL_FMULT_S;      //Setting fractional multiplier
        ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 1;                    //Enable SYSPLL
        EDIS;

        //Wait for the SYSPLL lock
        while(ClkCfgRegs.AUXPLLSTS.bit.LOCKS != 1)
        {
            // Uncomment to service the watchdog
            // ServiceDog();
        }
    }

    //Configure Dividers
    //increase the freq. of operation in steps to avoid any VDD fluctuations
    ui16TempDivsel = 3;
    while(ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV != ((ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S))
    {
        EALLOW;
        ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV = ui16TempDivsel;
        EDIS;
        ui16TempDivsel -= 1;
        if(ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV != ((ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S))
        {
            SysCtlDelay(15);
        }
    }

    //Enable PLLSYSCLK is fed from system PLL clock
    EALLOW;
    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 1;
    EDIS;
}

//*****************************************************************************
//
//! Powers up the USB PLL.
//!
//! This function will enable the USB controller's PLL.
//!
//! \note Because every application is different, the user will likely have to
//! modify this function to ensure the PLL multiplier is set correctly to
//! achieve the 60 MHz required by the USB controller.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlUSBPLLEnable(void)
{
//    // Turn on INTOSC2
//    ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;
//    //Select INTOSC2 as USB PLL Clk In
//    ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 0;
//    // Set Aux PLL divider
//    ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV = 1;
//    // Set Aux PLL multiplier
//    ClkCfgRegs.AUXPLLMULT.bit.IMULT = 12;
//    // Set Aux PLL fractional multiplier to 0.0
//  ClkCfgRegs.AUXPLLMULT.bit.FMULT = 0;
//    //Enable AUXPLL
//  ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 1;
//
//    //Wait for the AUXPLL lock
//  while(ClkCfgRegs.AUXPLLSTS.bit.LOCKS != 1)
//  {
//      // Uncomment to service the watchdog
//      // ServiceDog();
//  }
//    // AUXPLLCLK is fed from the AUXPLL
//  ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 1;

}

//*****************************************************************************
//
//! Powers down the USB PLL.
//!
//! This function will disable the USB controller's PLL.  The USB registers
//! are still accessible, but the physical layer will no longer function.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlUSBPLLDisable(void)
{
    //Disable the PLL
//    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


