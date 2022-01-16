/**
 * @file arduino_serial_communication.cc
 * @author Alperen BAYRAMOĞLU
 * @date 2022
 *
 * Serial command parsing & communication example.
 */
#include "Arduino.h"

/* Buffer coming from serial port */
char buffer[256];

/* Turn on the led */
char command_ledon[] = "ledon"; 
int command_ledon_size = 5;

/* Turn off the led */
char command_ledoff[] = "ledoff";
int command_ledoff_size = 6;
/*
 * Clear buffer
 */
void 
clear_buffer(char *bp, int size)
{
	if(size > 0) {
		int i;
		for(i = 0; i < size; i++)
			bp[i] = '\0';		
	}
}

/*
 * Check if string are equal
 * @returns 0 on equality
 * @returns 1 on non-equality
 */
int
string_compare(char *src, char *dst, int siz)
{
	int i;
	for(i = 0; i < siz; i++) {
		if(src[i] != dst[i])
			return 0;	
	}
	return 1;
}

/*
 * Processing coming command from serial
 */
void
process_command(char *bp, int size)
{
	if(size == command_ledon_size && string_compare(bp, command_ledon, size)) {
		digitalWrite(8, HIGH); /* Write 8 to HIGH */
	} else if(size == command_ledoff_size && string_compare(bp, command_ledoff, size)) {
		digitalWrite(8, LOW); /* Write 8 to LOW */
	}	
}

/*
 * Setup arduino
 */
void
setup()
{
	Serial.begin(115200); /* 115200 baud rate. */
	Serial.println("Arduino started"); 
	pinMode(8, OUTPUT); /* For led commands. */
	pinMode(9, OUTPUT); /* Command indicator. */
}

/*
 * Main loop
 */
void 
loop() 
{
	int read_bytes = 0;	
	if(Serial.available() > 0) {
		read_bytes = Serial.readBytes(buffer,256);	
		Serial.print("\nI received your message good luck: ");
		Serial.println(buffer); 	
		process_command(buffer, read_bytes); /* Process command. */	
		clear_buffer(buffer, read_bytes); /* Clear the buffer. */	
		digitalWrite(9, HIGH); /* Turn on indicator */
		delay(100);	
	}
	digitalWrite(9, LOW);
}

