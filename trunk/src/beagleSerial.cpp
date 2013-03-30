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

	configPort(0);
}

beagleSerial::~beagleSerial() {
	if (fd > 0) {
		closePort();
	}
}

/*
 * Serial Function
 */

int beagleSerial::readString(char *buf, int count) {
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

int beagleSerial::writeString(const char *buf, int count) {
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

void beagleSerial::openPort() {
	int rc;

	// Open the file for write only
	if ((rc = open(tty, O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
		perror("BeagelSerial: Unable to open file ");
	} else {
		fd = rc;
	}
}

void beagleSerial::openPort(int flags) {
	// Opent the serial port
	openPort();

	// Set the port configuration
	configPort(flags);
}

void beagleSerial::closePort() {
	int rc;

	// Close the file
	if ((rc = close(fd)) < 0) {
		perror("BeagleSerial: Unable to close file ");
	} else {
		fd = 0;
	}
}

void beagleSerial::configPort(int flags) {
	struct termios options;

	fcntl(fd, F_SETFL, FNDELAY); /* Configure port reading */

	tcgetattr(fd, &options); /* Get the current options for the port */

	cfsetispeed(&options, B9600); /* Set the baud rates to 9600 */
	cfsetospeed(&options, B9600);

	options.c_cflag |= (CLOCAL | CREAD); /* Enable the receiver and set local mode */
	options.c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8; /* Select 8 data bits */
	options.c_cflag &= ~CRTSCTS; /* Disable hardware flow control */
	options.c_lflag &= ~(ICANON | ECHO | ISIG);/* Enable data to be processed as raw input */

	tcsetattr(fd, TCSANOW, &options); /* Set the new options for the port */
}
