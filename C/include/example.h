/**
 * @file    example.h
 * @brief   Header file for `example.c`.
 *
 * @author  Anna DeVries
 * @date    August 17, 2024
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

/**
 * @brief   Prints "Hello World" to the console.
 *
 * This function outputs the string "Hello World" to the standard output using
 * the `printf` function from the C standard library. It returns 0 to indicate
 * successful execution.
 *
 * @return  Returns 0 on success.
 *
 * @example
 * @code
 * #include "hello.h"
 * 
 * int main() {
 *     hello();
 *     return 0;
 * }
 * @endcode
 */
int hello();

#endif // EXAMPLE_H
