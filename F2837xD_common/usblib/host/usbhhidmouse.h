//#############################################################################
// FILE: usbhhidmouse.h
// TITLE: This file holds the application interfaces for USB
//#############################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//#############################################################################

#ifndef __USBHHIDMOUSE_H__
#define __USBHHIDMOUSE_H__

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
//! \addtogroup usblib_host_device
//! @{
//
//*****************************************************************************

typedef struct tUSBHMouse tUSBHMouse;

//*****************************************************************************
//
// The prototype for the host USB mouse driver callback function.
//
//*****************************************************************************
typedef void (*tUSBHIDMouseCallback)(tUSBHMouse *psMsInstance,
                                     uint32_t ui32Event,
                                     uint32_t ui32MsgParam,
                                     void *pvMsgData);

extern tUSBHMouse * USBHMouseOpen(tUSBHIDMouseCallback pfnCallback,
                                  uint8_t *pui8Buffer, uint32_t ui32Size);
extern uint32_t USBHMouseClose(tUSBHMouse *psMsInstance);
extern uint32_t USBHMouseInit(tUSBHMouse *psMsInstance);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
