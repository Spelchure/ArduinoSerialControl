/**
 * @file asc_pipe_io.hpp
 * @author Alperen BAYRAMOĞLU
 * @date 2022
 *
 * @brief Reading from named pipe and sending commands to arduino through AscSerialIO
 *
 */
#ifndef __ASC_PIPE_IO
#define __ASC_PIPE_IO

#include "asc_serial_io.hpp"

/* Close command for closing named pipe. */
constexpr auto CLOSE_COMMAND = "close";

/**
 * @brief PipeIO
 */
class AscPipeIO {
	const char * const pipe_filename; /* Pipe file name */
	int pipe_fd; /* Pipe file descriptor */
	AscSerialIO *serial; /* Serial interface. */	

	public:
		AscPipeIO(const char *const pipe) : pipe_filename(pipe) {}
		~AscPipeIO();
		bool initialize_pipe(AscSerialIO *serial); /* Initializes pipe. */
		void start_pipe_reading(); /* Starts reading from pipe. */
};

#endif
