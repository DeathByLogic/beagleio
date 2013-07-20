/*
 * beagleSerial.cpp
 *
 *  Created on: Mar 29, 2013
 *      Author: daniel@deathbylogic.com
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "beagleSerial.h"

using namespace std;

/*
 * Constructor
 */

beagleSerial::beagleSerial(const char *ttyDir) {
	tty = ttyDir;
}

beagleSerial::~beagleSerial() {
	if (fd > 0) {
		closePort();
	}
}

/*
 * Serial Function
 */

// Read a string from the serial port
int beagleSerial::readString(void *buf, int count) {
	int rc;

	if (fd <= 0) {
		perror("BeagleSerial: Serial port has not been opened");
	} else {
		// Read from buffer
		if ((rc = read(fd, buf, count)) < 0) {
			perror("BeagleSerial: Unable to read from port ");
		}
	}

	return rc;
}

// Write a string to the serial port
int beagleSerial::writeString(const void *buf, int count) {
	int rc;

	if (fd <= 0) {
		perror("BeagleSerial: Serial port has not been opened");
	} else {
		// Write string to buffer
		if ((rc = write(fd, buf, count)) < 0) {
			perror("BeagleSerial: Unable to write to port ");
		}
	}

	return rc;
}

// Open the serial port and configure settings
void beagleSerial::openPort(BAUD baud_rate, PARITY_BIT parity_bit, BYTE_SIZE byte_size, STOP_BIT stop_bit) {
	int rc;

	// Open the file for write only
	if ((rc = open(tty, O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
		perror("BeagelSerial: Unable to open file ");
	} else {
		fd = rc;
	}

	// Set the port configuration
	configPort(baud_rate, parity_bit, byte_size, stop_bit);
}

// Close the serial port
void beagleSerial::closePort() {
	int rc;

	// Close the file
	if ((rc = close(fd)) < 0) {
		perror("BeagleSerial: Unable to close file ");
	} else {
		fd = 0;
	}
}

// Configure the serial port settings
void beagleSerial::configPort(BAUD baud_rate, PARITY_BIT parity_bit, BYTE_SIZE byte_size, STOP_BIT stop_bit) {
	struct termios options;

	// Configure port reading
	fcntl(fd, F_SETFL, FNDELAY);

	// Get the current options for the port
	tcgetattr(fd, &options);

	// Set the Tx and Rx baud rates
	cfsetispeed(&options, baud_rate);
	cfsetospeed(&options, baud_rate);

	// Enable the receiver and set local mode
	options.c_cflag |= (CLOCAL | CREAD);

	// Mask previous settings
	options.c_cflag &= ~(PARENB | PARODD | CSTOPB | CSIZE);

	// Configure new settings
	options.c_cflag |= byte_size;
	options.c_cflag |= parity_bit;
	options.c_cflag |= stop_bit;

	// Disable hardware flow control
	options.c_cflag &= ~CRTSCTS;

	// Enable data to be processed as raw input
	options.c_lflag &= ~(ICANON | ECHO | ISIG | ONLCR | OCRNL | ECHONL | IEXTEN);
	options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	options.c_oflag &= ~OPOST;

	// Set the new for the port
	tcsetattr(fd, TCSANOW, &options);
}
