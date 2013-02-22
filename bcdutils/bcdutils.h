/*
 * bcdutils.h - convert from decimal to bcd routines
 *
 *  Author: kimballr
 *  Date: Feb 21, 2013
 *  Version: 1.00
 */

#ifndef BCDUTILS_H_
#define BCDUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

struct bcd16_t {
    uint8_t d0:4;
    uint8_t d1:4;
    uint8_t d2:4;
    uint8_t d3:4;
    uint8_t d4:4;
    uint8_t sign:4;
    uint8_t rsvd6:4;
    uint8_t rsvd7:4;
};

struct bcd32_t {
  uint8_t d0:4;
  uint8_t d1:4;
  uint8_t d2:4;
  uint8_t d3:4;
  uint8_t d4:4;
  uint8_t d5:4;
  uint8_t d6:4;
  uint8_t d7:4;
  uint8_t d8:4;
  uint8_t d9:4;
  uint8_t sign:4;
  uint8_t rsvd11:4;
  uint8_t rsvd12:4;
  uint8_t rsvd13:4;
  uint8_t rsvd14:4;
  uint8_t rsvd15:4;
};

long u16tobcd(unsigned);
long long u32tobcd(unsigned long);

#ifdef __cplusplus
}
#endif

#endif /* BCDUTILS_H_ */
