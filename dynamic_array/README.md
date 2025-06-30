## Dynamic array

A dynamic array is a linear data structure containing `n` elements of a certain type, where $n\in\mathbb{N}_0$.  
$\mathbb{N}_0$ is platform-specific and constrained to the size of `size_t`.  
This implementation is heavily inspired by [stb](https://nothings.org/stb_ds/).


### Usage
```c
#include <stdio.h>
#include "dynamic_array.h'

// Macros assign to the first argument on resize;
// that means that you must pass the array pointer by reference to other functions. 
// Hence, in the below example, we use `int **ints`, instead of `int *ints`, which could make any changes (resize) to `ints`
// ineffective in the `main` function scope. This is similar to how `realloc` works.
void append_two_items(int **ints) {
  da_append(*ints, 10);
  da_append(*ints, 20);
}

int main() {
  int *ints = NULL;
  append_two_items(&ints);
  da_append(ints, 30);
  da_append(ints, 40);
  
  for (size_t i = 0; i < da_len(ints); i++) {
    printf("%zu: %d\n", i, ints[i]);
  }
  // 0: 10
  // 1: 20
  // 2: 30
  // 3: 40
}
```

### Interface
- `da_append(% *da, % elem)` - appends `elem`. 
- `da_len(% *da)` - returns the number of items in the array.
`%` - substitute the provided type
