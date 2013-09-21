/*
 * main.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#include <beagleIO.h>

using namespace std;

int main() {

	/*
	 * Test Analog Read
	 */

	cout << "BeagleIO Analog Read" << endl;

	for (int i = 0; i < 10; i++) {
		cout << P9_39.readPin() << endl;

		sleep(1);
	}

	/*
	 * Test Digital Write
	 */

	cout << "BeagleIO Digital Write" << endl;

	P8_45.exportPin();

	P8_45.setDirection(OUTPUT_PIN);

	for (int j = 0; j < 10; j++) {
		P8_45.writePin(j%2);

		sleep(1);
	}

	P8_45.unexportPin();

	/*
	 * Test Digital Read
	 */

	cout << "BeagleIO Digital Read" << endl;

	P8_41.exportPin();

	P8_41.setDirection(INPUT_PIN);

	P8_41.openPin(O_RDONLY | O_NONBLOCK);

	for (int k = 0; k < 10; k++) {
		while (P8_41.readPin() == true) {
			sleep(1);
		}

		cout << "P8_41 pushed" << endl;

		while (P8_41.readPin() == false) {
			sleep(1);
		}

		cout << "P8_41 released" << endl;
	}

	P8_41.closePin();

	P8_41.unexportPin();

	/*
	 * Test Serial Read Write
	 */

	cout << "BeagleIO Serial Write" << endl;

	P8_37.exportPin();
	P8_37.setDirection(OUTPUT_PIN);

	P8_37.openPort(BR_57600);

	for (int m = 0; m < 20; m++) {
		P8_37.writePort("U",1);

		sleep(1);
	}

	P8_37.closePort();

	return 0;
}


