//###########################################################################
//
// FILE:   F2837xD_Upp_defines.h
//
// TITLE:  #defines used in Upp examples
//
//###########################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $
//###########################################################################

#ifndef F2837xD_UPP_DEFINES_H
#define F2837xD_UPP_DEFINES_H


#ifdef __cplusplus
extern "C" {
#endif


#define uPP_TX_MSGRAM_ADDR 0x6C00
#define uPP_TX_MSGRAM_SIZE 512

#define uPP_RX_MSGRAM_ADDR 0x6E00
#define uPP_RX_MSGRAM_SIZE 512

#define uPP_RX_MODE 0
#define uPP_TX_MODE 1

#define uPP_SDR 0
#define uPP_DDR 1

#define uPP_TX_SIZE_64B 0
#define uPP_TX_SIZE_128B 1
#define uPP_TX_SIZE_256B 3

#define uPP_RX_SIZE_64B 0
#define uPP_RX_SIZE_128B 1
#define uPP_RX_SIZE_256B 3

#define uPP_INT_EOWI 0x8
#define uPP_INT_EOLI 0x10
#define uPP_INT_EOWQ 0x800
#define uPP_INT_EOLQ 0x1000

//Write Mask to stop writing to control critical bit 
//None


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837xD_EMIF_DEFINES_H

//===========================================================================
// End of file.
//===========================================================================
