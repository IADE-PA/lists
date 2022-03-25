#include "unity/unity.h"

#include "../src/list.h"

List list;

int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char* strings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

void setUp(void) {
    list = list_create();
}

void tearDown(void) {
    list_destroy(list);
}

void insert_elements(int start, int end, void* array) {
    for (int i = start; i <= end; i++) {
        list_insert_last(list, &(array[i]));
    }
}

void insert_numbers(int start, int end) {
    insert_elements(start, end, (void*)numbers);
}

void insert_strings(int start, int end) {
    insert_elements(start, end, (void*)strings);
}

void test_list_is_empty() {
    TEST_ASSERT(list_is_empty(list));
}

void test_list_size() {
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(0, 0);
    TEST_ASSERT_EQUAL(1, list_size(list));
    list_insert_last(list, &strings[3]);
    TEST_ASSERT_EQUAL(2, list_size(list));
}

void test_list_get_first() {
    TEST_ASSERT_EQUAL(NULL, list_get_first(list));
    insert_numbers(0, 3);
    TEST_ASSERT_EQUAL(&numbers[0], list_get_first(list));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_is_empty);
    RUN_TEST(test_list_size);
    RUN_TEST(test_list_get_first);
    return UNITY_END();
}