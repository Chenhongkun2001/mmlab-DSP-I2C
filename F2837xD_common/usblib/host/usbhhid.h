//#############################################################################
// FILE: usbhhid.h
// TITLE: This hold the host driver for hid class
//#############################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//#############################################################################

#ifndef __USBHHID_H__
#define __USBHHID_H__

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
//! \addtogroup usblib_host_class
//! @{
//
//*****************************************************************************

typedef struct tHIDInstance tHIDInstance;

//*****************************************************************************
//
// These defines are the the events that will be passed in the ui32Event
// parameter of the callback from the driver.
//
//*****************************************************************************
#define USBH_EVENT_HID_SETRPT   USBH_HID_EVENT_BASE + 0
#define USBH_EVENT_HID_REPORT   USBH_HID_EVENT_BASE + 1

//
//! The HID keyboard detected a key being pressed.
//
#define USBH_EVENT_HID_KB_PRESS USBH_HID_EVENT_BASE + 16

//
//! The HID keyboard detected a key being released.
//
#define USBH_EVENT_HID_KB_REL   USBH_HID_EVENT_BASE + 17

//
//! The HID keyboard detected one of the keyboard modifiers being pressed.
//
#define USBH_EVENT_HID_KB_MOD   USBH_HID_EVENT_BASE + 18

//
//! A button was pressed on a HID mouse.
//
#define USBH_EVENT_HID_MS_PRESS USBH_HID_EVENT_BASE + 32

//
//! A button was released on a HID mouse.
//
#define USBH_EVENT_HID_MS_REL   USBH_HID_EVENT_BASE + 33

//
//! The HID mouse detected movement in the X direction.
//
#define USBH_EVENT_HID_MS_X     USBH_HID_EVENT_BASE + 34

//
//! The HID mouse detected movement in the Y direction.
//
#define USBH_EVENT_HID_MS_Y     USBH_HID_EVENT_BASE + 35

//*****************************************************************************
//
//! The following values are used to register callbacks to the USB HOST HID
//! device class layer.
//
//*****************************************************************************
typedef enum
{
    //
    //! No device should be used.  This value should not be used by
    //! applications.
    //
    eUSBHHIDClassNone = 0,

    //
    //! This is a keyboard device.
    //
    eUSBHHIDClassKeyboard,

    //
    //! This is a mouse device.
    //
    eUSBHHIDClassMouse,

    //
    //! This is a vendor specific device.
    //
    eUSBHHIDClassVendor
}
tHIDSubClassProtocol;

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Prototypes.
//
//*****************************************************************************
extern tHIDInstance * USBHHIDOpen(tHIDSubClassProtocol iDeviceType,
                                  tUSBCallback pfnCallback,
                                  void *pvCBData);
extern void USBHHIDClose(tHIDInstance *psHIDInstance);
extern uint32_t USBHHIDGetReportDescriptor(tHIDInstance *psHIDInstance,
                                           uint8_t *pui8Buffer,
                                           uint32_t ui32Size);
extern uint32_t USBHHIDSetIdle(tHIDInstance *psHIDInstance, uint8_t ui8Duration,
                               uint8_t ui8ReportID);
extern uint32_t USBHHIDSetProtocol(tHIDInstance *psHIDInstance,
                                   uint32_t ui32BootProtocol);
extern uint32_t USBHHIDSetReport(tHIDInstance *psHIDInstance,
                                 uint32_t ui32Interface, uint8_t *pui8Data,
                                 uint32_t ui32Size);
extern uint32_t USBHHIDGetReport(tHIDInstance *psHIDInstance,
                                 uint32_t ui32Interface, uint8_t *pui8Data,
                                 uint32_t ui32Size);

extern const tUSBHostClassDriver g_sUSBHIDClassDriver;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBHHID_H__
