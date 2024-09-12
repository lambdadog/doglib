/* doglib_types.h - reusable C types

   FLAGS
     DOGLIB_TYPES_PREFIXED
       Prefixes all types with doglib_. Ideally wouldn't be used, but
       may be useful in the case of name collisions.

   USAGE
     Shorthand integer types
       doglib typedefs the following int types from <stdint.h> for
       ease-of-use purposes:
         - {u,}int{8,16,32,64}_t -> {u,i}{8,16,32,64}
	 - {u,}intptr_t          -> {u,i}size
       These conventions are largely inspired by Zig integer types,
       just without the arbitrary sizing.

     DOGLIB_TYPES_EQ macro
       Imperfect macro for checking type equality at
       compile-time. Does not work properly for list types or void.

     DOGLIB_TYPE macro
       Intended mostly for internal use, but may also be useful to
       libraries which depend on doglib. Depending on whether
       DOGLIB_TYPES_PREFIXED is defined, DOGLIB_TYPE(asdf) either
       evaluates to doglib_asdf or asdf.

   LICENSE
     SPDX-License-Identifier: Unlicense OR MIT

     See end of file for more detail.
*/

#ifndef DOGLIB_TYPES_H
#define DOGLIB_TYPES_H

#ifdef DOGLIB_TYPES_PREFIXED
#  define DOGLIB_TYPE(T) doglib_##T
#else
#  define DOGLIB_TYPE(T) T
#endif

#include <stdint.h>
#include <assert.h>

/* Re-export */
#include <stdbool.h>

#define DOGLIB_TYPES_EQ1(T1, T2) _Generic(((T1){0}), T2: 1, default: 0)
#define DOGLIB_TYPES_EQ(T1, T2) (DOGLIB_TYPES_EQ1(T1, T2) && DOGLIB_TYPES_EQ1(T2, T1))

static_assert(DOGLIB_TYPES_EQ(uintptr_t, size_t), "uintptr_t != size_t");

typedef    int8_t DOGLIB_TYPE( i8);
typedef   uint8_t DOGLIB_TYPE( u8);
typedef   int16_t DOGLIB_TYPE(i16);
typedef  uint16_t DOGLIB_TYPE(u16);
typedef   int32_t DOGLIB_TYPE(i32);
typedef  uint32_t DOGLIB_TYPE(u32);
typedef   int64_t DOGLIB_TYPE(i64);
typedef  uint64_t DOGLIB_TYPE(u64);
typedef  intptr_t DOGLIB_TYPE(isize);
typedef uintptr_t DOGLIB_TYPE(usize);

#define DOGLIB_I8_MIN  INT8_MIN
#define DOGLIB_I8_MAX  INT8_MAX
#define DOGLIB_U8_MAX UINT8_MAX

#define DOGLIB_I16_MIN  INT16_MIN
#define DOGLIB_I16_MAX  INT16_MAX
#define DOGLIB_U16_MAX UINT16_MAX

#define DOGLIB_I32_MIN  INT32_MAX
#define DOGLIB_I32_MAX  INT32_MAX
#define DOGLIB_U32_MAX UINT32_MAX

#define DOGLIB_I64_MIN  INT64_MIN
#define DOGLIB_I64_MAX  INT64_MAX
#define DOGLIB_U64_MAX UINT64_MAX

#define DOGLIB_ISIZE_MIN  INTPTR_MIN
#define DOGLIB_ISIZE_MAX  INTPTR_MAX
#define DOGLIB_USIZE_MAX UINTPTR_MAX
#endif

/*
  This software is available under 2 licenses, choose whichever you
  prefer:

  ALTERNATIVE A - Public Domain (www.unlicense.org)
    This is free and unencumbered software released into the public
    domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a
    compiled binary, for any purpose, commercial or non-commercial,
    and by any means.

    In jurisdictions that recognize copyright laws, the author or
    authors of this software dedicate any and all copyright interest
    in the software to the public domain. We make this dedication for
    the benefit of the public at large and to the detriment of our
    heirs and successors. We intend this dedication to be an overt act
    of relinquishment in perpetuity of all present and future rights
    to this software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org/>

  ALTERNATIVE B - MIT License
    Copyright (c) 2024 lambdadog

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/
