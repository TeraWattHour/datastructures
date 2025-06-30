#ifndef DATASTRUCTURES_PREFIX_TREE
#define DATASTRUCTURES_PREFIX_TREE

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

size_t utf8_codepoint_width(char *source);

typedef struct Prefix_Node {
  const char *codepoint;
  size_t width;

  struct Prefix_Node *next;
} Prefix_Node;

Prefix_Node *pn_create(const char *source) {
  if (!source || !*source) return NULL;

  Prefix_Node *head = (Prefix_Node *)malloc(sizeof(Prefix_Node));
  memset(head, 0, sizeof(Prefix_Node));

  Prefix_Node *cursor = head;

  for (char *ptr = (char *)source; *ptr;) {
    size_t width = utf8_codepoint_width(ptr);
    Prefix_Node *pn = (Prefix_Node *)malloc(sizeof(Prefix_Node));
    pn->codepoint = ptr;
    pn->width = width;
    pn->next = NULL;

    cursor->next = pn;
    cursor = pn;

    ptr += width;
  }

  return head->next;
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