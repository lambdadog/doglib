/* dog_alloc.h - implementation of passable allocators

   USAGE
     For now, see allockit.h USAGE section. Documentation to come.

     https://github.com/lambdadog/allockit/blob/fcf6c122534d3e71e2a597ed2cc292fe8fee729a/allockit.h

   LICENSE
     SPDX-License-Identifier: Unlicense OR MIT

     See end of file for more detail.

 */

#ifndef DOG_ALLOC_H_DEFS
#define DOG_ALLOC_H_DEFS

#include <stdalign.h>
#include <stddef.h>

typedef struct DogAlloc {
  void *(*alloc)(struct DogAlloc *, size_t, size_t, size_t);
  int (*resize)(struct DogAlloc *, void *, size_t, size_t, size_t);
  void (*free)(struct DogAlloc *, void *);
} DogAlloc;

#define dog_alloc(pAlloc, Size, Align, Count) \
  (((pAlloc)->alloc)(pAlloc, Size, Align, Count))
#define dog_alloc(pAlloc, T, Count) \
  dog_alloc(pAlloc, sizeof(T), alignof(T), Count)

#define dog_resize(pAlloc, Addr, Size, Align, Count) \
  (((pAlloc)->resize)(pAlloc, Addr, Size, Align, Count))
#define dog_resize(pAlloc, Addr, T, Count) \
  dog_resize(pAlloc, Addr, sizeof(T), alignof(T), Count)

#define dog_free(pAlloc, Addr) \
  (((pAlloc)->free)(pAlloc, Addr))

#endif  /* !DOG_AK_H_DEFS */

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
