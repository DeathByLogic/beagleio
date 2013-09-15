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

#ifndef BEAGLEANALOG_H_
#define BEAGLEANALOG_H_

#include "beagleGPIO.h"

// GPIO Directories
#define FS_ANALOG_DIR	"/sys/devices/ocp.2/helper.9/%s"

class beagleAnalog: public beagleGPIO {
private:
	const char *_ani;

protected:

public:
				beagleAnalog(const char *id, const char *ani) : beagleGPIO(id), _ani(ani) {}

	void 		readPin(int *);
	int  		readPin();

	int			openPin(const int flags);
	void		closePin();
};

#endif /* BEAGLEANALOG_H_ */
