/*
 * beagleAnalog.h
 *
 *  Created on: Sep 8, 2013
 *      Author: daniel
 */

#ifndef BEAGLEANALOG_H_
#define BEAGLEANALOG_H_

#include "beagleGPIO.h"

// GPIO Directories
#define FS_ANALOG_DIR	"/sys/devices/ocp.2/helper.9/AIN%d"

class beagleAnalog: public beagleGPIO {
private:
	const int	_index;

protected:

public:
				beagleAnalog(const char *id, const int index) : beagleGPIO(id), _index(index) {}

	void 		readPin(int *);
	int  		readPin();

	int			openPin(const int flags);
	void		closePin();
};

#endif /* BEAGLEANALOG_H_ */
