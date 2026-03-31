/*
                  Linker File for Renesas RZ/T2 FSP
*/

INCLUDE memory_regions.ld

/* The memory information for each device is done in memory regions file.
 * The starting address and length of memory not defined in memory regions file are defined as 0. */

ATCM_PRV_START = DEFINED(ATCM_START) ? ATCM_START : 0;
ATCM_PRV_LENGTH = DEFINED(ATCM_LENGTH) ? ATCM_LENGTH : 0;
BTCM_PRV_START = DEFINED(BTCM_START) ? BTCM_START : 0;
BTCM_PRV_LENGTH = DEFINED(BTCM_LENGTH) ? BTCM_LENGTH : 0;
SYSTEM_RAM_PRV_START = DEFINED(SYSTEM_RAM_START) ? SYSTEM_RAM_START : 0;
SYSTEM_RAM_PRV_LENGTH = DEFINED(SYSTEM_RAM_LENGTH) ? SYSTEM_RAM_LENGTH : 0;
SYSTEM_RAM_MIRROR_PRV_START = DEFINED(SYSTEM_RAM_MIRROR_START) ? SYSTEM_RAM_MIRROR_START : 0;
SYSTEM_RAM_MIRROR_PRV_LENGTH = DEFINED(SYSTEM_RAM_MIRROR_LENGTH) ? SYSTEM_RAM_MIRROR_LENGTH : 0;
xSPI0_CS0_SPACE_MIRROR_PRV_START = DEFINED(xSPI0_CS0_SPACE_MIRROR_START) ? xSPI0_CS0_SPACE_MIRROR_START : 0;
xSPI0_CS0_SPACE_MIRROR_PRV_LENGTH = DEFINED(xSPI0_CS0_SPACE_MIRROR_LENGTH) ? xSPI0_CS0_SPACE_MIRROR_LENGTH : 0;
xSPI0_CS1_SPACE_MIRROR_PRV_START = DEFINED(xSPI0_CS1_SPACE_MIRROR_START) ? xSPI0_CS1_SPACE_MIRROR_START : 0;
xSPI0_CS1_SPACE_MIRROR_PRV_LENGTH = DEFINED(xSPI0_CS1_SPACE_MIRROR_LENGTH) ? xSPI0_CS1_SPACE_MIRROR_LENGTH : 0;
xSPI1_CS0_SPACE_MIRROR_PRV_START = DEFINED(xSPI1_CS0_SPACE_MIRROR_START) ? xSPI1_CS0_SPACE_MIRROR_START : 0;
xSPI1_CS0_SPACE_MIRROR_PRV_LENGTH = DEFINED(xSPI1_CS0_SPACE_MIRROR_LENGTH) ? xSPI1_CS0_SPACE_MIRROR_LENGTH : 0;
xSPI1_CS1_SPACE_MIRROR_PRV_START = DEFINED(xSPI1_CS1_SPACE_MIRROR_START) ? xSPI1_CS1_SPACE_MIRROR_START : 0;
xSPI1_CS1_SPACE_MIRROR_PRV_LENGTH = DEFINED(xSPI1_CS1_SPACE_MIRROR_LENGTH) ? xSPI1_CS1_SPACE_MIRROR_LENGTH : 0;
CS0_SPACE_MIRROR_PRV_START = DEFINED(CS0_SPACE_MIRROR_START) ? CS0_SPACE_MIRROR_START : 0;
CS0_SPACE_MIRROR_PRV_LENGTH = DEFINED(CS0_SPACE_MIRROR_LENGTH) ? CS0_SPACE_MIRROR_LENGTH : 0;
CS2_SPACE_MIRROR_PRV_START = DEFINED(CS2_SPACE_MIRROR_START) ? CS2_SPACE_MIRROR_START : 0;
CS2_SPACE_MIRROR_PRV_LENGTH = DEFINED(CS2_SPACE_MIRROR_LENGTH) ? CS2_SPACE_MIRROR_LENGTH : 0;
CS3_SPACE_MIRROR_PRV_START = DEFINED(CS3_SPACE_MIRROR_START) ? CS3_SPACE_MIRROR_START : 0;
CS3_SPACE_MIRROR_PRV_LENGTH = DEFINED(CS3_SPACE_MIRROR_LENGTH) ? CS3_SPACE_MIRROR_LENGTH : 0;
CS5_SPACE_MIRROR_PRV_START = DEFINED(CS5_SPACE_MIRROR_START) ? CS5_SPACE_MIRROR_START : 0;
CS5_SPACE_MIRROR_PRV_LENGTH = DEFINED(CS5_SPACE_MIRROR_LENGTH) ? CS5_SPACE_MIRROR_LENGTH : 0;
xSPI0_CS0_SPACE_PRV_START = DEFINED(xSPI0_CS0_SPACE_START) ? xSPI0_CS0_SPACE_START : 0;
xSPI0_CS0_SPACE_PRV_LENGTH = DEFINED(xSPI0_CS0_SPACE_LENGTH) ? xSPI0_CS0_SPACE_LENGTH : 0;
xSPI0_CS1_SPACE_PRV_START = DEFINED(xSPI0_CS1_SPACE_START) ? xSPI0_CS1_SPACE_START : 0;
xSPI0_CS1_SPACE_PRV_LENGTH = DEFINED(xSPI0_CS1_SPACE_LENGTH) ? xSPI0_CS1_SPACE_LENGTH : 0;
xSPI1_CS0_SPACE_PRV_START = DEFINED(xSPI1_CS0_SPACE_START) ? xSPI1_CS0_SPACE_START : 0;
xSPI1_CS0_SPACE_PRV_LENGTH = DEFINED(xSPI1_CS0_SPACE_LENGTH) ? xSPI1_CS0_SPACE_LENGTH : 0;
xSPI1_CS1_SPACE_PRV_START = DEFINED(xSPI1_CS1_SPACE_START) ? xSPI1_CS1_SPACE_START : 0;
xSPI1_CS1_SPACE_PRV_LENGTH = DEFINED(xSPI1_CS1_SPACE_LENGTH) ? xSPI1_CS1_SPACE_LENGTH : 0;
CS0_SPACE_PRV_START = DEFINED(CS0_SPACE_START) ? CS0_SPACE_START : 0;
CS0_SPACE_PRV_LENGTH = DEFINED(CS0_SPACE_LENGTH) ? CS0_SPACE_LENGTH : 0;
CS2_SPACE_PRV_START = DEFINED(CS2_SPACE_START) ? CS2_SPACE_START : 0;
CS2_SPACE_PRV_LENGTH = DEFINED(CS2_SPACE_LENGTH) ? CS2_SPACE_LENGTH : 0;
CS3_SPACE_PRV_START = DEFINED(CS3_SPACE_START) ? CS3_SPACE_START : 0;
CS3_SPACE_PRV_LENGTH = DEFINED(CS3_SPACE_LENGTH) ? CS3_SPACE_LENGTH : 0;
CS5_SPACE_PRV_START = DEFINED(CS5_SPACE_START) ? CS5_SPACE_START : 0;
CS5_SPACE_PRV_LENGTH = DEFINED(CS5_SPACE_LENGTH) ? CS5_SPACE_LENGTH : 0;

