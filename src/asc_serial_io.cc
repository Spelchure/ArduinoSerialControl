/**
 * @file asc_serial_io.cc
 * @author Alperen BAYRAMOĞLU
 * @date 2022
 *
 * @brief Initializing and communication with arduino on serial port.
 *
 */
#include "asc_serial_io.hpp" 
#include <iostream>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <mutex>


extern bool communication_end;
extern std::mutex mtx_communication_end;

/**
 * @brief Initializes communication with serial port.
 *
 * Makes termios configuration.
 * Checks for device is a tty.
 * Opens serial device.
 * Sets baud rate.
 *
 * @return true if initialization success.
 * @return false if initialization fails.
 */ 
bool
AscSerialIO::initialize_communication()
{
	this->termios_protocol.c_iflag = 0;
	this->termios_protocol.c_oflag = 0;
	this->termios_protocol.c_cflag = CS8 | CREAD | CLOCAL;
	this->termios_protocol.c_lflag = 0;

	/* Non Blocking I/O */	
	this->termios_protocol.c_cc[VMIN] = 0;
	this->termios_protocol.c_cc[VTIME] = 0;

	if((this->fd = open(this->tty, O_RDWR | O_NONBLOCK)) < 0)
		return false; /* Cannot open tty. */
	
	if(!isatty(this->fd)) {
		close(this->fd);	
		return false; /* File is not tty. */	
	}

	/* Set baud rate to 115200. Arduino or serial device must be configured to 115200 baud rate.
	 * Serial.begin(115200);
	 */
	cfsetospeed(&this->termios_protocol, B115200);
	cfsetispeed(&this->termios_protocol, B115200);

	return tcsetattr(this->fd, TCSANOW, &this->termios_protocol) == 0;
}

/**
 * @brief Destructor
 */
AscSerialIO::~AscSerialIO()
{
	if(this->fd != -1)
		close(this->fd); /* If open close the device. */
}

/**
 * @brief Thread. Reads from serial port and prints to screen.
 */
void
AscSerialIO::start_serial_reading()
{
	using namespace std::literals::chrono_literals;
	char buf[256] { 0 };

	if(this->fd == -1)
		return; /* Device not opened ! */
	
	while(true) {
		/* Read to buffer from serial dev. */	
		if(read(this->fd, &buf, 256) > 0) {
			std::cout << "\n[*] MESSAGE FROM SERIAL DEVICE: " << buf << '\n';
			std::memset(&buf,0,256); /* Clear buffer. */	
		}
		mtx_communication_end.lock();
		if(communication_end) {
			mtx_communication_end.unlock();
			return;
		}
		mtx_communication_end.unlock();
				
		std::this_thread::sleep_for(50ms); /* Continue */	
	}
}

/**
 * @brief Sends command to serial device.
 *
 * @param msg Message to send.
 */
void
AscSerialIO::send_to_serial(const char*msg, int size)
{
	int written_bytes = 0;
	if(this->fd != -1) {
		written_bytes = write(this->fd, msg, size);
		std::cout << "\n[*] SEND MESSAGE TO SERIAL DEVICE: " << msg << '\n';
	}		
}
