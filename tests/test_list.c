#include "unity/unity.h"

#include "../src/list.h"

#include <string.h>
#include <stdlib.h>
// #include <mcheck.h>

List list;

int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char* strings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

void setUp(void) {
    list = list_create();
}

void tearDown(void) {
    list_destroy(list, NULL);
}

/*******************************************************************************
 Helper functions.
 ******************************************************************************/

bool is_equal(void* a, void* b) {
    return a == b;
}

void insert_numbers(int start, int end) {
    for (int i = start - 1; i < end; i++) {
        list_insert_last(list, &numbers[i]);
    }
}

void insert_number(int number) {
    insert_numbers(number, number);
}

int* number_address_of(int number) {
    return &(numbers[number - 1]);
}

void insert_strings(int start, int end) {
    for (int i = start - 1; i < end; i++) {
        list_insert_last(list, &strings[i]);
    }
}

void insert_string(int str_idx) {
    insert_strings(str_idx, str_idx);
}

char** string_address_of(int str_idx) {
    return &(strings[str_idx - 1]);
}

/*******************************************************************************
 Tests
 ******************************************************************************/

void test_list_is_empty() {
    TEST_ASSERT(list_is_empty(list));
}

void test_list_size() {
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(1, 1);
    TEST_ASSERT_EQUAL(1, list_size(list));
    insert_strings(3, 3);
    TEST_ASSERT_EQUAL(2, list_size(list));
}

void test_list_get_first() {
    TEST_ASSERT_NULL(list_get_first(list));
    insert_numbers(1, 3);
    TEST_ASSERT_EQUAL(number_address_of(1), list_get_first(list));
}

void test_list_get_last() {
    TEST_ASSERT_NULL(list_get_last(list));
    insert_numbers(1, 3);
    TEST_ASSERT_EQUAL(number_address_of(3), list_get_last(list));
}

void test_list_get() {
    TEST_ASSERT_NULL(list_get(list, 0));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(number_address_of(2), list_get(list, 1));
}

void test_list_find() {
    TEST_ASSERT_EQUAL(-1, list_find(list, is_equal, number_address_of(1)));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(2, list_find(list, is_equal, number_address_of(3)));
    TEST_ASSERT_EQUAL(-1, list_find(list, is_equal, number_address_of(10)));
}

void test_list_insert_first() {
    TEST_ASSERT_NULL(list_get_first(list));
    list_insert_first(list, &strings[0]);
    TEST_ASSERT_EQUAL(&strings[0], list_get_first(list));
    list_insert_first(list, &numbers[0]);
    TEST_ASSERT_EQUAL(&numbers[0], list_get_first(list));
}

void test_list_insert_last() {
    TEST_ASSERT_NULL(list_get_last(list));
    list_insert_last(list, &strings[0]);
    TEST_ASSERT_EQUAL(&strings[0], list_get_last(list));
    TEST_ASSERT_EQUAL(1, list_size(list));
    list_insert_last(list, &numbers[0]);
    TEST_ASSERT_EQUAL(&numbers[0], list_get_last(list));
    TEST_ASSERT_EQUAL(2, list_size(list));
}

void test_list_insert() {
    list_insert(list, &numbers[0], 10);
    TEST_ASSERT_EQUAL(0, list_size(list));
    TEST_ASSERT_NULL(list_get_first(list));
    TEST_ASSERT_NULL(list_get_last(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    list_insert(list, &numbers[0], 0);
    TEST_ASSERT_EQUAL(1, list_size(list));
    TEST_ASSERT_EQUAL(&numbers[0], list_get_first(list));
    insert_strings(1,3);
    list_insert(list, &numbers[1], 4);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(&numbers[1], list_get_last(list));
    list_insert(list, &numbers[2], 3);
    TEST_ASSERT_EQUAL(6, list_size(list));
    TEST_ASSERT_EQUAL(&numbers[2], list_get(list, 3));
}

void test_list_remove_first() {
    TEST_ASSERT_NULL(list_remove_first(list));
    insert_string(1);
    TEST_ASSERT_EQUAL(string_address_of(1), list_remove_first(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(1), list_get_first(list));
    TEST_ASSERT_EQUAL(number_address_of(1), list_remove_first(list));
    TEST_ASSERT_EQUAL(4, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(2), list_get_first(list));
}

void test_list_remove_last() {
    TEST_ASSERT_NULL(list_remove_last(list));
    insert_string(1);
    TEST_ASSERT_EQUAL(string_address_of(1), list_remove_last(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(5), list_get_last(list));
    TEST_ASSERT_EQUAL(number_address_of(5), list_remove_last(list));
    TEST_ASSERT_EQUAL(4, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(4), list_get_last(list));
}

void test_list_remove() {
    TEST_ASSERT_NULL(list_remove(list, 0));
    TEST_ASSERT_NULL(list_remove(list, 10));
    insert_strings(1, 6);
    TEST_ASSERT_EQUAL(string_address_of(1), list_remove(list, 0));
    TEST_ASSERT_EQUAL(string_address_of(6), list_remove(list, list_size(list) - 1));
    TEST_ASSERT_EQUAL(string_address_of(4), list_remove(list, 2));
    TEST_ASSERT_EQUAL(string_address_of(5), list_remove(list, 2));
}

void test_list_make_empty() {
    insert_strings(1,3);
    insert_numbers(1,3);
    insert_strings(4,7);
    TEST_ASSERT_FALSE(list_is_empty(list));
    list_make_empty(list, NULL);
    TEST_ASSERT_TRUE(list_is_empty(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
}

void free_str(void *str) {
    free(str);
}

void test_list_make_empty_free_elements() {
    // mtrace();
    char* str = malloc(sizeof(char)*10);
    strcpy(str, "test");
    list_insert_last(list, str);
    list_make_empty(list, free_str);
}

void test_list_to_array() {
    insert_strings(1,3);
    char* array[3];
    list_to_array(list, (void**)array);
    TEST_ASSERT_EQUAL(string_address_of(1), array[0]);
    TEST_ASSERT_EQUAL(string_address_of(2), array[1]);
    TEST_ASSERT_EQUAL(string_address_of(3), array[2]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_is_empty);
    RUN_TEST(test_list_size);
    RUN_TEST(test_list_get_first);
    RUN_TEST(test_list_get_last);
    RUN_TEST(test_list_get);
    RUN_TEST(test_list_find);
    RUN_TEST(test_list_insert_first);
    RUN_TEST(test_list_insert_last);
    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_remove_first);
    RUN_TEST(test_list_remove_last);
    RUN_TEST(test_list_remove);
    RUN_TEST(test_list_make_empty);
    RUN_TEST(test_list_to_array);
    RUN_TEST(test_list_make_empty_free_elements);
    return UNITY_END();
}