/* User customizes the location in here */		 
FSP_STARTUP_LOCATION = 0x10040000;		 
SYSTEM_RAM_PRV_START = DEFINED(FSP_STARTUP_LOCATION) ? (FSP_STARTUP_LOCATION + 0x10000) : 0x10000000;

_RZT_ORDINAL = ((0x00100000 == BTCM_PRV_START && 0x10000000 == SYSTEM_RAM_PRV_START)) ? 1 : 2;
HAS_SYSTEM_RAM_MIRROR = DEFINED(SYSTEM_RAM_MIRROR_START) ? 1 : 0;

SYSTEM_RAM_ALIGN_START            = ALIGN(SYSTEM_RAM_PRV_START, 0x00020000);
SYSTEM_RAM_ALIGN_LENGTH           = SYSTEM_RAM_PRV_LENGTH - (SYSTEM_RAM_PRV_LENGTH % 0x00020000);
SYSTEM_RAM_MIRROR_OFFSET          = (0 == HAS_SYSTEM_RAM_MIRROR) ? (DEFINED(CR52_0) || DEFINED(CR52_1)) ? 0x00000000 :
                                                                                                          0x00200000 :
                                                                   0x20000000;

RAM_START                         = ((1 == _RZT_ORDINAL) && DEFINED(CR52_0)) ? ATCM_PRV_START : SYSTEM_RAM_ALIGN_START;
RAM_LENGTH                        = ((1 == _RZT_ORDINAL) && DEFINED(CR52_0)) ? ATCM_PRV_LENGTH : SYSTEM_RAM_ALIGN_LENGTH;
LOADER_START                      = ((1 == _RZT_ORDINAL) && DEFINED(CR52_0)) ? BTCM_PRV_START : SYSTEM_RAM_ALIGN_START;
LOADER_LENGTH                     = ((1 == _RZT_ORDINAL) && DEFINED(CR52_0)) ? BTCM_PRV_LENGTH : SYSTEM_RAM_ALIGN_LENGTH;

