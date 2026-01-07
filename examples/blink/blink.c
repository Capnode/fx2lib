// Blink two LEDs connected to Port A pins 0 and 1 alternately with 500ms delay
// Target Device: Cypress FX2LP (CY7C68013A)
// Compile with: sdcc -mmcs51 --model-large -o blink.ihx
//  sdcc -mmcs51 -I../fx2lib/include --code-size 0x1c00 --xram-size 0x0200 --xram-loc 0x1c00 -o blink.ihx blink.c ../fx2lib/lib/delay.rel
//
// Load and run program in RAM:
//  fx2tool -d 04b4:8613 load blink.ihx

// Write program to EEPROM:
//  python ../../../utils/ihx2iic.py blink.ihx blink.iic
//  fx2tool -d 04b4:8613 -F bin -B write_eeprom -W 1 -f blink.iic

#include <fx2regs.h>
#include <fx2macros.h>
#include <delay.h>

void main(void)
{
	// Configure Port A pins 0 and 1 as outputs
	// OEA (Output Enable for Port A) - set bits 0 and 1 to output mode
	OEA = 0x03;  // 0b00000011 - PA0 and PA1 as outputs
	
	// Main loop - blink LEDs alternately
	while (1) {
		// Turn on LED1 (PA0), turn off LED2 (PA1)
		IOA = 0x01;  // 0b00000001
		delay(500);  // 500ms delay
		
		// Turn off LED1 (PA0), turn on LED2 (PA1)
		IOA = 0x02;  // 0b00000010
		delay(500);  // 500ms delay
	}
}
