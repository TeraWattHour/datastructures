#ifndef DATASTRUCTURES_DA
#define DATASTRUCTURES_DA

#include <stdlib.h>
#include <assert.h>

#define DA_CREATE_TYPE(ty) \
  struct Dynamic_Array_##ty { \
    ty *elements; \
    size_t count; \
    size_t capacity; \
  }; \
  struct Dynamic_Array_##ty da_init_##ty() { \
    return (struct Dynamic_Array_##ty) { \
      .elements = malloc(sizeof(ty) * 256), \
      .count = 0, \
      .capacity = 256 \
    }; \
  } \
  void da_append_##ty(struct Dynamic_Array_##ty *da, ty elem) { \
    if (da->count >= da->capacity * 0.75) { \
      da->capacity *= 2; \
      da->elements = realloc(da->elements, sizeof(ty) * da->capacity); \
      assert(da->elements); \
    } \
    da->elements[da->count++] = elem; \
  }

#define da_foreach(da, ty) \
  for (struct { int i; ty elem; } it = {.i=0, .elem=(da)->elements[0]}; it.i < (da)->count; it.i++, it.elem=(da)->elements[it.i])

#endif
