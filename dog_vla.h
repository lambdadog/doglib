/* dog_vla.h - zig-style VLA (ArrayList) implementation */

/* Pending me implementing at least one allocator on top of
   dog_alloc.h... */
#error "dog_vla.h: WIP, not yet functional"

#ifndef DOG_TYPES_H_DEFS
#  include "dog_types.h"
#endif

#ifndef DOG_ALLOC_H_DEFS
#  error "dog_vla.h requires dog_alloc.h"
#  include "dog_alloc.h"
#endif

#ifdef DOG_VLA_STATIC
#  define DOG_VLA_IMPL
#  define DOGAPI static
#else
#  define DOGAPI extern
#endif

#ifndef DOG_VLA_H_DEFS
#define DOG_VLA_H_DEFS

#define DECLARE_DogVLA(T) \
  typedef struct DOG_VLA_##T { \
    T *ptr; \
    usize len; \
    usize step_size; \
    DogAlloc *alloc; \
  } DOG_VLA_##T

#define DogVLA(T) DOG_VLA_##T

#define dog_vla_sizeof(pVLA) (sizeof(typeof(&(pVLA)->ptr)))
#define dog_vla_alignof(pVLA) (alignof(typeof(&(pVLA)->ptr)))

#define dog_vla_initCustom(pVLA, Alloc, StepSize)       \
  (dog_vla_init_impl(pVLA, Alloc, StepSize,             \
                     dog_vla_sizeof(pVLA),              \
                     dog_vla_alignof(pVLA)))
#define dog_vla_init(pVLA, Alloc) dog_vla_initCustom(pVLA, Alloc, 8)

#define dog_vla_shouldGrow(pVLA)                                        \
  (!!((pVLA)->len) * !(((pVLA)->len) & ((pVLA)->step_size) - 1))        \

#define dog_vla_ensureSpace(pVLA)                       \
  (dog_vla_shouldGrow(pVLA)                             \
   ? dog_vla_grow_impl(pVLA, dog_vla_sizeof(pVLA),      \
                       dog_vla_alignof(pVLA))           \
   : true)

#define dog_vla_push(pVLA, Value)                       \
  (dog_vla_ensureSpace(pVLA)                            \
   ? *(((pVLA)->ptr)+((pVLA)->len++)) = (Value), true   \
   : false)

DOGAPI bool dog_vla_init_impl(void *, DogAlloc *, usize, usize, usize);
DOGAPI bool dog_vla_grow_impl(void *, usize, usize);

#endif  /* !DOG_VLA_H_DEFS */

#undef DOGAPI

#if defined(DOG_VLA_IMPL) && !defined(DOG_VLA_H_IMPL)
#define DOG_VLA_H_IMPL

DECLARE_DogVLA(void);

bool
dog_vla_init_impl(void *vla, DogAlloc *alloc, usize step_size,
                  usize size, usize align)
{
  DogVLA(void) *typed_vla = vla;
  void *ptr = NULL;

  if (step_size == 0 || (step_size & (step_size - 1))) {
    fprintf(stderr, "dog_vla_init_impl: step_size must be a power of 2\n");
    exit(EXIT_FAILURE);
  }

  /* FIXME: due to the structure of our VLA implementation, the
     initial allocation doesn't actually happen in `init`, it happens
     in `grow`. Once we've got an actual allocator underlying this
     it'll need to be fixed. */
  DogPageChunk chunk = dog_page_getChunk(4096, NULL, 8);
  ptr = chunk.addr;
  if (ptr == NULL) {
    return false;
  }

  typed_vla->ptr = ptr;
  typed_vla->len = 0;
  typed_vla->step_size = step_size;
  typed_vla->alloc = alloc;

  return true;
}

bool
dog_vla_grow_impl(void *vla, usize size, usize align)
{
  DogVLA(void) *typed_vla = vla;

  printf("dog_vla_grow_impl(%p, %zu, %zu)\n", vla, size, align);

  return true;
}

#endif  /* DOG_VLA_IMPL && !DOG_VLA_H_IMPL */

#undef DOG_VLA_N_POW2_TAG_BIT
