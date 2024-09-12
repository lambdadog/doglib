/* dog_page.h - cross-platform utilities for requesting OS pages

   FLAGS
     DOG_PAGE_STATIC
     DOG_PAGE_IMPL

   USAGE
     TODO
 */

#ifndef DOG_TYPES_H_DEFS
#  include "dog_types.h"
#endif

#ifdef DOG_PAGE_STATIC
#  define DOG_PAGE_IMPL
#  define DOGDEF static
#else
#  define DOGDEF extern
#endif

#ifndef DOG_PAGE_H_DEFS
#define DOG_PAGE_H_DEFS

typedef struct DogPageChunk {
  void *addr;
  usize count;
} DogPageChunk;

DOGDEF usize dog_page_getPageSize(void);
DOGDEF DogPageChunk dog_page_getChunk(usize, void *, usize);
DOGDEF bool dog_page_returnChunk(usize, DogPageChunk *);

#endif  /* !DOG_PAGE_H_DEFS */

#undef DOGDEF

#if defined(DOG_PAGE_IMPL) && !defined(DOG_PAGE_H_IMPL)
#define DOG_PAGE_H_IMPL

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define DOG_PAGE_PLATFORM_WINDOWS
#elif __APPLE__
#  error "dog_page.h: apple platforms not currently supported"
#elif __linux
#  define DOG_PAGE_PLATFORM_LINUX
#else
#  error "dog_page.h: unknown platform not currently supported"
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DOG_PAGE_PLATFORM_WINDOWS
#  include <memoryapi.h>
#  include <sysinfoapi.h>
#endif

#ifdef DOG_PAGE_PLATFORM_LINUX
#  include <sys/mman.h>
#  include <unistd.h>
#endif

usize
dog_page_getPageSize(void)
{
#ifdef DOG_PAGE_PLATFORM_WINDOWS
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);

  return (usize)sysinfo.dwPageSize;
#elif defined(DOG_PAGE_PLATFORM_LINUX)
  isize m_page_size = sysconf(_SC_PAGESIZE);

  if (m_page_size <= 0)
    return 0;

  return (usize)m_page_size;
#endif
}

DogPageChunk
dog_page_getChunk(usize page_size, void *addr, usize count)
{
  usize length;
  DogPageChunk res = {0};

  /* Is there a way we can make this overflow check cheaper? */
  if (count && page_size > USIZE_MAX/count)
    return res;

  length = page_size * count;

#ifdef DOG_PAGE_PLATFORM_WINDOWS
  void *m_addr = VirtualAlloc(addr, length,
                              MEM_COMMIT | MEM_RESERVE,
                              PAGE_READWRITE);
#elif defined(DOG_PAGE_PLATFORM_LINUX)
  int flags = MAP_ANONYMOUS | MAP_PRIVATE;

  if (addr != NULL)
    flags |= MAP_FIXED;

  void *m_addr = mmap(addr, length, PROT_READ | PROT_WRITE, flags, -1, 0);
  if (m_addr == MAP_FAILED)
    return res;
#endif

  res.addr = m_addr;
  res.count = count;
  return res;
}

bool
dog_page_returnChunk(usize page_size, DogPageChunk *pages)
{
  bool res;

#ifdef DOG_PAGE_PLATFORM_WINDOWS
  res = VirtualFree(pages->addr, 0, MEM_RELEASE);
#elif defined(DOG_PAGE_PLATFORM_LINUX)
  usize length = page_size * pages->count;

  /* munmap returns -1 on failure, 0 on success */
  res = (bool)(munmap(pages->addr, length) + 1);
#endif

  if (res)
    pages->addr = NULL;

  return res;
}

#endif  /* DOG_PAGE_IMPL && !DOG_PAGE_H_IMPL */
