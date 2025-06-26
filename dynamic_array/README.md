## Dynamic array

A dynamic array is a linear data structure containing `n` elements of a certain type, where $n\in\mathbb{N}_0$.  
$\mathbb{N}_0$ is platform-specific and constrained to the size of `size_t`.


### Usage
```c
#include <stdio.h>
#include "dynamic_array.h'

DA_CREATE_TYPE(int);                                // creates structures and functions responsible for handling a dynamic array of ints, works essentially like a template
typedef struct Dynamic_Array_int Dynamic_Array_Int; // convenience type alias

int main() {
  Dynamic_Array_Int da_int = da_init_int();
  da_append_int(&da_int, 10);
  da_append_int(&da_int, 20);

  da_foreach(&da_int, int) {
    printf("%d: %d\n", it.i, it.elem);
  }

  // 0: 10
  // 1: 20
}
```

### Interface
```c
typedef da_% Dynamic_Array_%; // type alias for convenience
da_% da_init_%(); // initializes the dynamic_array by allocating 256 elements of type ty 
void da_append_%(da_% *da, % elem); // appends the `elem` to the back of the array
void da_remove_%(da_% *da, size_t idx); // removes element at `idx`, shifts the rest to the left. DOES NOT ZERO-SET THE DANGLING ELEMENTS!

da_foreach(da_% *da, %) {
  // iterates over elements of `da`
  size_t index = it.i;
  % element = it.elem;
}
```
`%` - substitute the provided type