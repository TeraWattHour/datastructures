#include <unity/unity.h>

#include "../prefix_tree/prefix_tree.h"
#include <string.h>

void setUp(void) {}

void tearDown(void) {}

void advance_expect_ascii(Prefix_Node **pn, char expected) {
  TEST_ASSERT_EQUAL_CHAR(expected, *(*pn)->codepoint);
  *pn = (*pn)->next;
}

void advance_expect(Prefix_Node *pn, const char *expected) {
  for (Prefix_Node *candidate = pn->next; candidate < pn->next + da_len(pn->next); candidate++) {
    if (candidate->width == strlen(expected) && strncmp(candidate->codepoint, expected, candidate->width) == 0) {
      *pn = *candidate;
      return;
    }
  }
  TEST_ASSERT_NULL_MESSAGE(1, "unreachable");
}

void dump_prefix_tree(Prefix_Node *node) {
  if (node->codepoint) printf("%.*s", node->width, node->codepoint);

  for (Prefix_Node *next = node->next; next < node->next + da_len(node->next); next++) {
    dump_prefix_tree(next);
    if (next < node->next + da_len(node->next)-1)
      printf("\n");
  }
}

void test_ParseAscii(void) {
  Prefix_Node pn = {0};
  pn_insert(&pn, "hello, world!");
  pn_insert(&pn, "welcome");
  pn_insert(&pn, "hello everyone");

  dump_prefix_tree(&pn);
}

void test_ParseEmpty(void) {
  Prefix_Node pn = {0};
  TEST_ASSERT_NULL(pn.codepoint);
  TEST_ASSERT_NULL(pn.next);
}

void test_ParseOne(void) {
  Prefix_Node pn = {0};
  pn_insert(&pn, "1");
  TEST_ASSERT_EQUAL(1, da_len(pn.next));
  TEST_ASSERT_EQUAL(0, strcmp(pn.next[0].codepoint, "1"));
}

void test_ParseUtf8(void) {
  Prefix_Node pn = {0};
  pn_insert(&pn, "費玉清");
  advance_expect(&pn, "費");
  advance_expect(&pn, "玉");
  advance_expect(&pn, "清");
  TEST_ASSERT_NULL(pn.next);
}

int main(void) {
  UNITY_BEGIN();

  // RUN_TEST(test_ParseAscii);
  RUN_TEST(test_ParseEmpty);
  RUN_TEST(test_ParseOne);
  RUN_TEST(test_ParseUtf8);
  
  return UNITY_END();
}
