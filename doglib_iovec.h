/* doglib_iovec.h - v0.1 - iovec structures
 *
 * This software is dual-licensed to the public domain and under the
 * following license: you are granted a perpetual, irrevocable license
 * to copy, modify, publish, and distribute this file as you see fit.
 */

#ifndef DOGLIB_IOVEC_H
#define DOGLIB_IOVEC_H

#include <stddef.h>

#define DOGLIB_STRLIT(s) (struct doglib_iovec){(s), sizeof(s) - 1}

struct doglib_iovec {
  char *ptr;
  size_t len;
};

#endif
