//#############################################################################
// FILE: usbhandler.c
// TITLE: General USB handling routines
//#############################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//#############################################################################

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/usblibpriv.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdevicepriv.h"
#include "usblib/usblibpriv.h"

//*****************************************************************************
//
//! \addtogroup device_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The USB device interrupt handler.
//!
//! This the main USB interrupt handler entry point for use in USB device
//! applications.  This top-level handler will branch the interrupt off to the
//! appropriate application or stack handlers depending on the current status
//! of the USB controller.
//!
//! Applications which operate purely as USB devices (rather than dual mode
//! applications which can operate in either device or host mode at different
//! times) must ensure that a pointer to this function is installed in the
//! interrupt vector table entry for the USB0 interrupt.  For dual mode
//! operation, the vector should be set to point to \e USB0DualModeIntHandler()
//! instead.
//!
//! \return None.
//
//*****************************************************************************
void
USB0DeviceIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the controller interrupt status.
    //
    ui32Status = MAP_USBIntStatusControl(USB0_BASE);

    //
    // Call the internal handler.
    //
    USBDeviceIntHandlerInternal(0, ui32Status);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
