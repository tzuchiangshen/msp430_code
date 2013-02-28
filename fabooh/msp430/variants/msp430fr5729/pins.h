/*
  * pins.h - msp430g2231 GPIO port and pins
 *
 * Created: Nov 20, 2012
 *  Author: rick@kimballsoftware.com
 *    Date: 11-20-2012
 * Version: 1.0.0
 *
 * Note: this file a work in progress ...
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

#ifndef MSP430FR5739_NOBOARD_H_
#define MSP430FR5739_NOBOARD_H_

/*
 * P1 port and P1.X shorthand typedefs
 */
#ifdef __MSP430_HAS_PORT1_R__
 typedef GPIO_PORT<
         PAIN_L
         ,PAOUT_L
         ,PADIR_L
         ,PAIFG_L
         ,PAIES_L
         ,PAIE_L
         ,PASEL0_L
         ,PASEL1_L
         ,PAREN_L
         > P1;

 typedef GPIO_PIN<BIT0,P1> P1_0;
 typedef GPIO_PIN<BIT1,P1> P1_1;
 typedef GPIO_PIN<BIT2,P1> P1_2;
 typedef GPIO_PIN<BIT3,P1> P1_3;
 typedef GPIO_PIN<BIT4,P1> P1_4;
 typedef GPIO_PIN<BIT5,P1> P1_5;
 typedef GPIO_PIN<BIT6,P1> P1_6;
 typedef GPIO_PIN<BIT7,P1> P1_7;

 typedef GPIO_PIN<BIT0,P1> RED_LED;
 typedef GPIO_PIN<BIT6,P1> GREEN_LED;
 typedef GPIO_PIN<BIT3,P1> PUSH2;

#endif

/*
 * P2 port and P2.X shorthand typedefs
 */
#ifdef __MSP430_HAS_PORT2_R__

 typedef GPIO_PORT<
         PAIN_H
         ,PAOUT_H
         ,PADIR_H
         ,PAIFG_H
         ,PAIES_H
         ,PAIE_H
         ,PASEL0_H
         ,PASEL1_H
         ,PAREN_H
         > P2;

 typedef GPIO_PIN<BIT0,P2> P2_0;
 typedef GPIO_PIN<BIT1,P2> P2_1;
 typedef GPIO_PIN<BIT2,P2> P2_2;
 typedef GPIO_PIN<BIT3,P2> P2_3;
 typedef GPIO_PIN<BIT4,P2> P2_4;
 typedef GPIO_PIN<BIT5,P2> P2_5;
 typedef GPIO_PIN<BIT6,P2> P2_6;
 typedef GPIO_PIN<BIT7,P2> P2_7;

#endif

 /*
  * P3 port and P3.X shorthand typedefs
  */
 #ifdef __MSP430_HAS_PORT3_R__
 typedef GPIO_PORT<
         PBIN_L
         ,PBOUT_L
         ,PBDIR_L
         ,PBIFG_L
         ,PBIES_L
         ,PBIE_L
         ,PBSEL0_L
         ,PBSEL1_L
         ,PBREN_L
         > P3;

 typedef GPIO_PIN<BIT0,P3> P3_0;
 typedef GPIO_PIN<BIT1,P3> P3_1;
 typedef GPIO_PIN<BIT2,P3> P3_2;
 typedef GPIO_PIN<BIT3,P3> P3_3;
 typedef GPIO_PIN<BIT4,P3> P3_4; // SMCLK
 typedef GPIO_PIN<BIT5,P3> P3_5;
 typedef GPIO_PIN<BIT6,P3> P3_6;
 typedef GPIO_PIN<BIT7,P3> P3_7;

 #endif
#endif /* MSP430FR5739_NOBOARD_H_ */
