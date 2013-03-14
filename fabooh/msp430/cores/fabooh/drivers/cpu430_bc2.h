/*
 *  cpu430.h - msp430 BCS+ implementation
 *
 * Created: Dec 12, 2012
 *  Author: rick@kimballsoftware.com
 *    Date: 03-02-2013
 * Version: 1.0.1
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
 *
 */

#ifndef CPU430_H
#define CPU430_H

#include "cpu.h"

template <unsigned long FREQ=F_CPU>
struct cpu430_t {
	static const unsigned long MCLK_FREQ=FREQ;

  static void init_clock_impl(void) {
    if (MCLK_FREQ == 16000000) {
      #ifdef CALBC1_16MHZ_
      BCSCTL1 = CALBC1_16MHZ;
      DCOCTL = CALDCO_16MHZ;
      #else
      BCSCTL1 = 0x8F; // we provide some default values for an msp430g2231
      DCOCTL = 0x6F;  // TODO: each chip is different and needs to be calibrated
      #endif
    }
    else if (MCLK_FREQ == 12000000) {
      #ifdef CALBC1_12MHZ_
      BCSCTL1 = CALBC1_12MHZ;
      DCOCTL = CALDCO_12MHZ;
      #endif
    }
    else if (MCLK_FREQ == 8000000) {
      #ifdef CALBC1_8MHZ_
      BCSCTL1 = CALBC1_8MHZ;
      DCOCTL = CALDCO_8MHZ;
      #endif
    }
    else if (MCLK_FREQ == 1000000) {
      #ifdef CALBC1_1MHZ_
      BCSCTL1 = CALBC1_1MHZ;
      DCOCTL = CALDCO_1MHZ;
      #endif
    }
    else {
      // use default clock .. varies on each chip
    }
  }
};

typedef cpu_t<cpu430_t<F_CPU> > CPU;

#endif /* CPU430_H */
