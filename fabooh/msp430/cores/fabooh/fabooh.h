/*
 * fabooh.h - like Energia.h but not ...
 *
 * Created: Nov-12-2012
 *  Author: rick@kimballsoftare.com
 *    Date: 02-28-2013
 * Version: 1.0.0
 *
 * =========================================================================
 *  Copyright © 2013 Rick Kimball
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FABOOH_H_
#define FABOOH_H_

#ifdef __GNUC__
#define ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define ALWAYS_INLINE inline
#endif

#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "logic.h"
#ifdef __GNUC__
#include "ringbuffer.h"
#endif

#include "cpu.h"
#ifdef __MSP430_HAS_BC2__
#include "msp430/cpu430.h"
#else
#include "msp430/cpu430x.h"
#endif

#include "gpio.h"
#include <pins.h> // source by -I ${FABOOH_CORE}/variants/${BOARD}

#include "print.h"

void setup();
void loop();

#endif /* FABOOH_H_ */
