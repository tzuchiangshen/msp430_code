/**
 * ascii_table_extended.h - insertion operator stuff
 *
 * Author: rick@kimballsoftware.com
 * Date: 03-03-2013
 *
 */

#ifndef _ASCII_TABLE_EXT_H
#define _ASCII_TABLE_EXT_H
/*
 * print_t insertion operator support
 */
template<typename T>
inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

template<typename T>
struct _BASE {
  const T n;
  const base_e base;

  _BASE(const T _n, const base_e _base): n(_n), base(_base) {}
};

#define _RAW(n) _BASE<typeof((n))>(n,RAW)
#define _BIN(n) _BASE<typeof((n))>(n,BIN)
#define _OCT(n) _BASE<typeof((n))>(n,OCT)
#define _DEC(n) _BASE<typeof((n))>(n,DEC)
#define _HEX(n) _BASE<typeof((n))>(n,HEX)

template<typename T>
inline Print &operator <<(Print &obj, const _BASE<T> &arg) { obj.print(arg.n, arg.base); return obj; }

#endif
