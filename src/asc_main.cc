/*
 * @file asc_main.cc
 * @author Alperen BAYRAMOĞLU
 * @date 2022
 *
 * @brief Application entry for arduino serial communication
 *
 */
#include "asc_serial_io.hpp"
#include "asc_pipe_io.hpp"
#include <iostream>
#include <thread>
#include <cstring>
#include <cerrno>

using namespace std;

/* Created pipe file name can be changed here. */
constexpr auto PIPE_FILENAME = "/tmp/arduinocommand";

int
main(int argc, char **argv)
{
	AscSerialIO *serial {nullptr}; 
	AscPipeIO *pipe {nullptr};

	if(argc < 2) {
		cout << "Usage: ./ArduinoSerialControl <tty>\n\tExample: ./ArduinoSerialControl /dev/ttyUSB0\n";
		return 1;
	}	

	serial = new AscSerialIO(argv[1]);
	
	if(!serial->initialize_communication()) {
		std::cerr << "Cannot initialize serial communication.\n\t" << strerror(errno) << '\n';
		if(serial)
			delete serial;
		return 1; /* Cannot initialize serial communication. */	
	}
	
	pipe = new AscPipeIO(PIPE_FILENAME);

	if(!pipe->initialize_pipe(serial)) {
		std::cerr << "Cannot initialize named pipe.\n\t" << strerror(errno) << '\n';
		if(serial)
			delete serial;
		if(pipe)
			delete pipe;
		return 1; /* Cannot initialize pipe communication. */	
	}

	std::thread serial_thread(&AscSerialIO::start_serial_reading, serial);
	std::thread pipe_thread(&AscPipeIO::start_pipe_reading, pipe);	

	std::cout << "\n[**] ArduinoSerialController started successfully.\n";

	pipe_thread.join();
	

	if(serial)
		delete serial;
	if(pipe)
		delete pipe;	

	return 0;
}
