/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#include "api/ArduinoAPI.h"

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"{
#endif

#define TOGGLE          0x2
#define PINCTRL_OFFSET  0x10

/* Analog reference options */

/* Change in mega4809: two places to define analog reference
 - VREF peripheral defines internal reference
 - analog peripherals define internal/Vdd/external
*/

 // internal from VREF
 // external from VREF pin

#define INTERNAL0V55 0x0
#define INTERNAL1V1 0x1
#define INTERNAL2V5 0x2
#define INTERNAL4V3 0x3
#define INTERNAL1V5 0x4

#define DEFAULT     INTERNAL0V55
#define INTERNAL    ADC_REFSEL_INTREF_gc
#define VDD         ADC_REFSEL_VDDREF_gc
#define EXTERNAL    ADC_REFSEL_VREFA_gc

extern uint32_t F_CPU_CORRECTED;

#define interrupts() sei()
#define noInterrupts() cli()

uint16_t clockCyclesPerMicrosecond(uint32_t clk);
uint16_t clockCyclesToMicroseconds(uint16_t cycles, uint32_t clk);
uint32_t microsecondsToClockCycles(uint16_t cycles, uint32_t clk);

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

extern const uint8_t PROGMEM digital_pin_to_port[];
extern const uint8_t PROGMEM digital_pin_to_bit_mask[];
extern const uint8_t PROGMEM digital_pin_to_bit_position[];
extern const uint8_t PROGMEM digital_pin_to_timer[];
extern const uint8_t PROGMEM port_interrupt_offset[];
extern const uint8_t PROGMEM digital_pin_to_interrupt[];

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.
// 
// These perform slightly better as macros compared to inline functions
//
#define digitalPinToPort(pin) ( (pin < NUM_TOTAL_PINS) ? pgm_read_byte(digital_pin_to_port + pin) : NOT_A_PIN )
#define digitalPinToBitPosition(pin) ( (pin < NUM_TOTAL_PINS) ? pgm_read_byte(digital_pin_to_bit_position + pin) : NOT_A_PIN )
#define analogPinToBitPosition(pin) ( (pin < NUM_ANALOG_INPUTS) ? pgm_read_byte(digital_pin_to_bit_position + pin + 14) : NOT_A_PIN )
#define digitalPinToBitMask(pin) ( (pin < NUM_TOTAL_PINS) ? (1 << digitalPinToBitPosition(pin)) : NOT_A_PIN )
#define analogPinToBitMask(pin) ( (pin < NUM_ANALOG_INPUTS) ? (1 << analogPinToBitPosition(pin)) : NOT_A_PIN )
#define digitalPinToTimer(pin) ( (pin < NUM_TOTAL_PINS) ? pgm_read_byte(digital_pin_to_timer + pin) : NOT_ON_TIMER )

#define portToPortStruct(port) ((PORT_t *)&PORTA + port)
#define digitalPinToPortStruct(pin) ( (pin < NUM_TOTAL_PINS) ? ((PORT_t *)&PORTA + digitalPinToPort(pin)) : NULL)
#define getPINnCTRLregister(port, bit_pos) ( (port != NULL) ? ((uint8_t *)&(port->PIN0CTRL) + bit_pos) : NULL )
#define digitalPinToInterrupt(p) ( pgm_read_byte(digital_pin_to_interrupt + p) )
#define portPinToInterrupt(port, bit_pos) ( pgm_read_byte(port_interrupt_offset + port) + bit_pos )

#define NOT_A_PIN 255
#define NOT_A_PORT 255
#define NOT_AN_INTERRUPT 255

#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4
#define PF 5

#define NOT_ON_TIMER 0
#define TIMERA0 1
#define TIMERB0 2
#define TIMERB1 3
#define TIMERB2 4
#define TIMERB3 5

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "UART.h"
#include "USBCore.h"
#include "CDC.h"
#include "MSC.h"
#if defined(HAVE_HWSERIAL0) && defined(HAVE_CDCSERIAL)
#error "Targets with both UART0 and CDC serial not supported"
#endif

#endif

#include "pins_arduino.h"

#endif
