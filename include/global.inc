; GLOBAL DEFINITIONS

NULL equ 0

REG_BASE equ 2000h

SYS_CTRL1 equ 00h
SYS_CTRL2 equ 01h
SYS_CTRL3 equ 02h

TMR1_SCALE equ 18h
TMR1_OSC equ 19h

IRQ_PRI1 equ 20h
IRQ_PRI2 equ 21h
IRQ_PRI3 equ 22h

IRQ_ENA1 equ 23h
IRQ_ENA2 equ 24h
IRQ_ENA3 equ 25h
IRQ_ENA4 equ 26h

IRQ_ACT1 equ 27h
IRQ_ACT2 equ 28h
IRQ_ACT3 equ 29h
IRQ_ACT4 equ 2Ah

TMR1_CTRL_L equ 30h
TMR1_CTRL_H equ 31h

KEY_PAD equ 52h

IO_DIR equ 60h
IO_DATA equ 61h

PRC_MODE equ 80h
PRC_RATE equ 81h

PRC_MAP_LO equ 82h
PRC_MAP_MID equ 83h
PRC_MAP_HI equ 84h

PRC_SCROLL_Y equ 85h
PRC_SCROLL_X equ 86h

PRC_SPR_LO equ 87h
PRC_SPR_MID equ 88h
PRC_SPR_HI equ 89h

PRC_CNT equ 8Ah

; System status flags

SC_Z EQU 1
SC_C EQU 2
SC_V EQU 4
SC_N EQU 8
SC_D EQU 16
SC_U EQU 32
SC_I0 EQU 64
SC_I1 EQU 128

OFF_Z EQU 0FFh^1
OFF_C EQU 0FFh^2
OFF_V EQU 0FFh^4
OFF_N EQU 0FFh^8
OFF_D EQU 0FFh^16
OFF_U EQU 0FFh^32
OFF_I0 EQU 0FFh^64
OFF_I1 EQU 0FFh^128

; Hardware Register Flags

PRC_MODE_INVERT equ 0h
PRC_MODE_COPY equ 8h

; Key flags

KEY_A EQU 1
KEY_B EQU 2
KEY_C EQU 4
KEY_UP EQU 8
KEY_DOWN EQU 16
KEY_LEFT EQU 32
KEY_RIGHT EQU 64
KEY_POWER EQU 128

; IO flags

IR_RX EQU 1
IR_TX EQU 2
EEPROM_DATA EQU 4
EEPROM_CLK EQU 8
RUMBLE EQU 16
IR_DIS EQU 32
PULLUP EQU 64
IR_TX_2 EQU 128

; Macros

assert MACRO condition
    IF condition == 0
        FAIL 'ASSERTION FAILED'
    ENDIF
ENDM

farcall MACRO function
    LD NB, #@CPAG(function)
    CARL function
ENDM

farjump MACRO line
    LD NB, #@CPAG(line)
    JRL line
ENDM

farload MACRO reg, address
    IF @SCP("reg", 'CODE') || @SCP("reg", 'code')
        LD HL, #@COFF(address)
        LD B, #@CPAG(address)
    ELSE
        IF @SCP("reg",'HL') || @SCP("reg",'hl')
            LD HL, #@DOFF(address)
            LD EP, #@DPAG(address)
        ELSE
            LD I\reg, #@DOFF(address)
            LD reg\P, #@DPAG(address)
        ENDIF
    ENDIF
ENDM

bgstruct MACRO _166b, prc_rate, _162b,          \
               tilemap0, tilemap1, pet0, pet1,  \
               _proc0, _proc1, _proc2, _proc3,  \
               _1647, _1648, bgm, _func, _addr, \
               _2cc2, _unk
    DB _166b, prc_rate, _162b
    DW @DOFF(tilemap0)
    DB @DPAG(tilemap0)
    DW @DOFF(tilemap1)
    DB @DPAG(tilemap1)
    DW @DOFF(pet0)
    DB @DPAG(pet0)
    DW @DOFF(pet1)
    DB @DPAG(pet1)
    DW @COFF(_proc0)
    DB @CPAG(_proc0)
    DW @COFF(_proc1)
    DB @CPAG(_proc1)
    DW @COFF(_proc2)
    DB @CPAG(_proc2)
    DW @COFF(_proc3)
    DB @CPAG(_proc3)
    DB _1647, _1648, bgm
    DW @COFF(_func)
    DB @CPAG(_func)
    DW @DOFF(_addr)
    DB @DPAG(_addr)
    DB _2cc2
    DB _unk
ENDM
