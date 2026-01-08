; USB Descriptors for Blink Example
; Based on fx2lib default descriptors

.module DEV_DSCR 

; descriptor types
DSCR_DEVICE_TYPE=1
DSCR_CONFIG_TYPE=2
DSCR_STRING_TYPE=3
DSCR_INTERFACE_TYPE=4
DSCR_ENDPOINT_TYPE=5
DSCR_DEVQUAL_TYPE=6

DSCR_INTERFACE_LEN=9
DSCR_ENDPOINT_LEN=7

ENDPOINT_TYPE_CONTROL=0
ENDPOINT_TYPE_ISO=1
ENDPOINT_TYPE_BULK=2
ENDPOINT_TYPE_INT=3

    .globl	_dev_dscr, _dev_qual_dscr, _highspd_dscr, _fullspd_dscr, _dev_strings, _dev_strings_end
    .area	DSCR_AREA	(CODE)

_dev_dscr:
	.db	dev_dscr_end-_dev_dscr
	.db	DSCR_DEVICE_TYPE
	.dw	0x0002					; usb 2.0
	.db	0xff  					; class (vendor specific)
	.db	0xff					; subclass (vendor specific)
	.db	0xff					; protocol (vendor specific)
	.db	64						; packet size (ep0)
	.dw	0xB404					; vendor id (Cypress)
	.dw	0x1386					; product id (8613 in little endian)
	.dw	0x0100					; version id
	.db	1		                ; manufacturer str idx				
	.db	2				        ; product str idx	
	.db	0				        ; serial str idx 
	.db	1			            ; n configurations
dev_dscr_end:

_dev_qual_dscr:
	.db	dev_qualdscr_end-_dev_qual_dscr
	.db	DSCR_DEVQUAL_TYPE
	.dw	0x0002
	.db	0xff
	.db	0xff
	.db	0xff
	.db	64
	.db	1
	.db	0
dev_qualdscr_end:

_highspd_dscr:
	.db	highspd_dscr_end-_highspd_dscr
	.db	DSCR_CONFIG_TYPE
	.dw	(highspd_dscr_realend-_highspd_dscr) & 0xff
	.dw	(highspd_dscr_realend-_highspd_dscr) >> 8
	.db	1		; n interfaces
	.db	1		; config number
	.db	0		; config string
	.db	0x80	; attrs (bus powered)
	.db	0x32	; max power (100ma)
highspd_dscr_end:

; interface 0
	.db	DSCR_INTERFACE_LEN
	.db	DSCR_INTERFACE_TYPE
	.db	0		; interface number
	.db	0		; alternate setting
	.db	0		; n endpoints (none for this simple example)
	.db	0xff	; class (vendor specific)
	.db	0xff	; subclass
	.db	0xff	; protocol
	.db	0		; string index	

highspd_dscr_realend:

_fullspd_dscr:
	.db	fullspd_dscr_end-_fullspd_dscr
	.db	DSCR_CONFIG_TYPE
	.dw	(fullspd_dscr_realend-_fullspd_dscr) & 0xff
	.dw	(fullspd_dscr_realend-_fullspd_dscr) >> 8
	.db	1		; n interfaces
	.db	1		; config number
	.db	0		; config string
	.db	0x80	; attrs (bus powered)
	.db	0x32	; max power (100ma)
fullspd_dscr_end:

; interface 0
	.db	DSCR_INTERFACE_LEN
	.db	DSCR_INTERFACE_TYPE
	.db	0		; interface number
	.db	0		; alternate setting
	.db	0		; n endpoints
	.db	0xff	; class (vendor specific)
	.db	0xff	; subclass
	.db	0xff	; protocol
	.db	0		; string index	

fullspd_dscr_realend:

_dev_strings:

; string 0 (language)
string0:
	.db	string0end-string0
	.db	DSCR_STRING_TYPE
	.db	0x09, 0x04	; 0x0409 is English (United States)
string0end:

; string 1 (manufacturer)
string1:
	.db	string1end-string1
	.db	DSCR_STRING_TYPE
	.ascii	'f'
	.db	0
	.ascii	'x'
	.db	0
	.ascii	'2'
	.db	0
	.ascii	'l'
	.db	0
	.ascii	'i'
	.db	0
	.ascii	'b'
	.db	0
string1end:

; string 2 (product)
string2:
	.db	string2end-string2
	.db	DSCR_STRING_TYPE
	.ascii	'B'
	.db	0
	.ascii	'l'
	.db	0
	.ascii	'i'
	.db	0
	.ascii	'n'
	.db	0
	.ascii	'k'
	.db	0
	.ascii	' '
	.db	0
	.ascii	'L'
	.db	0
	.ascii	'E'
	.db	0
	.ascii	'D'
	.db	0
string2end:

_dev_strings_end:
	.dw	0x0000
