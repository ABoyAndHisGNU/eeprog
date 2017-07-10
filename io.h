/*
 * file - io.h
 * author - Harlan J. Waldrop
 */

#ifndef IO_H_
#define IO_H_

#include <stdint.h>

#define IO_OFFSET(io_addr)	((io_addr) + 0x20)

#define SET(addr)	(*(volatile uint8_t *)(addr))

#endif /* IO_H_ */
