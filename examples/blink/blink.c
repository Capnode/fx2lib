// Blink two LEDs connected to Port A pins 0 and 1 alternately with 500ms delay
// with USB enumeration support for EEPROM booting
// Target Device: Cypress FX2LP (CY7C68013A)
//
// Build instructions:
//  make
//
// Program loading instructions:
//  Make sure WinUSB FX2 drivers are installed and fx2tool is available.
//  Make sure device appears in Device Manager under "Universal Serial Bus Devices"
//  Device VID:PID = 04b4:8613
// 
// Load and run program in RAM:
//  fx2tool -d 04b4:8613 load blink.ihx
//
// Write program to EEPROM:
//  python ../../../utils/ihx2iic.py -v 0x04b4 -p 0x8613 blink.ihx blink.iic
//  Insert jumper, start device, remove jumper
//  fx2tool -d 04b4:8613 -F bin -B write_eeprom -W 2 -f blink.iic
//  Press reset button to run from EEPROM - device should enumerate as "Blink LED"

#include <fx2regs.h>
#include <fx2macros.h>
#include <fx2ints.h>
#include <autovector.h>
#include <delay.h>
#include <setupdat.h>

volatile __bit dosud = FALSE;

// Stub functions for USB setup handlers (required by setupdat.c)
BOOL handle_vendorcommand(BYTE cmd) {
	return FALSE;
}

BOOL handle_get_interface(BYTE ifc, BYTE* alt_ifc) {
	*alt_ifc = 0;
	return TRUE;
}

BOOL handle_set_interface(BYTE ifc, BYTE alt_ifc) {
	return TRUE;
}

BOOL handle_get_configuration(void) {
	return TRUE;
}

BOOL handle_set_configuration(BYTE config) {
	return TRUE;
}

void handle_get_descriptor(void) {
	// Handled by setupdat.c using descriptor pointers
}

// USB interrupt handlers
void sudav_isr(void) __interrupt(SUDAV_ISR) {
	dosud = TRUE;
	CLEAR_SUDAV();
}

void usbreset_isr(void) __interrupt(USBRESET_ISR) {
	handle_hispeed(FALSE);
	CLEAR_USBRESET();
}

void hispeed_isr(void) __interrupt(HISPEED_ISR) {
	handle_hispeed(TRUE);
	CLEAR_HISPEED();
}

void main(void)
{
	// Set up USB interrupts first
	USE_USB_INTS();
	ENABLE_SUDAV();
	ENABLE_USBRESET();
	ENABLE_HISPEED();
	
	EA = 1;  // Enable global interrupts
	
	// Initialize USB with delay for stability
	// For EEPROM boot: disconnect and reconnect
	// For RAM load: just enable USB without disconnect
#ifndef NORENUM
	RENUMERATE();
#else
	USBCS &= ~bmDISCON;
#endif
	
	// Configure Port A pins 0 and 1 as outputs
	OEA = 0x03;  // 0b00000011 - PA0 and PA1 as outputs
	
	// Main loop - blink LEDs alternately
	while (1) {
		// Handle USB setup requests
		if (dosud) {
			dosud = FALSE;
			handle_setupdata();
		}
		
		// Turn on LED1 (PA0), turn off LED2 (PA1)
		IOA = 0x01;  // 0b00000001
		delay(500);  // 500ms delay
		
		// Turn off LED1 (PA0), turn on LED2 (PA1)
		IOA = 0x02;  // 0b00000010
		delay(500);  // 500ms delay
	}
}
