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

#ifndef BEAGLEDIGITAL_H_
#define BEAGLEDIGITAL_H_

#include "beagleGPIO.h"

enum PIN_VALUE {
	LOW		= 0,
	HIGH	= 1
};

enum PIN_DIRECTION {
	INPUT_PIN,
	OUTPUT_PIN
};

enum PIN_EDGE {
	NONE,
	RISING_EDGE,
	FALLING_EDGE,
	BOTH_EDGES
};

// GPIO Directories
#define	FS_VALUE_DIR	"/sys/class/gpio/gpio%d/value"
#define FS_DIR_DIR		"/sys/class/gpio/gpio%d/direction"
#define FS_EDGE_DIR		"/sys/class/gpio/gpio%d/edge"
#define FS_EXPORT_DIR	"/sys/class/gpio/export"
#define FS_UNEXPORT_DIR	"/sys/class/gpio/unexport"

class beagleDigital: public beagleGPIO {
private:
	int			_index;
	bool		_exported;

protected:

public:
	// Constructor & Deconstructor
		 	 	 beagleDigital(const char *id, const int index) : beagleGPIO(id), _index(index), _exported(false) {}
		 	 	~beagleDigital();

	// Pin Open and close functions
	int	 		 openPin(const int flags);
	void 		 closePin();

	// Read and write functions
	void		 readPin(bool *value);
	bool		 readPin();

	void		 writePin(bool value);

	// Pin settings functions
	int		 	 setDirection(PIN_DIRECTION);
//	void 		 getDirection();

	int 		 setEdge(PIN_EDGE);
//	void		 getEdge();

	// Pin export and unexport functions
	int	 		 exportPin();
	int  		 unexportPin();

	bool		 isExported();
};

#endif /* BEAGLEDIGITAL_H_ */
