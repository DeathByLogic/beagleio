/*
 * beagleDigital.cpp
 *
 *  Created on: Jul 20, 2013
 *      Author: daniel
 */

#include <cstdio>
#include <fcntl.h>
#include <cstring>

#include "beagleGPIO.h"
#include "beagleDigital.h"

/*
 * Deconstructor
 */

beagleDigital::~beagleDigital() {
	if (_exported == true) {
		unexportPin();
	}
}

/*
 * Export and Unexport functions
 */

// Export the GPIO pin
int beagleDigital::exportPin() {
	int rc;
	int	fd;

	int buf_length;
	char buf[MAX_BUFF];

	// Attempt to open file for write only
	if ((fd = gpioOpen(FS_EXPORT_DIR, O_WRONLY)) < 0) {
		return fd;
	} else {
		buf_length = snprintf(buf, sizeof(buf), "%d", _index);

		// Write pin number to export file
		if ((rc = gpioWrite(fd, buf, buf_length)) < 0) {
			perror("BeagleIO: Unable to export pin ");
		} else {
			_exported = true;

			printf("BeagleIO: Exported gpio %d\t(%s)\n", _index, _id);
		}

		// Close export file
		if ((rc = gpioClose(fd)) < 0) {
			return rc;
		}

		return 0;
	}
}

// Unexport the GPIO pin
int beagleDigital::unexportPin() {
	int rc;
	int	fd;
	int buf_length;
	char buf[MAX_BUFF];

	// Open file for write only
	if ((fd = gpioOpen(FS_UNEXPORT_DIR, O_WRONLY)) < 0) {
		return fd;
	} else {
		buf_length = snprintf(buf, sizeof(buf), "%d", _index);

		// Write pin to unexport file
		if ((rc = gpioWrite(fd, buf, buf_length)) < 0) {
			perror("BeagleIO: Unable to unexport pin ");
		} else {
			_exported =  false;

			printf("BeagleIO: Unexported gpio %d\t(%s)\n", _index, _id);
		}

		// Close File
		if ((rc = gpioClose(fd)) < 0) {
			return rc;
		}

		return 0;
	}
}

// Return true is pin has been exported
bool beagleDigital::isExported() {
	return _exported;
}

/*
 * Virtual open & close functions from beagleGPIO
 */

// Open pin file and return file descriptor
int beagleDigital::openPin(const int flags) {
	char buf[MAX_BUFF];

	if (!isPinOpen()) {
		if (_exported == false) {
			fprintf(stderr, "BeagleIO: Pin %s has not been exported\n", _id);
		} else {
			snprintf(buf, sizeof(buf), FS_VALUE_DIR, _index);

			// Open the file location
			_fd = gpioOpen(buf, flags);
		}
	}

	return _fd;
}

// Close the pin file
void beagleDigital::closePin() {
	if (isPinOpen()) {
		if(gpioClose(_fd) == 0) {
			_fd = 0;
		}
	}
}

/*
 * Configure Pin Settings
 */

// Set direction of pin
int beagleDigital::setDirection(PIN_DIRECTION direction) {
	int fd;
	int rc;

	char buf[MAX_BUFF];
	char dir[MAX_BUFF];

	if (_exported == false) {
		fprintf(stderr, "BeagleIO: Pin %s has not been exported\n", _id);

		return -1;
	} else {
		snprintf(buf, sizeof(buf), FS_DIR_DIR, _index);

		// Open the file location
		if ((fd = gpioOpen(buf, O_WRONLY)) < 0) {
			return fd;
		} else {
			// Write direction string to array
			switch (direction) {
			case INPUT_PIN:
				strcpy(dir, "in");

				break;
			case OUTPUT_PIN:
				strcpy(dir, "out");

				break;
			}

			// Write direction to file
			if ((rc = gpioWrite(fd, dir, sizeof(dir))) < 0) {
				perror("BeagleIO: Unable to set direction ");
			}

			// Close the file location
			if ((rc = gpioClose(fd)) < 0) {
				return rc;
			}
		}
	}

	return 0;
}

// Set Pin edge trigger
int beagleDigital::setEdge(PIN_EDGE edge) {
	int fd;
	int rc;

	char buf[MAX_BUFF];
	char edg[MAX_BUFF];

	if (_exported == false) {
		fprintf(stderr, "BeagleIO: Pin %s has not been exported\n", _id);

		return -1;
	} else {
		snprintf(buf, sizeof(buf), FS_EDGE_DIR, _index);

		// Open the file location
		if ((fd = gpioOpen(buf, O_WRONLY)) < 0) {
			return fd;
		} else {
			// Write direction to array
			switch (edge) {
			case NONE:
				strcpy(edg, "none");

				break;
			case RISING_EDGE:
				strcpy(edg, "rising");

				break;
			case FALLING_EDGE:
				strcpy(edg, "falling");

				break;
			case BOTH_EDGES:
				strcpy(edg, "both");

				break;
			}

			// Write edge to file
			if ((rc = gpioWrite(fd, edg, sizeof(edg))) < 0) {
				perror("BeagleIO: Unable to set edge ");
			}

			// Close the file location
			if ((rc = gpioClose(fd)) < 0) {
				return rc;
			}
		}
	}

	return 0;
}

/*
 * Read & Write pin value
 */

// Read pin value and write to pointer
void beagleDigital::readPin(bool *value) {
	int	rc;
	int rtn;

	// Export pin if needed
	if (_exported == false) {
		fprintf(stderr, "BeagleIO: Pin %s has not been exported\n", _id);
	} else {
		// Open the file location
		if ((rc = openPin(O_RDONLY | O_NONBLOCK)) > 0) {
			// Read the value of pin
			gpioRead(_fd, &rtn);

			*value = (bool)rtn;

			// Close the file location
			closePin();
		}
	}
}

// Read the value as pass back as return value
bool beagleDigital::readPin() {
	bool tmpValue;

	readPin(&tmpValue);

	return tmpValue;
}

void beagleDigital::writePin(bool value) {
	int rc;

	if (_exported == false) {
		fprintf(stderr, "BeagleIO: Pin %s has not been exported\n", _id);
	} else {
		// Open the file location
		if ((rc = openPin(O_WRONLY)) > 0) {
			// Seek to beginning

			// Write the value of pin
			gpioWrite(_fd, value);

			// Close the file location
			closePin();

			//rsync();
		}
	}
}
