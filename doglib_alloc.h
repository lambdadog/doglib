/* doglib_alloc.h - v0.1 - passable allocator
 *
 * This software is dual-licensed to the public domain and under the
 * following license: you are granted a perpetual, irrevocable license
 * to copy, modify, publish, and distribute this file as you see fit.
 */

#ifndef DOGLIB_ALLOC_H
#define DOGLIB_ALLOC_H

#include <stdlib.h>

struct doglib_allocator {
  void *(*alloc)(size_t);
  void *(*resize)(void *, size_t);
  void (*free)(void *);
};

extern struct doglib_allocator doglib_alloc_libc;

void *doglib_alloc(struct doglib_allocator *, size_t);
void *doglib_resize(struct doglib_allocator *, void *, size_t);
void doglib_free(struct doglib_allocator *, void *);

#ifdef DOGLIB_IMPL

struct doglib_allocator doglib_alloc_libc = {
  .alloc = &malloc,
  .resize = &realloc,
  .free = &free
};

void *doglib_alloc(struct doglib_allocator *allocator, size_t size)
{
  return (allocator->alloc)(size);
}

void *doglib_resize(struct doglib_allocator *allocator, void *ptr, size_t size)
{
  return (allocator->resize)(ptr, size);
}

void doglib_free(struct doglib_allocator *allocator, void *ptr)
{
  return (allocator->free)(ptr);
}

#endif
#endif
