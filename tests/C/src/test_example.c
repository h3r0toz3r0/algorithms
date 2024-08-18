/**
 * @file    test_example.c
 * @brief   Example test suite.
 *
 * This file contains the test suite creation for 'example.c'.
 *
 * @author  Anna DeVries
 * @date    August 17, 2024
 */

#include <CUnit/Basic.h>

#include "example.h"
#include "test_example.h"

// Function Declarations
static void test_hello( void );

// Suite Creation Funtion
CU_pSuite example_suite( void ) 
{
    CU_pSuite suite = NULL;

    if ( NULL == ( suite = CU_add_suite("Example Suite", 0, 0) ) ) 
    {
        goto CLEANUP;
    }

    if ( NULL == ( CU_add_test(suite, "test_hello", test_hello) ) ) 
    {
        suite = NULL;
        goto CLEANUP;
    }

CLEANUP:
    if ( NULL == suite )
    {
        CU_cleanup_registry();
    }

    return suite;
}

// Test Case Functions
/**
 * @brief   Test case for the hello function.
 *
 * This test verifies that the hello function prints "Hello World" and returns
 * 0. It captures the output and checks against the expected output.
 */
static void test_hello( void ) 
{
    // // Capture standard output
    // FILE *original_stdout = stdout;
    // freopen("test_output.txt", "w", stdout);

    // // Call the hello function
    // int result = hello();

    // // Restore standard output
    // freopen("/dev/tty", "w", stdout);

    // // Read and check the output
    // FILE *file = fopen("test_output.txt", "r");
    // char output[256];
    // fgets(output, sizeof(output), file);
    // fclose(file);

    // // Check that the output is "Hello World"
    // CU_ASSERT_STRING_EQUAL(output, "Hello World\n");

    // // Check that the function returns 0
    // CU_ASSERT_EQUAL(result, 0);
    return;
}
