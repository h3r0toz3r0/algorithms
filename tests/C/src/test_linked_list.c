/**
 * @file    test_linked_list.c
 * @brief   Linked List test suite.
 *
 * @author  Anna DeVries
 * @date    August 21, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <CUnit/Basic.h>
#include "linked_list.h"
#include "test_auxiliary.h"
#include "test_linked_list.h"

// Function Declarations
static void test_linked_list_simple(void);
void static_print_int(void *p_data);
void static_delete_int(void *p_data);
int static_compare_ints(void *p_lhs, void *p_rhs);

// Suite Creation Funtion
CU_pSuite
linked_list_suite (void)
{
    CU_pSuite suite = NULL;
    suite           = CU_add_suite("linked-list-suite", 0, 0);

    if (NULL == suite)
    {
        ERROR_LOG("Failed to add linked-list-suite\n");
        goto CLEANUP;
    }

    if (NULL == (CU_add_test(suite, "test_linked_list_simple", test_linked_list_simple)))
    {
        ERROR_LOG("Failed to add test_linked_list_simple to suite\n");
        suite = NULL;
        goto CLEANUP;
    }

CLEANUP:
    if (NULL == suite)
    {
        CU_cleanup_registry();
    }

    return suite;
}

/**
 * @brief   Test case for the hello function.
 *
 * This test verifies that the hello function prints "Hello World" and returns
 * 0. It captures the output and checks against the expected output.
 *
 * @return  None.
 */
static void
test_linked_list_simple (void)
{
    linked_list_t *p_test = NULL;
    char *output = NULL;
    char expected_output[10];

    // Create the linked list
    p_test = linked_list_create(static_delete_int, static_compare_ints, static_print_int);

    // Test case 1: Preappend value when list is empty
    int *value_1 = calloc(1, sizeof(int));
    *value_1 = 5;
    p_test = linked_list_preappend(p_test, value_1);

    // Capture and check output
    output = capture_stdout(linked_list_print, p_test);
    snprintf(expected_output, sizeof(expected_output), "%d\n", *value_1); // Expect only "5\n"
    CU_ASSERT_STRING_EQUAL(output, expected_output);

    // Test case 2: Preappend value when a list exists
    int *value_2 = calloc(1, sizeof(int));
    *value_2 = 4;
    p_test = linked_list_preappend(p_test, value_2);

    // Capture and check output
    output = capture_stdout(linked_list_print, p_test);
    snprintf(expected_output, sizeof(expected_output), "%d\n%d\n", *value_2, *value_1); // Expect "4\n5\n"
    CU_ASSERT_STRING_EQUAL(output, expected_output);

    // Test case 3: Insert value at end of list
    int *value_3 = calloc(1, sizeof(int));
    *value_3 = 10;
    p_test = linked_list_insert(p_test, value_3, 2);

    // Capture and check output
    output = capture_stdout(linked_list_print, p_test);
    snprintf(expected_output, sizeof(expected_output), "%d\n%d\n%d\n", *value_2, *value_1, *value_3); // Expect "4\n5\n10\n"
    CU_ASSERT_STRING_EQUAL(output, expected_output);

    // Test case 4: Insert value in the middle of the list
    int *value_4 = calloc(1, sizeof(int));
    *value_4 = 23;
    p_test = linked_list_insert(p_test, value_4, 2);

    // Capture and check output
    output = capture_stdout(linked_list_print, p_test);
    snprintf(expected_output, sizeof(expected_output), "%d\n%d\n%d\n%d\n", *value_2, *value_1, *value_4, *value_3); // Expect "4\n5\n23\n10\n"
    CU_ASSERT_STRING_EQUAL(output, expected_output);

    // Destroy the linked list
    linked_list_destroy(p_test);

    // Check if the list is empty (should not print anything)
    output = capture_stdout(linked_list_print, p_test);
    CU_ASSERT_STRING_EQUAL(output, ""); // Expect an empty string since the list is destroyed

    free(output);
    return;
}

// Function to delete an integer (free the memory)
void static_delete_int(void *p_data) 
{
    free(p_data);
    p_data = NULL;
    return;
}

// Function to compare two integers
int static_compare_ints(void *p_lhs, void *p_rhs) 
{
    int lhs = *(int *)p_lhs;
    int rhs = *(int *)p_rhs;
    return (lhs > rhs) - (lhs < rhs);
}

// Function to print an integer
void static_print_int(void *p_data) 
{
    printf("%d ", *(int *)p_data);
    return;
}