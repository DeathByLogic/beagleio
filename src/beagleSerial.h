/*
 * beagleSerial.h
 *
 *  Created on: Mar 29, 2013
 *      Author: daniel@deathbylogic.com
 */

#ifndef BEAGLESERIAL_H_
#define BEAGLESERIAL_H_

using namespace std;

// Class definition
class beagleSerial {
public:
	beagleSerial(const char*);
	~beagleSerial();

	// Serial Functions
	int		readString(char*, int);
	int		writeString(const char*, int);
	void	openPort();
	void	openPort(int);
	void	closePort();
	void	configPort(int);

private:
	int		fd;
	const char	*tty;
};

#endif /* BEAGLESERIAL_H_ */
