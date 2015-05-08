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

#include "beagleBlackIO.h"

/*
 * BeagleBone Black P8 Header Pins
 */

beagleDigital P8_03("GPIO1_6",		38);
beagleDigital P8_04("GPIO1_7",		39);
beagleDigital P8_05("GPIO1_2",		34);
beagleDigital P8_06("GPIO1_3",		35);
beagleDigital P8_07("TIMER4",		66);
beagleDigital P8_08("TIMER7",		67);
beagleDigital P8_09("TIMER5",		69);
beagleDigital P8_10("TIMER6",		68);
beagleDigital P8_11("GPIO1_13",		45);
beagleDigital P8_12("GPIO1_12",		44);
beagleDigital P8_13("EHRPWM2B",		23);
beagleDigital P8_14("GPIO0_26",		26);
beagleDigital P8_15("GPIO1_15",		47);
beagleDigital P8_16("GPIO1_14",		46);
beagleDigital P8_17("GPIO0_27",		27);
beagleDigital P8_18("GPIO2_1",		65);
beagleDigital P8_19("EHRPWM2A",		22);
beagleDigital P8_20("GPIO1_31",		63);
beagleDigital P8_21("GPIO1_30",		62);
beagleDigital P8_22("GPIO1_5",		37);
beagleDigital P8_23("GPIO1_4",		36);
beagleDigital P8_24("GPIO1_1",		33);
beagleDigital P8_25("GPIO1_0",		32);
beagleDigital P8_26("GPIO1_29",		61);
beagleDigital P8_27("GPIO2_22",		86);
beagleDigital P8_28("GPIO2_24",		88);
beagleDigital P8_29("GPIO2_23",		87);
beagleDigital P8_30("GPIO2_25",		89);
beagleDigital P8_31("UART5_CTSN",	10);
beagleDigital P8_32("UART5_RTSN",	11);
beagleDigital P8_33("UART4_RTSN",	9);
beagleDigital P8_34("UART3_RTSN",	81);
beagleDigital P8_35("UART4_CTSN",	8);
beagleDigital P8_36("UART3_CTSN",	80);
beagleSerial  P8_37("UART5_TXD",	78, 	"ttyO5");
beagleSerial  P8_38("UART5_RXD",	79,		"ttyO5");
beagleDigital P8_39("GPIO2_12",		76);
beagleDigital P8_40("GPIO2_13",		77);
beagleDigital P8_41("GPIO2_10",		74);
beagleDigital P8_42("GPIO2_11",		75);
beagleDigital P8_43("GPIO2_8",		72);
beagleDigital P8_44("GPIO2_9",		73);
beagleDigital P8_45("GPIO2_6",		70);
beagleDigital P8_46("GPIO2_7",		71);

/*
 * BeagleBone Black P9 Header Pins
 */

beagleSerial  P9_11("UART4_RXD",	30,		"ttyO4");
beagleDigital P9_12("GPIO1_28",		60);
beagleSerial  P9_13("UART4_TXD",	31,		"ttyO4");
beagleDigital P9_14("EHRPWM1A",		50);
beagleDigital P9_15("GPIO1_16",		48);
beagleDigital P9_16("EHRPWM1B",		51);
beagleDigital P9_17("I2C1_SCL",		5);
beagleDigital P9_18("I2C1_SDA",		4);
beagleDigital P9_19("I2C2_SCL",		13);
beagleDigital P9_20("I2C2_SDA",		12);
beagleSerial  P9_21("UART2_TXD",	3,		"ttyO2");
beagleSerial  P9_22("UART2_RXD",	2,		"ttyO2");
beagleDigital P9_23("GPIO1_17",		49);
beagleSerial  P9_24("UART1_TXD",	15,		"ttyO1");
beagleDigital P9_25("GPIO3_21",		88);
beagleSerial  P9_26("UART1_RXD",	14,		"ttyO1");
beagleDigital P9_27("GPIO3_19",		86);
beagleDigital P9_28("SPI1_CS0",		84);
beagleDigital P9_29("SPI1_D0",		82);
beagleDigital P9_30("SPI1_D1",		116);
beagleDigital P9_31("SPI1_SCLK",	110);
// Pin P9_32 is VDD_ADC
beagleAnalog  P9_33("AIN4",			"ANI4");
// Pin P9_34 is GNDA_ADC
beagleAnalog  P9_35("AIN6",			"AIN6");
beagleAnalog  P9_36("AIN5",			"AIN5");
beagleAnalog  P9_37("AIN2",			"AIN2");
beagleAnalog  P9_38("AIN3",			"AIN3");
beagleAnalog  P9_39("AIN0",			"AIN0");
beagleAnalog  P9_40("AIN1",			"AIN1");
beagleDigital P9_41("CLKOUT2",		20);
beagleDigital P9_42("GPIO0_7",		7);
