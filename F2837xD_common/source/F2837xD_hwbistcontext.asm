
    .cdecls C,LIST,"F2837xD_Device.h"               ; Device Headers

    ; C-Callable function defs
    .def _HWBISTASMSelfTestRun
    .def _HWBISTASMResetHandler

    ; RAM section globals
    .global  __biststack                            ; HWBIST Stack (used during BIST context restore/save)

    ; RAM section (stack addresses filled in by the linker)
__biststack:    .usect  ".ebss", 80             ; Reserve 80 words (160 bytes) for stack

    ; Code section
    .sect ".text"

    ; C-Callable function globals
    .global  __HWBISTASMSelfTestRun
    .global  __HWBISTASMResetHandler

    ; BIST reset handler
    ; This is the entry point that is called by BootROM after a BIST reset
    ; This function is NOT C-Callable and does NOT return anywhere
    ; After this function is called, the processor context is restored
    ; (the PC is set to retpcloc: in _HWBISTASMSelfTestRun)
_HWBISTASMResetHandler:

    MOVW    DP, #0                              ; Set DP so we can access @SP

    ; 14 NOPs
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

infloop:
    SB  infloop, UNC

    ; BEGIN ContextRestore
    MOV     SP, #(__biststack + 0x4C)               ; Move SP last BIST stack store location
    POP     RPC										; Start Restoring in reverse order
    POP     DP:ST1
    POP     T:ST0
    POP     XAR7
    POP     XAR6
    POP     XAR5
    POP     XAR4
    POP     XAR3
    POP     XAR2
    POP     XAR1
    POP     XAR0
    POP     P
    POP     ACC                                     ; Remember: AH = ST1, AL = ST0 from user context
    POP     XT
    POP     IER
    POP     RB										; Restore FPU Registers
    MOV32   STF,*--SP
    MOV32   R7H,*--SP
    MOV32   R6H,*--SP
    MOV32   R5H,*--SP
    MOV32   R4H,*--SP
    MOV32   R3H,*--SP
    MOV32   R2H,*--SP
    MOV32   R1H,*--SP
    MOV32   R0H,*--SP
    VMOV32   VR0,*--SP								; Restore VCU Registers
    VMOV32   VR1,*--SP
    VMOV32   VR2,*--SP
    VMOV32   VR3,*--SP
    VMOV32   VR4,*--SP
    VMOV32   VR5,*--SP
    VMOV32   VR6,*--SP
    VMOV32   VR7,*--SP
    VMOV32   VR8,*--SP
    VMOV32   VT0,*--SP
    VMOV32   VT1,*--SP
    VMOV32   VSTATUS,*--SP
    VMOV32   VCRC,*--SP
    MOV     SP, #(__biststack + 0x4E)				; Move SP to end of BIST Stack to restore XAR7
    POP     XAR7                                    ; Get return PC into XAR7
    MOV     @SP, *(0:__biststack)                   ; Restore user SP
    ; END ContextRestore

    EALLOW

    MOVW    DP, #_CpuSysRegs
    MOV     @_CpuSysRegs.RESC.all, #0x00000000           ; Reset HW BIST reset source bits
    MOVW    DP, #_HwbistRegs
    MOV     @_HwbistRegs.CSTCCRD.all, #0x0000000A          ; Context restore done, re-issue logged interrupts

    ; 14 NOPs
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

    LB      *XAR7                                   ; Restore PC (this will branch back to retpcloc: in _HWBISTASMSelfTestRun)


    ; C-Callable function that starts the self test run
    ; This function will be eventually return to user code after the BIST reset cycle
    ; It may also return if BISTDISABLE = 0xA
