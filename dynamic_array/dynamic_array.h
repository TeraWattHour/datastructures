#ifndef DATASTRUCTURES_DA
#define DATASTRUCTURES_DA

#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
      assert(da->capacity / 2 <= SIZE_T_MAX && "dynamic array can contain at most `SIZE_T_MAX` elements"); \
      da->capacity *= 2; \
      da->elements = realloc(da->elements, sizeof(ty) * da->capacity); \
      assert(da->elements); \
    } \
    da->elements[da->count++] = elem; \
  } \
  void da_remove_##ty(struct Dynamic_Array_##ty *da, size_t idx) { \
    assert(idx < da->count); \
    memmove(da->elements+idx, da->elements+idx+1, sizeof(ty) * (da->count-idx-1)); \
    da->count--; \
  }

#define da_foreach(da, ty) \
  for (struct { int i; ty elem; } it = {.i=0, .elem=(da)->elements[0]}; it.i < (da)->count; it.i++, it.elem=(da)->elements[it.i])

#endif
