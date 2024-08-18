/**
 * @file    test_main.c
 * @brief   Control suite for all test cases.
 *
 * @author  Anna DeVries
 * @date    August 17, 2024
 */

#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_example.h"

// Function Declarations
static void print_help( void );

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
int main(int argc, char *argv[])
{
    int retval = EXIT_SUCCESS;  // Assume success unless an error occurs

    // Initialize the CUnit registry
    if (CUE_SUCCESS != CU_initialize_registry()) 
    {
        fprintf(stderr, "Failed to initialize CUnit registry\n");
        retval = CU_get_error();
        goto CLEANUP;
    }

    // Create the Example Suite
    if (NULL == example_suite())
    {
        fprintf(stderr, "Failed to create Example Suite\n");
        retval = CU_get_error();
        goto CLEANUP;
    }

    // Process command-line arguments
    if (2 == argc) 
    {
        if (0 == strncmp(argv[1], "help", 4)) 
        {
            print_help();
        } 
        else 
        {
            // Find and run the specified suite
            CU_pSuite suite = CU_get_registry()->pSuite;
            while (suite != NULL) 
            {
                if (0 == strcmp(CU_get_suite_name(suite), argv[1])) 
                {
                    CU_basic_set_mode(CU_BRM_VERBOSE);
                    CU_basic_run_suite(suite);
                    goto CLEANUP;
                }
                suite = suite->pNext;
            }
            fprintf(stderr, "Test suite '%s' not found\n", argv[1]);
            retval = EXIT_FAILURE;
        }
    } 
    else if (2 < argc) 
    {
        print_help(); 
    } 
    else 
    {
        // Run all test suites
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
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
static void print_help( void )
{
    printf("Usage: test_main [command]\n");
    printf("Commands:\n");
    printf("  help          Print this help message\n");
    printf("  <suite_name>  Run the specified test suite\n");
    printf("  (no argument) Run all test suites\n");
    return;
}