INTVEC_ADDRESS                    = RAM_START;
LOADER_TEXT_ADDRESS               = ((1 == _RZT_ORDINAL) && DEFINED(CR52_0)) ? LOADER_START + 0x00002000 : LOADER_START + 0x00001000;
NONCACHE_INIT_ADDRESS             = (1 == _RZT_ORDINAL) ? DATA_NONCACHE_INIT_START : SYSTEM_RAM_ALIGN_START + 0x00010000;
TEXT_ADDRESS                      = (1 == _RZT_ORDINAL) ? DEFINED(CR52_0) ? RAM_START + 0x00000100 :
                                                                              RAM_START + 0x00010000 :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? RAM_START + 0x00010000 :
                                                                                                                                   noncache_init_end;

/* Define starting addresses for CPU-shared and CPU-specific non-cache areas. */
DATA_NONCACHE_OFFSET              = DEFINED(SYSTEM_RAM_START) ? 0x00068000 : 0;
DMAC_LINK_MODE_OFFSET             = DEFINED(SYSTEM_RAM_START) ? 0x00064000 : 0;
SHARED_NONCACHE_BUFFER_OFFSET     = DEFINED(SYSTEM_RAM_START) ? 0x00060000 : 0;
NONCACHE_BUFFER_OFFSET            = DEFINED(SYSTEM_RAM_START) ? 0x00040000 : 0;

SYSTEM_RAM_END_ADDRESS            = SYSTEM_RAM_ALIGN_START + SYSTEM_RAM_ALIGN_LENGTH;
SYSTEM_RAM_MIRROR_END_ADDRESS     = SYSTEM_RAM_ALIGN_START + SYSTEM_RAM_ALIGN_LENGTH + SYSTEM_RAM_MIRROR_OFFSET;

DATA_NONCACHE_INIT_START          = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_END_ADDRESS - DATA_NONCACHE_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? __ThreadStackLimit :
                                                                                                                                   _mdata_noncache;
DMAC_LINK_MODE_INIT_START         = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_END_ADDRESS - DMAC_LINK_MODE_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? _data_noncache_end :
                                                                                                                                   _mdmac_link_mode;
NONCACHE_BUFFER_INIT_START        = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_END_ADDRESS - NONCACHE_BUFFER_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? _dmac_link_mode_end :
                                                                                                                                   _mncbuffer;
