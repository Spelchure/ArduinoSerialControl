/**
 * @file asc_pipe_io.cc
 * @author Alperen BAYRAMOĞLU
 * @date 2022
 *
 * @brief Reading from named pipe and sending commands to arduino through AscSerialIO
 *
 */
#include "asc_pipe_io.hpp"
#include <iostream>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <thread>
#include <cstring>

AscPipeIO::~AscPipeIO() 
{
	/* Remove pipe file. */	
	if(this->pipe_fd != -1) {
		std::remove(this->pipe_filename);
		close(this->pipe_fd);
	}	
}

/**
 * @brief Initialize named pipe.
 *
 * If named pipefile exist it will be deleted !
 *
 * @param serial Serial communication interface.
 */
bool 
AscPipeIO::initialize_pipe(AscSerialIO *serial)
{
	struct stat pipe_stat;

	/* Check file exist. */
	if(stat(this->pipe_filename, &pipe_stat) == 0)
		std::remove(this->pipe_filename);

	if(mkfifo(this->pipe_filename, 0666) < 0) 
		return false; /* Cannot create pipe file. */	

	this->serial = serial;
	return true;	
}

/**
 * @brief Thread for reading message from named pipe.
 */
void 
AscPipeIO::start_pipe_reading()
{
	char buf[256] { 0 };
	int count = 0;	

	using namespace std::chrono_literals;
		
	this->pipe_fd = open(this->pipe_filename, O_RDONLY);
	if(this->pipe_fd == -1)
		return; /* Cannot open pipe file. */
	
	while(true) {
		if((count = read(this->pipe_fd, buf, 256)) > 0) {
			if(std::string(buf) == CLOSE_COMMAND) {
				std::cout << "\n[**] CLOSE COMMAND FROM PIPE BYE.\n";
				return;
			}	
			std::cout << "\n[**] MESSAGE FROM PIPE: " << buf << '\n';	
			if(this->serial) 
				this->serial->send_to_serial(buf, count); /* Send to serial. */
			
			std::memset(&buf, 0, count); /* Clear buffer. */	
		}
		std::this_thread::sleep_for(50ms);	
	}
}


