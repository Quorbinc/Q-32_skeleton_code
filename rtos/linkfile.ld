/*-------------------------------------------------------------------------------------------*/
/* Linker script for STM32L432C  256K Flash & 64K RAM                                        */
/*-------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------*/
/* Memory Spaces Definitions   RAM = 65536  @ 0x20000000  ROM = 262144 @ 0x08000000          */
/*-------------------------------------------------------------------------------------------*/
MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000,  LENGTH = 0x00010000      /* RAM Size =  65536 Bytes */
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x00040000      /* ROM Size = 262144 Bytes */
}

/*--- Length of RAM = 65536 ---*/
eram = 0x20000000 + 0x00010000;
_eram = eram;
__eram = _eram;

/*--- Length of ROM = 262144 ---*/
eflash = 0x08000000 + 0x00040000;
_eflash = eflash;
__eflash = _eflash;

/*-------------------------------------------------------------------------------------------*/
/* Define Stack */
/*-------------------------------------------------------------------------------------------*/
/* Assign 4K Bytes for Stack Size */
Minimum_Stack_Size = 0x1000;
Stack_Size = 0x1000;                            /*--- Size of Stack = 4K */
Stack_End = _eram;                              /*--- End of Stack Address Value Highest RAM */
Stack_Start = Stack_End - Stack_Size;           /*--- Beginning, Lowest Address of Stack     */

PROVIDE ( _Stack_Size = Stack_Size ) ;
PROVIDE ( __Stack_Size = Stack_Size ) ;

estack = 0x20010000;                            /*--- Define End of Stack */
_estack = estack;

/*-------------------------------------------------------------------------------------------*/
/* Define of Heap Size */
/*-------------------------------------------------------------------------------------------*/

/* _Min_Heap_Size = 0x0000; */
_Min_Heap_Size = 0;
/* end of allocated ram _end */
PROVIDE( _HEAP_START = _end );
/* end of the heap -> align 8 byte */
PROVIDE ( _HEAP_END = ALIGN(ORIGIN(RAM) + LENGTH(RAM) - 8 ,8) );

/*-------------------------------------------------------------------------------------------*/
/*  Define Memory Sections                                                                   */
/* "STM32_SEC_FLASH.ld"                                                                      */
/*-------------------------------------------------------------------------------------------*/

SECTIONS
{
  /*-----------------------------------------------------------------------------------------*/
  /*      For Cortex devices, the beginning of the Vector Table is at The Bottom of FLASH    */
  /*-----------------------------------------------------------------------------------------*/
  .isr_vector :
  {
    . = ALIGN(4);
      KEEP(*(.isr_vector))     /* ISR Vector Table in Flash */
    . = ALIGN(4);
  } >FLASH

  /*-----------------------------------------------------------------------------------------*/
  /* the program code is stored in the .text section, which goes to Flash                    */
  /*-----------------------------------------------------------------------------------------*/

  .text :
  {
    . = ALIGN(4);
    *(.text)                   /* remaining code */
    *(.text.*)
    . = ALIGN(4);
    *(.rodata)                 /* read-only data (constants) */
    . = ALIGN(4);
    _etext = .;

    /*---------------------------------------------------------------------------------------*/
    /* This is used by the startup in order to initialize the .data secion                   */
    /*---------------------------------------------------------------------------------------*/

   _sidata = _etext;
  } >FLASH

  /*-----------------------------------------------------------------------------------------*/
  /*  This is the initialized data section                                                   */
  /*  The program executes knowing that the data is in the RAM                               */
  /*  but the loader puts the initial values in the FLASH (inidata).                         */
  /*  It is one task of the startup to copy the initial values from FLASH to RAM.            */
  /*-----------------------------------------------------------------------------------------*/

  .data  : AT ( _sidata )
  {
    . = ALIGN(8);
    _sdata = . ;    /* This is used by the startup in order to initialize the .data Start    */
    *(.data)
    . = ALIGN(8);
    _edata = . ;    /* This is used by the startup in order to initialize the .data End      */
  } >RAM

  /* This is the uninitialized data section in RAM */
  .bss :
  {
    . = ALIGN(8);
    _sbss = .;      /* This is used by the startup in order to initialize the .bss Start     */

    *(.bss)
    *(COMMON)
    . = ALIGN(8);

    _ebss = . ;     /* This is used by the startup in order to initialize the .bss End       */
  } >RAM

  PROVIDE ( start = _sbss );
  PROVIDE ( _start = _sbss );
  PROVIDE ( end = _ebss );
  PROVIDE ( _end = _ebss );
}