SHARED_NONCACHE_BUFFER_INIT_START = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_END_ADDRESS - SHARED_NONCACHE_BUFFER_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? _ncbuffer_end :
                                                                                                                                   _msncbuffer;

DATA_NONCACHE_START               = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_MIRROR_END_ADDRESS - DATA_NONCACHE_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? __ThreadStackLimit :
                                                                                                                                   _mdata_noncache + SYSTEM_RAM_MIRROR_OFFSET;
DMAC_LINK_MODE_START              = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_MIRROR_END_ADDRESS - DMAC_LINK_MODE_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? _data_noncache_end :
                                                                                                                                   _mdmac_link_mode + SYSTEM_RAM_MIRROR_OFFSET;
NONCACHE_BUFFER_START             = (1 == _RZT_ORDINAL) ? SYSTEM_RAM_MIRROR_END_ADDRESS - NONCACHE_BUFFER_OFFSET :
                                                          ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? _dmac_link_mode_end :
                                                                                                                                   _mncbuffer + SYSTEM_RAM_MIRROR_OFFSET;
SHARED_NONCACHE_BUFFER_START      = SYSTEM_RAM_MIRROR_END_ADDRESS - SHARED_NONCACHE_BUFFER_OFFSET;

data_noncache_size                = _data_noncache_end - _data_noncache_start;
dmac_link_mode_size               = _dmac_link_mode_end - _dmac_link_mode_start;
sncbuffer_size                    = _sncbuffer_end - _sncbuffer_start;
ncbuffer_size                     = _ncbuffer_end - _ncbuffer_start;

MEMORY
{
    ATCM : ORIGIN = ATCM_PRV_START, LENGTH = ATCM_PRV_LENGTH
    BTCM : ORIGIN = BTCM_PRV_START, LENGTH = BTCM_PRV_LENGTH
    SYSTEM_RAM : ORIGIN = SYSTEM_RAM_ALIGN_START, LENGTH = SYSTEM_RAM_ALIGN_LENGTH
    SYSTEM_RAM_MIRROR : ORIGIN = SYSTEM_RAM_MIRROR_PRV_START, LENGTH = SYSTEM_RAM_MIRROR_PRV_LENGTH
    xSPI0_CS0_SPACE_MIRROR : ORIGIN = xSPI0_CS0_SPACE_MIRROR_PRV_START, LENGTH = xSPI0_CS0_SPACE_MIRROR_PRV_LENGTH
    xSPI0_CS1_SPACE_MIRROR : ORIGIN = xSPI0_CS1_SPACE_MIRROR_PRV_START, LENGTH = xSPI0_CS1_SPACE_MIRROR_PRV_LENGTH
    xSPI1_CS0_SPACE_MIRROR : ORIGIN = xSPI1_CS0_SPACE_MIRROR_PRV_START, LENGTH = xSPI1_CS0_SPACE_MIRROR_PRV_LENGTH
    xSPI1_CS1_SPACE_MIRROR : ORIGIN = xSPI1_CS1_SPACE_MIRROR_PRV_START, LENGTH = xSPI1_CS1_SPACE_MIRROR_PRV_LENGTH
    CS0_SPACE_MIRROR : ORIGIN = CS0_SPACE_MIRROR_PRV_START, LENGTH = CS0_SPACE_MIRROR_PRV_LENGTH
    CS2_SPACE_MIRROR : ORIGIN = CS2_SPACE_MIRROR_PRV_START, LENGTH = CS2_SPACE_MIRROR_PRV_LENGTH
    CS3_SPACE_MIRROR : ORIGIN = CS3_SPACE_MIRROR_PRV_START, LENGTH = CS3_SPACE_MIRROR_PRV_LENGTH
    CS5_SPACE_MIRROR : ORIGIN = CS5_SPACE_MIRROR_PRV_START, LENGTH = CS5_SPACE_MIRROR_PRV_LENGTH
    xSPI0_CS0_SPACE : ORIGIN = xSPI0_CS0_SPACE_PRV_START, LENGTH = xSPI0_CS0_SPACE_PRV_LENGTH
    xSPI0_CS1_SPACE : ORIGIN = xSPI0_CS1_SPACE_PRV_START, LENGTH = xSPI0_CS1_SPACE_PRV_LENGTH
    xSPI1_CS0_SPACE : ORIGIN = xSPI1_CS0_SPACE_PRV_START, LENGTH = xSPI1_CS0_SPACE_PRV_LENGTH
    xSPI1_CS1_SPACE : ORIGIN = xSPI1_CS1_SPACE_PRV_START, LENGTH = xSPI1_CS1_SPACE_PRV_LENGTH
    CS0_SPACE : ORIGIN = CS0_SPACE_PRV_START, LENGTH = CS0_SPACE_PRV_LENGTH
    CS2_SPACE : ORIGIN = CS2_SPACE_PRV_START, LENGTH = CS2_SPACE_PRV_LENGTH
    CS3_SPACE : ORIGIN = CS3_SPACE_PRV_START, LENGTH = CS3_SPACE_PRV_LENGTH
    CS5_SPACE : ORIGIN = CS5_SPACE_PRV_START, LENGTH = CS5_SPACE_PRV_LENGTH
    RAM_TEXT : ORIGIN = RAM_START, LENGTH = RAM_LENGTH
    RAM_DATA : ORIGIN = RAM_START, LENGTH = RAM_LENGTH
    LOADER_TEXT_STACK : ORIGIN = LOADER_START, LENGTH = LOADER_LENGTH
    LOADER_DATA_STACK : ORIGIN = LOADER_START, LENGTH = LOADER_LENGTH
    NONCACHE_INIT : ORIGIN = SYSTEM_RAM_ALIGN_START, LENGTH = SYSTEM_RAM_ALIGN_LENGTH
    NONCACHE : ORIGIN = SYSTEM_RAM_ALIGN_START + SYSTEM_RAM_MIRROR_OFFSET, LENGTH = SYSTEM_RAM_ALIGN_LENGTH
}

