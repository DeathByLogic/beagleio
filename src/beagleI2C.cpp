/*
	Copyright (C) 2015 deathbylogic.com
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
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "beagleI2C.h"

/*
 * Constructor
 */

beagleI2C::~beagleI2C() {
	if (_i2c_fd > 0) {
		closePort();
	}
}

/*
 * Open and close port functions
 */

// Open the serial port and configure settings
int beagleI2C::openPort(int address) {
	char buf[MAX_BUFF];

	// Open the file for read/write
	if (!isPortOpen()) {
		snprintf(buf, sizeof(buf), FS_I2C_DIR, _i2c.c_str());

		if ((_i2c_fd = gpioOpen(buf, O_RDWR)) > 0) {
			// Set the port configuration
			if (ioctl(_i2c_fd, I2C_SLAVE, address) < 0) {
				perror("BeagleI2C: Unable to set slave I2C address");
			}
		}
	}

	return _i2c_fd;
}

// Close the serial port
void beagleI2C::closePort() {
	// Close the file
	if (isPortOpen()) {
		if (gpioClose(_i2c_fd) == 0) {
			_i2c_fd = 0;
		}
	}
}

// Return boolean on if the serial port is open
bool beagleI2C::isPortOpen() {
	if (_i2c_fd > 0) {
		return true;
	} else {
		return false;
	}
}

int beagleI2C::getPortFD() {
	return _i2c_fd;
}

/*
 * Low Level Serial Function
 */

// Read a string from the serial port
void beagleI2C::readPort(void *str, size_t size) {
	int rc;

	if (!isPortOpen()) {
		perror("BeagleI2C: I2C port has not been opened");
	} else {
		// Read from buffer
		if ((rc = gpioRead(_i2c_fd, str, size)) < 0) {
			perror("BeagleI2C: Unable to read from port ");
		}
	}
}

// Write a string to the serial port
void beagleI2C::writePort(const void *str, size_t size) {
	int rc;

	if (!isPortOpen()) {
		perror("BeagleI2C: I2C port has not been opened");
	} else {
		// Write string to buffer
		if ((rc = gpioWrite(_i2c_fd, str, size)) < 0) {
			perror("BeagleI2C: Unable to write to port ");
		}
	}
}

/*
 * High Level Serial Functions
 */

void beagleI2C::writeTo(const void *str, char address, size_t size) {
	if (isPortOpen()) {
		perror("BealgeI2C: I2C port is already in use");
	} else {
		if (openPort(address) > 0) {
			// Write data to device
			writePort(str, size);

			// Close the port
			closePort();
		}
	}
}

void beagleI2C::requestFrom(void *str, char address, size_t size, bool consecutively) {
	if (isPortOpen()) {
		perror("BealgeI2C: I2C port is already in use");
	} else {
		if (openPort(address) > 0) {
			if (consecutively) {
				for (unsigned int i = 0; i < size; i++) {
					readPort(str + i, 1);
				}
			} else {
				// Read data from device
				readPort(str, size);
			}

			// Close the port
			closePort();
		}
	}
}
