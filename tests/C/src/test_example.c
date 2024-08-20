/**
 * @file    test_example.c
 * @brief   Example test suite.
 *
 * This file contains the test suite creation for 'example.c'.
 *
 * @author  Anna DeVries
 * @date    August 17, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <CUnit/Basic.h>

#include "example.h"
#include "test_example.h"

// Function Declarations
static void test_hello(void);

// Suite Creation Funtion
CU_pSuite
example_suite (void)
{
    CU_pSuite suite = NULL;
    suite           = CU_add_suite("example-suite", 0, 0);

    if (NULL == suite)
    {
        goto CLEANUP;
    }

    if (NULL == (CU_add_test(suite, "test_hello", test_hello)))
    {
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
test_hello (void)
{
    // Redirect stdout to capture output
    int stdout_fd = dup(fileno(stdout));
    FILE *output = fopen("/tmp/test_hello_output.txt", "w");
    dup2(fileno(output), fileno(stdout));

    // Call the function
    int result = hello();

    // Restore stdout and close the file
    fflush(stdout);
    dup2(stdout_fd, fileno(stdout));
    close(stdout_fd);
    fclose(output);

    // Read the output file
    output = fopen("/tmp/test_hello_output.txt", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), output);
    fclose(output);

    // Check the output and return value
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_STRING_EQUAL(buffer, "Hello World\n");

    // Clean up
    remove("/tmp/test_hello_output.txt");
    return;
}
