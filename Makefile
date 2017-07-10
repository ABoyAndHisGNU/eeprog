#
# file - Makefile
# author - Harlan J. Waldrop <root@aboyandhisgnu.org>
# 

MAKEFLAGS += --no-builtin-rules
NAME = eeprog

PREFIX = avr-

CC = $(PREFIX)gcc
CP = $(PREFIX)objcopy

ISP = avrdude
ISP_TOOL = usbtiny
BAUDRATE = 19200

TARGET = 328p
TARGET_ARCH =  avr:5

OPTIMIZE = -Os

CFLAGS = -mmcu=atmega$(TARGET) \
	-std=c99 \
	-nostdlib \
	-Wall \
	-Wextra

LDFLAGS = -Wl,--script=atmega$(TARGET).ld

SRC = vector.S \
	main.c \
	snx4hc595.c

OBJ = $(addsuffix .o, $(SRC))

ELF = $(NAME).elf
HEX = $(NAME).hex

$(HEX): $(ELF)
	$(CP) -O ihex $^ $@

$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

%.o: %
	$(CC) $(CFLAGS) -c -o $@ $^

flash: $(HEX)
	sudo $(ISP) -b $(BAUDRATE) -c $(ISP_TOOL) -p m$(TARGET) -e -U flash:w:$^ -P usb -v

clean:
	rm -f $(OBJ) $(HEX) $(ELF)

.PHONY: clean flash
