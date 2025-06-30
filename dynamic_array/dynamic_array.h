#ifndef DATASTRUCTURES_DA
#define DATASTRUCTURES_DA

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

typedef struct Dynamic_Array {
  size_t count;
  size_t capacity;
} Dynamic_Array;

#define da_alloc(typ)                     da_allocf(sizeof(typ), 0)
#define da_allocn(typ, initial_capacity)  da_allocf(sizeof(typ), initial_capacity)

#define da_header(p)      ((p) ? (Dynamic_Array *)(p)-1 : NULL)
#define da_len(p)         ((p) ? da_header(p)->count : 0)
#define da_append(p, v)   ({ da_growf((void **)&p, sizeof(*(p))); (p)[da_header(p)->count++] = (v); })
#define da_remove(p, idx) ({ da_removef(p, idx, sizeof(*p)); })

void *da_allocf(size_t element_size, size_t initial_capacity) {
  Dynamic_Array *da = malloc(sizeof(Dynamic_Array) + initial_capacity * element_size);
  da->count = 0;
  da->capacity = initial_capacity;
  return da + 1;
}

// Grows the array's size twofold.
// Returns pointer to the 0th element.
void da_growf(void **p, size_t element_size) {
  Dynamic_Array *da = da_header(*p);
  if (da->count + 1 < da->capacity * 0.75) return;

  da->capacity *= 2;
  if (da->capacity == 0) da->capacity = 4;

  *p = ((Dynamic_Array *)realloc(da, sizeof(Dynamic_Array) + da->capacity * element_size)) + 1;
}

void da_removef(void *p, size_t idx, size_t element_size) { 
  Dynamic_Array *da = da_header(p);
  memmove(p+idx*element_size, p+(idx+1)*element_size, element_size * (--da->count-idx)); 
}

#endif
