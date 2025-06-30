#include <unity/unity.h>

#include "../dynamic_array/dynamic_array.h"

void setUp(void) {}

void tearDown(void) {}

void test_ArrayRetainsManyValues(void) {
  int *seq = da_alloc(int);

  for (int i = 0; i < INT16_MAX; i++) {
    da_append(seq, i);
    TEST_ASSERT_EQUAL(i, seq[i]);
  }
  TEST_ASSERT_EQUAL(INT16_MAX, da_len(seq));

  for (int i = 0; i < INT16_MAX; i++) TEST_ASSERT_EQUAL(i, seq[i]);
}

void test_RemoveFront(void) {
  int *seq = da_alloc(int);
  
  da_append(seq, 1);
  da_append(seq, 2);

  da_remove(seq, 0);
  TEST_ASSERT_EQUAL(1, da_header(seq)->count);
  TEST_ASSERT_EQUAL(2, seq[0]);
}

void test_RemoveFold(void) {
  int *seq = da_alloc(int);

  for (int i = 0; i < 32; i++) da_append(seq, i);
  for (int i = 0; i < 31; i++) {
    da_remove(seq, 0);
    TEST_ASSERT_EQUAL(i+1, seq[0]);
  }
  da_remove(seq, 0);
  TEST_ASSERT_EQUAL(0, da_header(seq)->count);
}

void test_RemoveBack(void) {
  int *seq = da_alloc(int);

  for (int i = 0; i < 32; i++) da_append(seq, i);
  for (int i = 0; i < 32; i++) {
    TEST_ASSERT_EQUAL(32-i, da_header(seq)->count);
    da_remove(seq, 31 - i);
    TEST_ASSERT_EQUAL(31-i, da_header(seq)->count);
  }
  TEST_ASSERT_EQUAL(0, da_header(seq)->count);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_ArrayRetainsManyValues);
  RUN_TEST(test_RemoveFront);
  RUN_TEST(test_RemoveFold);
  RUN_TEST(test_RemoveBack);

  return UNITY_END();
}
