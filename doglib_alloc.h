/* doglib_alloc.h - v0.2 - passable allocator
 *
 * This software is dual-licensed to the public domain and under the
 * following license: you are granted a perpetual, irrevocable license
 * to copy, modify, publish, and distribute this file as you see fit.
 */

#ifndef DOGLIB_ALLOC_H
#define DOGLIB_ALLOC_H

#include <stdlib.h>

struct doglib_allocator_vtable {
  void *(*alloc)(void *, size_t);
  void *(*resize)(void *, void *, size_t);
  void (*free)(void *, void *);
};

struct doglib_allocator {
  void *ptr;
  const struct doglib_allocator_vtable *vtable;
};

extern struct doglib_allocator doglib_alloc_libc;

void *doglib_alloc(struct doglib_allocator, size_t);
void *doglib_resize(struct doglib_allocator, void *, size_t);
void doglib_free(struct doglib_allocator, void *);

#ifdef DOGLIB_IMPL

static void *doglib_libc_alloc(void *alloc_state, size_t size)
{
  return malloc(size);
}

static void *doglib_libc_resize(void *alloc_state, void *ptr, size_t size)
{
  return realloc(ptr, size);
}

static void doglib_libc_free(void *alloc_state, void *ptr)
{
  return free(ptr);
}

struct doglib_allocator_vtable doglib_alloc_vtable_libc = {
  .alloc = &doglib_libc_alloc,
  .resize = &doglib_libc_resize,
  .free = &doglib_libc_free
};

struct doglib_allocator doglib_alloc_libc = {
  .ptr = NULL,
  .vtable = &doglib_alloc_vtable_libc
};

void *doglib_alloc(struct doglib_allocator allocator, size_t size)
{
  return (allocator.vtable->alloc)(allocator.ptr, size);
}

void *doglib_resize(struct doglib_allocator allocator, void *ptr, size_t size)
{
  return (allocator.vtable->resize)(allocator.ptr, ptr, size);
}

void doglib_free(struct doglib_allocator allocator, void *ptr)
{
  return (allocator.vtable->free)(allocator.ptr, ptr);
}

#endif
#endif
