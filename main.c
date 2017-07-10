/*
 * file - main.c
 * author - Harlan J. Waldrop <root@aboyandhisgnu.org>
 *
 * EEPROM-PROGRAMMER is a small project which utilizes an Atmega328p and two (2)
 * external, daisy-chained SN74HC595 shift registers to quickly program Atmel
 * EEPROM chips (AT28C16).
 *
 * The microcontroller shifts in a 16-bit control word containing 8 bits of the
 * address signal and the corresponding byte of memory to set. The remaining
 * 3 bits of the address are set manually.
 *
 * FIGURES
 * 	PORTx_7:0 = [ ADDR_10:8 ][ SRCLR, SRCLK, RCLK, OE, SER ]
 *
 * 	[       ATMEGA328P       ]
 * 	 ------------------------
 * 	[ SN74HC595 ][ SN74HC595 ]
 * 	[  ADDRESS  ][  MEMORY   ]
 * 	 ------------------------
 * 	[         AT28C16        ]
 */

#include "snx4hc595.h"

extern void start() __asm__("g_start") __attribute__((noreturn));

void
start(void)
{
	snx4hc595_setup();
	snx4hc595_set(0);

	for (;;);
}
