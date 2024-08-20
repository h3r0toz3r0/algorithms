/**
 * @file    test_auxiliary.h
 * @brief   Header file for `test_auxiliary.c`.
 *
 * @author  Anna DeVries
 * @date    August 20, 2024
 */

#ifndef TEST_AUXILIARY_H
#define TEST_AUXILIARY_H

#include <stdbool.h>

/**
 * @brief Provides global error logging.
 * 
 * This definition allows additional arguments to be passed as an option.
 */
#define ERROR_LOG(fmt, ...) fprintf(stderr, "\n[Error]: " fmt "\n", ##__VA_ARGS__)


/**
 * @brief Captures the stdout output of a given function.
 *
 * This function redirects stdout to a temporary file, executes the specified
 * function, and captures its output. The output is returned as a dynamically
 * allocated string, which must be freed by the caller.
 *
 * @param func Pointer to the function whose stdout output needs to be captured.
 * @return char* Pointer to the captured output, or NULL if an error occurred.
 */
char* 
capture_stdout(int (*func)(void));

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
bool
is_name_match (const char *string_1, const char *string_2);

#endif // TEST_AUXILIARY_H
