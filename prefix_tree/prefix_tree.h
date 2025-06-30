#ifndef DATASTRUCTURES_PREFIX_TREE
#define DATASTRUCTURES_PREFIX_TREE

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "dynamic_array.h"

size_t utf8_codepoint_width(char *source);

typedef struct Prefix_Node {
  const char *codepoint;
  size_t width;

  struct Prefix_Node *next;
} Prefix_Node;

void pn_insert(Prefix_Node *tree, const char *source) {
  if (!source || !*source) return;

  Prefix_Node *node = tree;

  for (char *ptr = (char *)source; *ptr;) {
    size_t width = utf8_codepoint_width(ptr);
    const char *codepoint = ptr;
    ptr += width;
    
    if (!node->next) node->next = da_alloc(Prefix_Node);
    Prefix_Node *candidate = node->next;

    for (; candidate < node->next + da_len(node->next); candidate++) {
      // sequence already exists, no need for adding it again
      if (width == candidate->width && strncmp(candidate->codepoint, codepoint, width) == 0) {
        node = candidate;
        goto outer;
      }
    }

    Prefix_Node pn = {
      .codepoint = codepoint,
      .width = width,
      .next = NULL,
    };
    da_append(node->next, pn);
    node = &node->next[da_len(node->next)-1];

  outer:;
  }

  return;
}

size_t utf8_codepoint_width(char *source) {
  if ((*source & 0x80) == 0x00) {  // 0xxxxxxx
    return 1;
  } else if ((*source & 0xE0) == 0xC0) {  // 110xxxxx
    return 2;
  } else if ((*source & 0xF0) == 0xE0) {  // 1110xxxx
    return 3;
  } else if ((*source & 0xF8) == 0xF0) {  // 11110xxx
    return 4;
  }
  
  assert(0 && "invalid codepoint");
}

#endif // DATASTRUCTURES_PREFIX_TREE