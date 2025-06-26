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

#define da_header(p)      ((p) ? (Dynamic_Array *)(p)-1 : NULL)
#define da_must(p)        (((Dynamic_Array *)((p) ? (p) : da_init(p))) - 1)
#define da_init(p)        (p = da_initf(p, sizeof(*(p))))
#define da_len(p)         ((p) ? da_header(p)->count : 0)
#define da_append(p, v)   ({ da_must(p); da_growf((void **)&p, sizeof(*(p))); (p)[da_header(p)->count++] = (v); })
#define da_remove(p, idx) ({ da_must(p); da_removef(p, idx, sizeof(*p)); })

// Allocates space for 8 potential elements and a prefix that stores information about the state of the array.
// Returns pointer to the 0th element.
void *da_initf(void *p, size_t element_size) {
  Dynamic_Array *da = malloc(sizeof(Dynamic_Array) + 8 * element_size);
  da->count = 0;
  da->capacity = 8;
  return da + 1;
}

// Grows the array's size twofold.
// Returns pointer to the 0th element.
void da_growf(void **p, size_t element_size) {
  Dynamic_Array *da = da_header(*p);
  if (da->count < da->capacity * 0.75) return;

  da->capacity *= 2;
  *p = ((Dynamic_Array *)realloc(da, sizeof(Dynamic_Array) + da->capacity * element_size)) + 1;
}

void da_removef(void *p, size_t idx, size_t element_size) { 
  Dynamic_Array *da = da_header(p);
  memmove(p+idx*element_size, p+(idx+1)*element_size, element_size * (--da->count-idx)); 
}

#endif
