/*
 * file - snx4hc595.c
 * author - Harlan J. Waldrop <root@aboyandhisgnu.org>
 */

#include "snx4hc595.h"

#include "atmega328p.h"
#include "io.h"
#include "utils.h"

#define PORTX	PORTD
#define DDRX	DDRD

#define SER	0	// Serial Output
#define OE	1	// Output Enable (negated)
#define RCLK	2	// Refresh Output Clock
#define SRCLK	3	// Shift Register Clock
#define SRCLR	4	// Shift Register Clear (negated)

/*
 * FUNCTION
 * 	static INLINE(void) _clear(void)
 * 
 * DESCRIPTION
 * 	Resets the contents of the SNx4HC595
 */
static INLINE(void)
_clear(void)
{
	SET(PORTX) &= ~(1 << SRCLR);
	SET(PORTX) |= (1 << SRCLR);
}

/*
 * FUNCTION
 * 	static INLINE(void) _enable(void)
 *
 * DESCRIPTION
 * 	Enables parallel output.
 */
static INLINE(void)
_enable(void)
{
	SET(PORTX) &= ~(1 << OE); 
}

/*
 * FUNCTION
 * 	static INLINE(void) _refresh(void)
 * 
 * DESCRIPTION
 * 	Pulses the RCLK bit in order to refresh output lines.
 */
static INLINE(void)
_refresh(void)
{
	SET(PORTX) &= ~(1 << RCLK);
	SET(PORTX) |= (1 << RCLK);
	SET(PORTX) &= ~(1 << RCLK);
}

/*
 * FUNCTION
 * 	void snx4hc595_set(uint8_t byte)
 * 
 * DESCRIPTION
 * 	Sets the contents of the shift register to 'byte' and calls _refresh()
 */
void
snx4hc595_set(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t bit = (byte & 1);

		SET(PORTX) |= (bit << SER);
		SET(PORTX) |= (1 << SRCLK);
		SET(PORTX) &= ~(1 << SRCLK);
		SET(PORTX) &= ~(1 << SER);

		byte >>= 1;
	}

	_refresh();
}

/*
 * FUNCTION
 * 	void snx4hc595_setup(void)
 *
 * DESCRIPTION
 * 	Configures the last 5 bits of DDRx in the microcontroller for
 * 	output and initializes it to 0 and does the following:
 * 		(1) Clears the SNx4HC595
 * 		(2) Turns on parallel output
 */
void
snx4hc595_setup(void)
{
	SET(DDRX) = 0x1F;	// lowest 5 bits are control lines
	SET(PORTX) = 0x00;	// set contents to known value (0)

	_clear();
	_enable();
}
