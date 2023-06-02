#--------------------------------------------------------------------------
# Template makefile for STM32L432 Devices
# make all = Make software.
# make clean = Clean out built project files.
#
#	See "projectdefs.h" file for specific files to include in the make
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
# MCU name and processor setup
#--------------------------------------------------------------------------
MCU = cortex-m4
THUMB = -mthumb

#  Thumb Interwork is OK
THUMB_IW = -mthumb-interwork

#  Create ROM-Image (final)
RUN_MODE = ROM_RUN

# Output format. (can be srec, ihex, binary) for use by the programmer / DFU
# NOTE: The $(TARGET).elf file is always created
FORMAT = ihex

# Define operating Shell
SHELL = /bin/sh

#--------------------------------------------------------------------------
# Definition of Source Files
#--------------------------------------------------------------------------

# Target file name (without extension). CHANGE THIS FOR YOUR PROJECT!!!
# This file contains the "main" function and the TARGET Output Name
TARGET = PROJECT

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files

SRC = startup.c
SRC += genrtn.c
SRC += opsys.c
SRC += uart_com.c
SRC += sys_tick.c
SRC += interrupts.c
# SRC += test_help.c
SRC += errors.c
# UnComment if I2C1 Used
	# SRC += i2c1.c
	# SRC += eeprom.c
SRC += $(TARGET).c

#--------------------------------------------------------------------------
# List Assembler source files here.
#--------------------------------------------------------------------------
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
#
#--------------------------------------------------------------------------
# Optimization level, can be [0, 1, 2, 3, s].
#--------------------------------------------------------------------------
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level)
# no optimizations
# OPT = 0
# Optimize for Size
OPT = s

#--------------------------------------------------------------------------
# Debugging format.
# DEBUG =
# DEBUG = stabs
#--------------------------------------------------------------------------
DEBUG = dwarf-2

#--------------------------------------------------------------------------
# List any extra directories to look for include files here.
#--------------------------------------------------------------------------
#     Each directory must be seperated by a space.
#EXTRAINCDIRS = ./include
EXTRAINCDIRS =

#--------------------------------------------------------------------------
# Compiler flag to set the C Standard level.
#--------------------------------------------------------------------------
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

#--------------------------------------------------------------------------
# Place -D or -U options for C here
#--------------------------------------------------------------------------
# CDEFS =  -D$(RUN_MODE) Also Disable Debug Info for now
CDEFS = -g$(DEBUG)

#--------------------------------------------------------------------------
# Place -I options here
#--------------------------------------------------------------------------
CINCS =

#--------------------------------------------------------------------------
# Place -D or -U options for ASM here
#--------------------------------------------------------------------------
ADEFS = -D$(RUN_MODE)

#----------------------------------------------------------------------------------------------
# Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -mfloat			 Floatinf Point Math Active
#  -f...:        tuning, see GCC manual and arm-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#----------------------------------------------------------------------------------------------
CFLAGS = $(CDEFS) $(CINCS)
CFLAGS += -O$(OPT) -fverbose-asm -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wno-pointer-sign
# CFLAGS += -Wall -Wimplicit -Wunused-but-set-variable -Wunused-variable
CFLAGS += -Wall -Wimplicit
CFLAGS += -Wpointer-arith -Wswitch -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
CFLAGS += -Wa,-adhlns=$(<:.c=.lsc),-g$(DEBUG)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

# flags only for C
CONLYFLAGS  = -Wstrict-prototypes -Wmissing-declarations
CONLYFLAGS += -Wmissing-prototypes -Wnested-externs
CONLYFLAGS += $(CSTANDARD)

# Assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see arm-libc docs [FIXME: not yet described there]
# ASFLAGS = -Wa,-adhlns=$(<:.S=.lsa),-gstabs
#	ASFLAGS = $(ADEFS) -Wa,-adhlms=$(<:.S=.lst),-g$(DEBUG)
#	ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:.S=.lst),-g$(DEBUG)
# ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:.S=.lst)
# ASFLAGS = $(ADEFS) -Wa,-adhls=$(<:.S=.lst),-ahlms,-gstabs,-g$(DEBUG)

#Additional libraries.

#Support for newlibc-lpc (file: libnewlibc-lpc.a)
MATH_LIB = -lm

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to map file
#    -verbose listing
# LDFLAGS = -nostartfiles -Wl,-Map=$(TARGET).map,--cref,--verbose
LDFLAGS = -nostartfiles -Wl,-Map=$(TARGET).map,-cref,-verbose
LDFLAGS += $(THUMB) $(THUMB_IW)
LDFLAGS += $(MATH_LIB)
LDFLAGS += -lgcc -lc
LDFLAGS += -T$ linkfile.ld

#---------------------------------------------------------------------------
# Define programs and commands.
#--------------------------------------------------------------------------
SHELL = sh
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
NM = arm-none-eabi-gcc-nm
SIZE = arm-none-eabi-size
REMOVE = -rm
COPY = cp

