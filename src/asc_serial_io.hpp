/**
 * @file asc_serial_io.hpp
 * @author Alperen BAYRAMOĞLU
 * @date 2022
 *
 * @brief Initializing and communication with arduino on serial port.
 *
 */
#ifndef __ASC_SERIAL_IO_HPP
#define __ASC_SERIAL_IO_HPP

#include <termios.h>

/**
 * @brief ArduinoSerialControl Serial Input/Output
 */
class AscSerialIO {
	struct termios termios_protocol; /* Termios structure for config serial communication. */
	char *tty; /* TTY name of  serial device. */
	int fd = -1; /* File descriptor of serial device. */	
	
	public:
		AscSerialIO(char *tty_dev) : tty(tty_dev), termios_protocol {0} {}	
		~AscSerialIO();	
		bool initialize_communication(); /* Initialize serial communication. */
		void start_serial_reading(); /* Reads from serial device prints to screen. */
		void send_to_serial(const char *msg, int size);  /* Send message to serial device. */
};

#endif