SECTIONS
{
    .loader_text LOADER_TEXT_ADDRESS : AT (LOADER_TEXT_ADDRESS)
    {
        _loader_text_start = .;
        *(.loader_text)
        */fsp/src/bsp/cmsis/Device/RENESAS/Source/*.o(.text*)
        */fsp/src/bsp/mcu/all/*/bsp_irq_core.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_clocks.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_irq.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_semaphore.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_register_protection.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_cache.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_tzc400.o(.text*)
        */fsp/src/bsp/mcu/all/bsp_address_expander.o(.text*)
        */fsp/src/r_ioport/r_ioport.o(.text*)
        KEEP(*(.warm_start))
        _loader_text_end = .;
    } > LOADER_TEXT_STACK
    .loader_data _loader_text_end :
    {
        */fsp/src/bsp/cmsis/Device/RENESAS/Source/*.o(.data*)
        */fsp/src/bsp/cmsis/Device/RENESAS/Source/*/system_core.o(.rodata*)
        */fsp/src/bsp/mcu/all/*/bsp_irq_core.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_clocks.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_irq.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_semaphore.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_register_protection.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_register_protection.o(.rodata*)
        */fsp/src/bsp/mcu/all/bsp_cache.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_tzc400.o(.data*)
        */fsp/src/bsp/mcu/all/bsp_tzc400.o(.rodata*)
        */fsp/src/bsp/mcu/all/bsp_address_expander.o(.data*)
        */fsp/src/r_ioport/r_ioport.o(.data*)
        . = ALIGN(8);
        __loader_bss_start = .;
        */fsp/src/bsp/cmsis/Device/RENESAS/Source/*.o(.bss*)
        */fsp/src/bsp/mcu/all/*/bsp_irq_core.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_clocks.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_irq.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_semaphore.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_register_protection.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_cache.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_tzc400.o(.bss*)
        */fsp/src/bsp/mcu/all/bsp_address_expander.o(.bss*)
        */fsp/src/r_ioport/r_ioport.o(.bss*)
        KEEP(*(.ttbr))
        */fsp/src/bsp/cmsis/Device/RENESAS/Source/*.o(COMMON)
        */fsp/src/bsp/mcu/all/*/bsp_irq_core.o(COMMON)
        */fsp/src/bsp/mcu/all/bsp_clocks.o(COMMON)
        */fsp/src/bsp/mcu/all/bsp_irq.o(COMMON)
        */fsp/src/bsp/mcu/all/bsp_semaphore.o(COMMON)
        */fsp/src/bsp/mcu/all/bsp_register_protection.o(.COMMON)
        */fsp/src/bsp/mcu/all/bsp_cache.o(.COMMON)
        */fsp/src/bsp/mcu/all/bsp_tzc400.o(.COMMON)
        */fsp/src/bsp/mcu/all/bsp_address_expander.o(.COMMON)
        */fsp/src/r_ioport/r_ioport.o(.COMMON)
        . = ALIGN(8);
        __loader_bss_end = . ;
    } > LOADER_DATA_STACK
    .intvec INTVEC_ADDRESS : AT (INTVEC_ADDRESS)
    {
        _fvector_start = .;
        KEEP(*(.intvec))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x080))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x100))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x180))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x200))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x280))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x300))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x380))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x400))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x480))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x500))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x580))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x600))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x680))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x700))
        . = ALIGN(0x80);
        KEEP(*(.intvec_0x780))
        _fvector_end = .;
    } > RAM_TEXT
    .noncache_init NONCACHE_INIT_ADDRESS : AT (NONCACHE_INIT_ADDRESS)
    {
        . = (0 != data_noncache_size) ? ALIGN(8) : .;
        _mdata_noncache = .;
        . = . + data_noncache_size;
        . = (0 != dmac_link_mode_size) ? ALIGN(8) : .;
        _mdmac_link_mode = .;
        . = . + dmac_link_mode_size;
        . = (0 != sncbuffer_size) ? ALIGN(32) : .;
        _msncbuffer = .;
        . = . + sncbuffer_size;
        . = (0 != ncbuffer_size) ? ALIGN(32) : .;
        _mncbuffer = .;
        . = . + ncbuffer_size;
        noncache_init_end = .;
    } > NONCACHE_INIT
    .text TEXT_ADDRESS : AT (TEXT_ADDRESS)
    {
        _text_start = .;
        *(.text*)

        KEEP(*(.reset_handler))

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        _ctor_end = .;

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        _dtor_end = .;

        KEEP(*(.eh_frame*))
    } > RAM_TEXT
    .rvectors :
    {
        _rvectors_start = .;
        KEEP(*(.rvectors))
        _rvectors_end = .;
    } > RAM_TEXT
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > RAM_TEXT
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
        _text_end = .;
    } > RAM_TEXT
    .data _text_end :
    {
        _data_start = .;

        *(vtable)
        *(.data.*)
        *(.data)

        *(.rodata*)
        _erodata = .;

        . = ALIGN(8);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(8);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(8);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))

        . = ALIGN(8);

    } > RAM_DATA
    .got :
    {
        *(.got)
        *(.got.plt)

        /* All data end */
        _data_end = .;
    } > RAM_DATA
    .bss :
    {
        . = ALIGN(8);
        __bss_start__ = .;
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end__ = .;
        _ebss = .;
        _end = .;
    } > RAM_DATA
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __HeapBase = .;
        /* Place the STD heap here. */
        KEEP(*(.heap))
        __HeapLimit = .;
    } > RAM_DATA
    .aarch64_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __AArch64StackBase = .;
        /* Place the Thread stacks here. */
        KEEP(*(.aarch64_stack*))
        __AArch64StackLimit = .;
    } > RAM_DATA
    .thread_stack (NOLOAD):
    {
        . = ALIGN(8);
        __ThreadStackBase = .;
        /* Place the Thread stacks here. */
        KEEP(*(.stack*))
        __ThreadStackLimit = .;
    } > RAM_DATA
    .sys_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __SysStackBase = .;
        /* Place the sys_stack here. */
        KEEP(*(.sys_stack))
        __SysStackLimit = .;
    } > LOADER_DATA_STACK
    .svc_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __SvcStackBase = .;
        /* Place the svc_stack here. */
        KEEP(*(.svc_stack))
        __SvcStackLimit = .;
    } > LOADER_DATA_STACK
    .irq_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __IrqStackBase = .;
        /* Place the irq_stack here. */
        KEEP(*(.irq_stack))
        __IrqStackLimit = .;
    } > LOADER_DATA_STACK
    .fiq_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __FiqStackBase = .;
        /* Place the fiq_stack here. */
        KEEP(*(.fiq_stack))
        __FiqStackLimit = .;
    } > LOADER_DATA_STACK
    .und_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __UndStackBase = .;
        /* Place the und_stack here. */
        KEEP(*(.und_stack))
        __UndStackLimit = .;
    } > LOADER_DATA_STACK
    .abt_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __AbtStackBase = .;
        /* Place the abt_stack here. */
        KEEP(*(.abt_stack))
        __AbtStackLimit = .;
    } > LOADER_DATA_STACK
    .data_noncache DATA_NONCACHE_START : AT (DATA_NONCACHE_INIT_START)
    {
        . = ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? ALIGN(64) : ALIGN(8);
        _data_noncache_start = .;
        KEEP(*(.data_noncache*))
        _data_noncache_end = .;
    } > NONCACHE
    .dmac_link_mode DMAC_LINK_MODE_START : AT (DMAC_LINK_MODE_INIT_START)
    {
        . = ALIGN(8);
        _dmac_link_mode_start = .;
        KEEP(*(.dmac_link_mode*))
        _dmac_link_mode_end = .;
    } > NONCACHE
    .shared_noncache_buffer SHARED_NONCACHE_BUFFER_START : AT (SHARED_NONCACHE_BUFFER_INIT_START)
    {
        . = ALIGN(32);
        _sncbuffer_start = .;
        KEEP(*(.shared_noncache_buffer*))
        _sncbuffer_end = .;
    } > NONCACHE
    .noncache_buffer NONCACHE_BUFFER_START : AT (NONCACHE_BUFFER_INIT_START)
    {
        . = ALIGN(32);
        _ncbuffer_start = .;
        KEEP(*(.noncache_buffer*))
        _ncbuffer_end = .;
    } > NONCACHE
}

__ddsc_ATCM_START       = ORIGIN(ATCM);
__ddsc_ATCM_END         = (1 == _RZT_ORDINAL) && DEFINED(CR52_0) ? __ThreadStackLimit : __ddsc_ATCM_START;
__ddsc_BTCM_START       = ORIGIN(BTCM);
__ddsc_BTCM_END         = (1 == _RZT_ORDINAL) && DEFINED(CR52_0) ? __AbtStackLimit : __ddsc_BTCM_START;
__ddsc_SYSTEM_RAM_START = ORIGIN(SYSTEM_RAM);
__ddsc_SYSTEM_RAM_END   = (1 == _RZT_ORDINAL) ? DEFINED(CR52_0) ? __ddsc_SYSTEM_RAM_START :
                                                                  __ThreadStackLimit :
                                                ((0 == HAS_SYSTEM_RAM_MIRROR) && (DEFINED(CR52_0) || DEFINED(CR52_1))) ? _ncbuffer_end :
                                                                                                                         __ThreadStackLimit;