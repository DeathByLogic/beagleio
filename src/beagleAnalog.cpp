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
#include <fcntl.h>

#include "beagleGPIO.h"
#include "beagleAnalog.h"

using namespace std;

/*
 * Virtual open & close functions from beagleGPIO
 */

int beagleAnalog::openPin(const int flags) {
	char buf[MAX_BUFF];

	if (!isPinOpen()) {
		snprintf(buf, sizeof(buf), FS_ANALOG_DIR, _ani);

		// Open the file location
		_fd = gpioOpen(buf, flags);
	}

	return _fd;
}

void beagleAnalog::closePin() {
	if (isPinOpen()) {
		if(gpioClose(_fd) == 0) {
			_fd = 0;
		}
	}
}

/*
 * Read pin value
 */

void beagleAnalog::readPin(int *value) {
	if (isPinOpen()) {
		// Read the value of pin
		gpioRead(_fd, value);
	} else if (openPin(O_RDONLY | O_NONBLOCK) > 0) {
		// Read the value of pin
		gpioRead(_fd, value);

		closePin();
	}
}

int beagleAnalog::readPin() {
	int tmpValue;

	readPin(&tmpValue);

	return tmpValue;
}

/*
 * Low level read
 */

//int beagleAnalog::gpioRead(int fd, int *value, int base) {
//	int rc;
//	char buf[MAX_BUFF];
//
//	// Seek to beginning
//	lseek(fd, 0, SEEK_SET);
//
//	// Read value of file
//	if ((rc = read(fd, buf, sizeof(buf))) < 0) {
//		perror("BeagleIO: Unable to read from file ");
//	} else {
//		*value = strtol(buf, NULL, base);
//	}
//
//	return rc;
//}
//
//int beagleAnalog::gpioRead(int fd, int *value) {
//	return gpioRead(fd, value, 0);
//}
