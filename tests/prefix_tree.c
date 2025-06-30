#include <unity/unity.h>

#include "../prefix_tree/prefix_tree.h"
#include <string.h>

void setUp(void) {}

void tearDown(void) {}

void advance_expect_ascii(Prefix_Node **pn, char expected) {
  TEST_ASSERT_EQUAL_CHAR(expected, *(*pn)->codepoint);
  *pn = (*pn)->next;
}

void advance_expect(Prefix_Node **pn, const char *expected) {
  printf("%s -> %.*s\n", expected, (*pn)->width, (*pn)->codepoint);
  TEST_ASSERT_EQUAL_CHAR(0, strncmp((*pn)->codepoint, expected, (*pn)->width));
  *pn = (*pn)->next;
}

void test_ParseAscii(void) {
  const char *source = "hello, world!";
  Prefix_Node *pn = pn_create(source);

  for (char *ptr = source; *ptr; ++ptr) advance_expect_ascii(&pn, *ptr);
}

void test_ParseEmpty(void) {
  const char *source = "";
  Prefix_Node *pn = pn_create(source);

  TEST_ASSERT_NULL(pn);
}

void test_ParseOne(void) {
  const char *source = "1";
  Prefix_Node *pn = pn_create(source);
  advance_expect_ascii(&pn, '1');
}

void test_ParseUtf8(void) {
  const char *source = "費玉清";
  Prefix_Node *pn = pn_create(source);
  advance_expect(&pn, "費");
  advance_expect(&pn, "玉");
  advance_expect(&pn, "清");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_ParseAscii);
  RUN_TEST(test_ParseEmpty);
  RUN_TEST(test_ParseOne);
  RUN_TEST(test_ParseUtf8);
  
  return UNITY_END();
}
