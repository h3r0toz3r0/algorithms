/**
 * @file    test_main.c
 * @brief   Control suite for all test cases.
 *
 * @author  Anna DeVries
 * @date    August 17, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "test_example.h"

// Macros
#define MAX_LENGTH 256

// Function Declarations
static void print_help(void);
static int  create_suites(void);
static void list_suites(void);
static void run_suite(const char *suite_name);
static bool is_name_match(const char *string_1, const char *string_2);

/**
 * @brief   Main function to run all tests.
 *
 * The function initializes the CUnit test registry, creates test suites,
 * and runs the tests based on command-line input.
 *
 * @param argc  Number of command-line arguments.
 * @param argv  Array of command-line arguments.
 *
 * @return  Returns 0 on success, or a non-zero value on failure.
 */
int
main (int argc, char *argv[])
{
    int retval = CUE_SUCCESS;          // Assume success unless an error occurs
    CU_basic_set_mode(CU_BRM_VERBOSE); // maximum output of test runs

    // Initialize the CUnit registry
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        fprintf(stderr, "Failed to initialize CUnit registry\n");
        retval = CU_get_error();
        goto CLEANUP;
    }

    // Create all test suites
    retval = create_suites();

    if (CUE_SUCCESS != retval)
    {
        fprintf(stderr, "Failed to create CUnit test suites\n");
        goto CLEANUP;
    }

    // Process command-line arguments
    if (1 == argc)
    {
        CU_basic_run_tests();
    }
    else if (2 == argc)
    {
        // Process the command
        if (is_name_match("help", argv[1]))
        {
            print_help();
        }
        else if (is_name_match("list", argv[1]))
        {
            list_suites();
        }
        else
        {
            run_suite(argv[1]);
        }
    }
    else
    {
        print_help();
    }

CLEANUP:
    CU_cleanup_registry();
    return retval;
}

/**
 * @brief   Print help instructions.
 *
 * @return  None.
 */
static void
print_help (void)
{
    printf("Usage: test_main [command]\n");
    printf("Commands:\n");
    printf("  help          Print this help message\n");
    printf("  <suite_name>  Run the specified test suite\n");
    printf("  (no argument) Run all test suites\n");
    return;
}

/**
 * @brief   List all available test suites.
 *
 * @return  None.
 */
static void
list_suites (void)
{
    CU_pSuite pSuite = NULL;
    printf("Available Suites:\n");

    for (pSuite = CU_get_registry()->pSuite; pSuite != NULL;
         pSuite = pSuite->pNext)
    {
        printf("\t%s\n", pSuite->pName);
    }

    printf("\n");
}

/**
 * @brief   Compare two strings for equality, checking length and null
 * termination.
 *
 * This function checks if two strings are of the same length, null-terminated,
 * and if their content matches up to the length of the shorter string.
 *
 * @param string_1  Pointer to the first string to compare.
 * @param string_2  Pointer to the second string to compare.
 *
 * @return  True if both strings are of the same length, null-terminated,
 *          and match in content. False otherwise.
 */
static bool
is_name_match (const char *string_1, const char *string_2)
{
    // Check if strings are null-terminated
    bool b_is_null_terminated;
    int  length_1;
    int  length_2;

    length_1 = strnlen(string_1, MAX_LENGTH);
    length_2 = strnlen(string_2, MAX_LENGTH);
    b_is_null_terminated
        = ('\0' == string_1[length_1]) && ('\0' == string_2[length_2]);

    // Check if strings are the same length
    bool b_same_length;
    b_same_length = (length_1 == length_2);

    // Check if the strings are the same length and match in content
    bool b_name_matches;
    b_name_matches
        = b_same_length && (0 == strncmp(string_1, string_2, length_1));
    return b_name_matches && b_is_null_terminated;
}

/**
 * @brief   Run the specified test suite.
 *
 * @param suite_name  Name of the suite to run.
 *
 * @return  Returns 0 on success, or a non-zero value on failure.
 */
static void
run_suite (const char *suite_name)
{
    CU_pSuite pSuite        = NULL;
    CU_pSuite current_suite = NULL;

    for (pSuite = CU_get_registry()->pSuite; pSuite != NULL;
         pSuite = pSuite->pNext)
    {
        if (is_name_match(suite_name, pSuite->pName))
        {
            current_suite = pSuite;
            break;
        }
    }

    if (NULL == current_suite)
    {
        fprintf(stderr, "'%s' not found\n", suite_name);
    }
    else
    {
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_suite(current_suite);
    }

    return;
}

/**
 * @brief   Create all test suites.
 *
 * This should be the only function that needs to be updated. This is
 * where a developer may add additional suites to be created. See the
 * "example_suite" as an example.
 *
 * @return  Returns 0 on success, or a non-zero value on failure.
 */
static int
create_suites (void)
{
    int retval = CUE_SUCCESS; // Assume success unless an error occurs

    // Example:
    if (NULL == example_suite())
    {
        fprintf(stderr, "Failed to create Example Suite\n");
        retval = CU_get_error();
        goto EXIT;
    }

    // Additionally test cases should be added below:

EXIT:
    return retval;
}
