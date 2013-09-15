/*
 * beagleAnalog.c
 *
 *  Created on: Sep 8, 2013
 *      Author: daniel@deathbylogic.com
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
		snprintf(buf, sizeof(buf), FS_ANALOG_DIR, _index);

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
