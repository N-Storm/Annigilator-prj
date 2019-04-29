DEVICE     = atmega48
F_CPU      = 16000000
PROGRAMMER = -c usbasp -P /dev/ttyUSB* -b 115200 
OBJECTS    = avr-init.o otvet.o start_test.o main.o

######################################################################
######################################################################

# Tune the lines below only if you know what you are doing:

CC = avr-gcc
SIZE = avr-size
CFLAGS = -Os -std=gnu11 -flto -Wall -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fpack-struct -fshort-enums
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) -v
COMPILE = $(CC) $(CFLAGS) -DF_CPU=$(F_CPU) -mmcu=$(DEVICE)

# symbolic targets:
all:	an-prj.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:an-prg.hex:i

fuse:	all flash
	$(AVRDUDE) -x section_config -e
	$(AVRDUDE) -U fuse:w:0xfe:m

install: flash

clean:
	rm -f an-prj.hex an-prj.elf an-prj.lss $(OBJECTS)

# file targets:
an-prj.elf: $(OBJECTS)
	$(COMPILE) -o an-prj.elf $(OBJECTS)

an-prj.hex: an-prj.elf
	rm -f an-prj.hex
	avr-objcopy -j .text -j .data -O ihex an-prj.elf an-prj.hex
	$(SIZE) -C --mcu=$(DEVICE) an-prj.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	an-prj.elf
	avr-objdump -d -h -S an-prj.elf > an-prj.lss

cpp:
	$(COMPILE) -E an-prj.c

debug: CFLAGS = -DDEBUG -Og -g -std=gnu11 -Wall
debug: clean an-prj.hex disasm
