//###########################################################################
//
// FILE:   systick.h
//
// TITLE:  Stellaris style wrapper driver for C28x CPU Timer 0.
//
//###########################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//###########################################################################

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
    extern void SysTickInit(void);
    extern void SysTickEnable(void);
    extern void SysTickDisable(void);
    extern void SysTickIntRegister(void (*pfnHandler)(void));
    extern void SysTickIntUnregister(void);
    extern void SysTickIntEnable(void);
    extern void SysTickIntDisable(void);
    extern void SysTickPeriodSet(unsigned long ulPeriod);
    extern unsigned long SysTickPeriodGet(void);
    extern unsigned long SysTickValueGet(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SYSTICK_H__



