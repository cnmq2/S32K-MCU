/**
 * @file main.c
 * @author Chu Nhat Minh Quan
 * @brief Application controls an LED to blink in a cycle of 3 seconds, with the sequence RED → GREEN → BLUE.
 * @version 1.0
 * @date 2025-09-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "S32K144.h"

/**
 * @brief Delay for a given number of cycles using a busy-wait loop.
 *
 * @param cycles
 */
void delay (volatile int cycles)
{
	while(cycles--);
}

/**
 * @brief Toggle an LED on the given pin with a delay.
 * 
 * @param u8PinNumber 
 * @param time
 */
void blink_LED(uint8_t u8PinNumber, uint32_t time)
{
	/*Toggle the pin with delay 3s using Port Toggle Output Register*/
	/*PORTD base address: 0x400FF0C0, offset for PTOR: 0xC*/
	*(uint32_t *)0x400FF0CC |= 1 << u8PinNumber;
	delay(time);

	*(uint32_t *)0x400FF0CC |= 1 << u8PinNumber;
}

int main(void) {

	/*Enable the clock for PORTD in the PCC register*/
	/*PCC base address: 0x40065000, offset for PORT_D: 0x130 */
    *(uint32_t *)0x40065130 |= (1u << 30);

    /*Configure Port Control Register as GPIO mode for pin 0, 15, 16, pin mux: 0b001*/
    /*PCR address for PORTD: 0x4004C00, offset for each pin: 4d * (pin_number)d */
    *(uint32_t *)0x4004C000 |= (1u << 8);
    *(uint32_t *)0x4004C03C |= (1u << 8);
    *(uint32_t *)0x4004C040 |= (1u << 8);

    /*Set the Port Data Direction Register (PDDR) in PORTD for pins 0, 15, and 16*/
    /*PORTD base address: 0x400FF0C0, offset for PDDR: 0x14*/
    *(uint32_t *)0x400FF0D4 |= (1<<0)|(1<<15)|(1<<16);

    /*Set output of pins 0, 15, and 16 to 1 using Port Set Output Register (PSOR)*/
    /*PORTD base address: 0x400FF0C0, offset for PSOR: 0x4 */
    *(uint32_t *)0x400FF0C4 |= (1<<0)|(1<<15)|(1<<16);


    while(1)
    {
    	blink_LED(0,3000000);
    	blink_LED(15,3000000);
    	blink_LED(16,3000000);

    }

    return 0;
}



