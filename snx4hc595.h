/*
 * file - snx4hc595.h
 * author - Harlan J. Waldrop <root@aboyandhisgnu.org>
 *
 * DESCRIPTION
 * 	Handles control signals for an external 8-bit shift register.
 */

#ifndef SNx4HC595_H_
#define SNx4HC595_H_

#include <stdint.h>

void snx4hc595_setup();
void snx4hc595_set(uint8_t byte);

#endif /* SNx4HC595_H_ */
