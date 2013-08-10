/*
 * beagleDigital.h
 *
 *  Created on: Jul 20, 2013
 *      Author: daniel
 */

#ifndef BEAGLEDIGITAL_H_
#define BEAGLEDIGITAL_H_

#include "beagleGPIO.h"

class beagleDigital: public beagleGPIO {
private:
	const char	*_mux;

protected:


public:
		 beagleDigital(const char *ID) : beagleGPIO(ID) {}

		~beagleDigital();

	int	 pinOpen();
	void pinClose();

	void setDirection(PIN_DIRECTION);
	void setEdge(PIN_EDGE);
	void getValue(bool *value);
	bool getValue();
	void setValue(bool value);

	void pinSetMux(PIN_MUX, PIN_PULLUP_EN = PULLUP_ENABLED, PIN_PULLUP = PULLDOWN, PIN_DIRECTION = OUTPUT_PIN, PIN_SLEW = FAST_SLEW);
	int	 pinExport();
	int  pinUnexport();

	void prnt(int value);
};

#endif /* BEAGLEDIGITAL_H_ */