_HWBISTASMSelfTestRun:
    PUSH    ACC                                     ; Explicitly save modified regs on user stack because they are modified in this function
    PUSH    XAR7                                    ; While this is saved by the calling function in the normal convention, we are
                                                    ; explicitly saving it just in case someone wants to call this from ASM

    PUSH    ST1                                     ; Save the user's ST1 register (preserves EALLOW, INTM, and other cpu status bits)
    POP     AH                                      ; AH = ST1

    PUSH    ST0                                     ; Save the user's ST0 register
    POP     AL                                      ; AL = ST0

    EALLOW

    MOVW    DP, #_HwbistRegs
 ;   MOV     @_HwbistRegs.CSTCGCR3.all, #0x0000000A         ; Start logging interrupts
    MOV     @0x5E00C, #0x0000000A         ; Start logging interrupts

    NOP                                             ; Pipeline flush (9 NOPs)
    NOP                                             ; These NOPs MUST be located here in order to gaurantee
    NOP                                             ; that pending interrupts in the IFR register are serviced
    NOP                                             ; before moving onto the context save (which cannot be interrupted)
    NOP
    NOP
    NOP
    NOP
    NOP

    ; TEST TEST TEST
    ;MOVW    DP, #_NmiIntruptRegs
    ;MOV     @_NmiIntruptRegs.NMIFLGFRC, #0x2        ; force clock fail

    EDIS

    ; The following disables are not needed because the interrupt logger
    ; disconnects the interrupt lines from the core
    ;DINT                                            ; Disable Interrupts
    ;SETC    DBGM                                    ; Disable DBGM realtime interrupts

    MOVW    DP, #0                                  ; For @SP accesses
    ; BEGIN ContextSave Routine                     ; StackLoc  Comment
    MOV     *(0:__biststack), @SP                   ; (0)       Save user SP to top of stack
    MOV     SP, #(__biststack + 2)                  ;           Load SP with next BIST stack location
    VMOV32   *SP++,VCRC								; Save VCU Registers
    VMOV32   *SP++,VSTATUS							; Save VCU Registers
    VMOV32   *SP++,VT1								; Save VCU Registers
    VMOV32   *SP++,VT0								; Save VCU Registers
    VMOV32   *SP++,VR8								; Save VCU Registers
    VMOV32   *SP++,VR7								; Save VCU Registers
    VMOV32   *SP++,VR6								; Save VCU Registers
    VMOV32   *SP++,VR5								; Save VCU Registers
    VMOV32   *SP++,VR4								; Save VCU Registers
    VMOV32   *SP++,VR3								; Save VCU Registers
    VMOV32   *SP++,VR2								; Save VCU Registers
    VMOV32   *SP++,VR1								; Save VCU Registers
    VMOV32   *SP++,VR0								; Save VCU Registers
    MOV32   *SP++,R0H								; Save FPU Registers
    MOV32   *SP++,R1H								; Save FPU Registers
    MOV32   *SP++,R2H								; Save FPU Registers
    MOV32   *SP++,R3H								; Save FPU Registers
    MOV32   *SP++,R4H								; Save FPU Registers
    MOV32   *SP++,R5H								; Save FPU Registers
    MOV32   *SP++,R6H								; Save FPU Registers
    MOV32   *SP++,R7H								; Save FPU Registers
    MOV32   *SP++,STF								; Save FPU Registers
    PUSH    RB								        ; Save FPU Registers
    PUSH    IER                                     ; (1)
    PUSH    XT                                      ; (2:3)
    PUSH    ACC                                     ; (4:5)     Remember: AH = ST1, AL = ST0 from user context
    PUSH    P                                       ; (6:7)
    PUSH    XAR0                                    ; (8:9)
    PUSH    XAR1                                    ; (A:B)
    PUSH    XAR2                                    ; (C:D)
    PUSH    XAR3                                    ; (E:F)
    PUSH    XAR4                                    ; (10:11)
    PUSH    XAR5                                    ; (12:13)
    PUSH    XAR6                                    ; (14:15)
    PUSH    XAR7                                    ; (16:17)
    PUSH    T:ST0                                   ; (18:19)
    PUSH    DP:ST1                                  ; (1A:1B)
    PUSH    RPC                                     ; (1C:1D)


curpcloc:
    MOV     XAR7, PC                                ;
    ADD     AR7, #(retpcloc - curpcloc)             ;           Add PC return offset (instruction after BIST_GO)
    PUSH    XAR7                                    ; (1E:1F)   Push PC
    ; END ContextSave Routine

    EALLOW

    NOP                                             ; Pipeline flush (9 NOPs)
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

    MOVW    DP, #_HwbistRegs
    MOV     @_HwbistRegs.CSTCGCR4.all, #0x0000000A          ; Start BIST Self Test (BIST_GO)

   ; LB      _HWBISTASMResetHandler                  ; For testing infinite context save / restore in a loop

    NOP                                             ; Pipeline flush (9 NOPs)
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bistdisabledloop:
    SB      bistdisabledloop, UNC                   ; Infinite loop that runs if BIST is disabled
                                                    ; Normally this loop would be skipped by the context save / restore
                                                    ; if BIST actually triggers a reset.

retpcloc:
    ; This is the return point from the BIST ResetHandler routine
    ; AH = ST1 (the user's ST1 from before the BIST_GO was triggered)
    ; ST1 must be restored now to return the EALLOW, INTM, DBGM state back to original status

    PUSH    AL                                      ; Restore user's ST0
    POP     ST0                                     ; ST0 = AL

    PUSH    AH                                      ; Restore user's ST1
    POP     ST1                                     ; ST1 = AH (at this point, INTM and DBGM will be restored to original state)

    POP     XAR7                                    ; Restore regs from user stack
    POP     ACC
    LRETR
