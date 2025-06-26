#include <unity/unity.h>

#include "../dynamic_array/dynamic_array.h"

DA_CREATE_TYPE(int)

void setUp(void) {}

void tearDown(void) {}

void test_ArrayRetainsManyValues(void) {
  struct Dynamic_Array_int da = da_init_int();

  for (int i = 0; i < INT_MAX; i++) {
    da_append_int(&da, i);
  }

  TEST_ASSERT_EQUAL(INT_MAX, da.count);
  for (int i = 0; i < INT_MAX; i++) {
    TEST_ASSERT_EQUAL_INT(i, da.elements[i]);
  }
}

void test_Foreach(void) {
  struct Dynamic_Array_int da = da_init_int();

  for (int i = 0; i < INT16_MAX; i++) da_append_int(&da, i * 2);
  TEST_ASSERT_EQUAL(INT16_MAX, da.count);

  size_t idx = 0;
  da_foreach(&da, int) {
    TEST_ASSERT_EQUAL(idx, it.i);
    TEST_ASSERT_EQUAL(idx * 2, it.elem);
    idx++;
  }
}

void test_RemoveFront(void) {
  struct Dynamic_Array_int da = da_init_int();
  da_append_int(&da, 1);
  da_append_int(&da, 2);

  da_remove_int(&da, 0);
  TEST_ASSERT_EQUAL(1, da.count);
  TEST_ASSERT_EQUAL(2, da.elements[0]);
}

void test_RemoveFold(void) {
  struct Dynamic_Array_int da = da_init_int();
  for (int i = 0; i < 32; i++) da_append_int(&da, i);
  for (int i = 0; i < 31; i++) {
    da_remove_int(&da, 0);
    TEST_ASSERT_EQUAL(i+1, da.elements[0]);
  }
  da_remove_int(&da, 0);
  TEST_ASSERT_EQUAL(0, da.count);
}

void test_RemoveBack(void) {
  struct Dynamic_Array_int da = da_init_int();
  for (int i = 0; i < 32; i++) da_append_int(&da, i);
  for (int i = 0; i < 32; i++) {
    TEST_ASSERT_EQUAL(32-i, da.count);
    da_remove_int(&da, 31 - i);
    TEST_ASSERT_EQUAL(31-i, da.count);
  }
  TEST_ASSERT_EQUAL(0, da.count);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_Foreach);
  RUN_TEST(test_RemoveFront);
  RUN_TEST(test_RemoveFold);
  RUN_TEST(test_RemoveBack);

  return UNITY_END();
}
