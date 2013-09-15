/*
	Copyright (C) 2013 deathbylogic.com
	Author: daniel@deathbylogic.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "beagleSerial.h"

using namespace std;

/*
 * Constructor
 */

beagleSerial::~beagleSerial() {
	if (_tty_fd > 0) {
		closePort();
	}
}

/*
 * Open and close port functions
 */

// Open the serial port and configure settings
int beagleSerial::openPort(BAUD baud_rate, PARITY_BIT parity_bit, BYTE_SIZE byte_size, STOP_BIT stop_bit) {
	char buf[MAX_BUFF];

	// Open the file for read/write
	if (!isPortOpen()) {
		snprintf(buf, sizeof(buf), FS_SERIAL_DIR, _tty);

		if ((_tty_fd = gpioOpen(buf, O_RDWR | O_NOCTTY | O_NDELAY)) > 0) {
			// Set the port configuration
			configPort(baud_rate, parity_bit, byte_size, stop_bit);
		}
	}

	return _tty_fd;
}

// Close the serial port
void beagleSerial::closePort() {
	// Close the file
	if (isPortOpen()) {
		if (gpioClose(_tty_fd) == 0) {
			_tty_fd = 0;
		}
	}
}

// Return boolean on if the serial port is open
bool beagleSerial::isPortOpen() {
	if (_tty_fd > 0) {
		return true;
	} else {
		return false;
	}
}

// Configure the serial port settings
void beagleSerial::configPort(BAUD baud_rate, PARITY_BIT parity_bit, BYTE_SIZE byte_size, STOP_BIT stop_bit) {
	struct termios options;

	if (isPortOpen())  {
		// Configure port reading
		fcntl(_tty_fd, F_SETFL, FNDELAY);

		// Get the current options for the port
		tcgetattr(_tty_fd, &options);

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
		tcsetattr(_tty_fd, TCSANOW, &options);
	}
}

/*
 * Serial Function
 */

// Read a string from the serial port
void beagleSerial::readPort(void *str, unsigned int count) {
	int rc;

	if (!isPortOpen()) {
		perror("BeagleSerial: Serial port has not been opened");
	} else {
		// Read from buffer
		if ((rc = gpioRead(_tty_fd, str, count)) < 0) {
			perror("BeagleSerial: Unable to read from port ");
		}
	}
}

// Write a string to the serial port
void beagleSerial::writePort(const void *str, unsigned int count) {
	int rc;

	if (!isPortOpen()) {
		perror("BeagleSerial: Serial port has not been opened");
	} else {
		// Write string to buffer
		if ((rc = gpioWrite(_tty_fd, str, count)) < 0) {
			perror("BeagleSerial: Unable to write to port ");
		}
	}
}
