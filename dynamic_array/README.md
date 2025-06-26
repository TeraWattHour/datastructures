## Dynamic array

A dynamic array is a linear data structure containing `n` elements of a certain type, where $n\in\mathbb{N}_0$.  
$\mathbb{N}_0$ is platform-specific and constrained to the size of `size-t`.


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
