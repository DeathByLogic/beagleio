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

#include <cstring>
#include <cstdio>
#include "beagleGPIO.h"

// GPIO Directories
#define FS_ANALOG_DIR	"/sys/devices"

class beagleAnalog: public beagleGPIO {
private:
	std::string  _ani;
	char	 	 _dir[MAX_BUFF];

//	bool		 _ani_found;

protected:

public:
	// Constructor
				beagleAnalog(const std::string &id, const std::string &ani) : beagleGPIO(id), _ani(ani) {
					char ocp_dir[MAX_BUFF];

//					if (!_ani_found) {
						dirSearch(FS_ANALOG_DIR, "ocp", ocp_dir);
						dirSearch(ocp_dir, "helper", _dir);

						strncat(_dir, "/%s", sizeof(_dir));

//						_ani_found = true;

						perror(_dir);
//					}
				}

	// Read pin value functions
	void 		readPin(int *);
	int  		readPin();

	// Open and close pin functions
	int			openPin(const int flags);
	void		closePin();
};

#endif /* BEAGLEANALOG_H_ */