#--------------------------------------------------------------------------
# Define Messages
#--------------------------------------------------------------------------
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- Begin --------
MSG_END = -------- End --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_FLASH = Creating load file for Flash:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_COMPILING_ARM = "Compiling C (ARM-only):"
MSG_COMPILINGCPP = Compiling C++:
MSG_COMPILINGCPP_ARM = "Compiling C++ (ARM-only):"
MSG_ASSEMBLING = Assembling:
MSG_ASSEMBLING_ARM = "Assembling (ARM-only):"
MSG_CLEANING = Cleaning project:
MSG_LPC21_RESETREMINDER = You may have to bring the target in bootloader-mode now.
MSG_TARGET = GCC Target:
MSG_LSA = Creating LSA File.
MSG_NULL = .

#--------------------------------------------------------------------------
# Define all object files.
#--------------------------------------------------------------------------
COBJ      = $(SRC:.c=.o)
AOBJ      = $(ASRC:.S=.o)

#--------------------------------------------------------------------------
# Define all listing files.
#LST = $(ASRC:.S=.lst) $(ASRCARM:.S=.lst) $(SRC:.c=.lst) $(SRCARM:.c=.lst)
#LST = $(ASRC:.S=.lst) $(SRC:.c=.lsc) $(SRCARM:.c=.lac)
LST = $(ASRC:.S=.lsa) $(SRC:.c=.lsc) $(SRCARM:.c=.lac)

#--------------------------------------------------------------------------
# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
#--------------------------------------------------------------------------
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

#--------------------------------------------------------------------------
# Combine all necessary flags and optional flags.
# Add target processor to flags.
#--------------------------------------------------------------------------
ALL_CFLAGS = -mcpu=$(MCU) $(THUMB) $(THUMB_IW) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mcpu=$(MCU) $(THUMB) $(THUMB_IW) -I. -x none

# Default target.
#all: begin gccversion sizebefore build sizeafter finished end
all: begin gccversion build finished end

#--------------------------------------------------------------------------
#build: Definitions elf hex lss sym map
#--------------------------------------------------------------------------
#build: elf hex lss sym map
build: elf hex lss lsa lsc sym map

#--------------------------------------------------------------------------
#		Output File Definitions
#--------------------------------------------------------------------------
elf: $(TARGET).elf
hex: $(TARGET).hex
lss: $(TARGET).lss
lsa: $(TARGET).lsa
lsc: $(TARGET).lsc
sym: $(TARGET).sym
map: $(TARGET).map

#--------------------------------------------------------------------------
# Eye candy.
#--------------------------------------------------------------------------
begin:
	@echo $(MSG_NULL)
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_NULL)
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_NULL)
	@echo $(MSG_END)

#--------------------------------------------------------------------------
# Display size of file.
#--------------------------------------------------------------------------
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf

sizebefore:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi


#--------------------------------------------------------------------------
# Display compiler version information.
#--------------------------------------------------------------------------
gccversion:
	@$(CC) --version

targvalue:
	@$(CC) --target

#--------------------------------------------------------------------------
# Create Listing and table files from ".elf" file
#--------------------------------------------------------------------------

# Create programmer Intel ".hex" output file
%.hex: %.elf
	@echo $(MSG_NULL)
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo $(MSG_NULL)
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@

# Create extended listing file from ELF output file.
%.lsa: %.elf
	@echo $(MSG_NULL)
	@echo $(MSG_LSA_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@

# Create C extended listing file from ELF output file.
%.lsc: %.elf
	@echo $(MSG_NULL)
	@echo $(MSG_LSA_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo $(MSG_NULL)
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@

# Create a MAP table from ELF output file.
%.map: %.elf
	@echo $(MSG_NULL)
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@


# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf

# .PRECIOUS : $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ)
.PRECIOUS : $(AOBJ) $(COBJ)

%.elf: $(AOBJ) $(COBJ)

#%.elf:  $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ)
	@echo $(MSG_NULL)
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(AOBJ) $(COBJ) --output $@ $(LDFLAGS)

# Compile: create object files from C source files. ARM/Thumb
$(COBJ) : %.o : %.c
	@echo $(MSG_NULL)
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@

# Assemble: create object files from assembler source files. ARM/Thumb
$(AOBJ) : %.o : %.S
	@echo $(MSG_NULL)
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Target: clean project.
clean: begin gccversion clean_list finished end

clean_list :
	$(REMOVE) *.o
#	$(REMOVE) *.obj
	$(REMOVE) *.hex
	$(REMOVE) *.elf
	$(REMOVE) *.map
	$(REMOVE) *.sym
	$(REMOVE) *.lsa
	$(REMOVE) *.lsc
	$(REMOVE) *.lss
	$(REMOVE) .dep/*

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex lss sym clean clean_list program
