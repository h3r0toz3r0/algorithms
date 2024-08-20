// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>

// #define OUTPUT_BUFFER_SIZE 256

// // Function to capture stdout output
// char* capture_stdout(int (*func)(void)) {
//     int stdout_fd = dup(fileno(stdout));  // Save the current stdout
//     FILE *temp_file = fopen("/tmp/test_output.txt", "w");
//     if (!temp_file) {
//         perror("Failed to open temporary output file");
//         return NULL;
//     }
//     dup2(fileno(temp_file), fileno(stdout));  // Redirect stdout to the temp file

//     // Execute the function and capture output
//     int result = func();

//     fflush(stdout);  // Ensure all output is flushed to the file
//     dup2(stdout_fd, fileno(stdout));  // Restore original stdout
//     close(stdout_fd);
//     fclose(temp_file);

//     // Read the output from the file
//     temp_file = fopen("/tmp/test_output.txt", "r");
//     if (!temp_file) {
//         perror("Failed to open temporary output file for reading");
//         return NULL;
//     }
//     char *output = (char *)malloc(OUTPUT_BUFFER_SIZE);
//     if (!output) {
//         perror("Failed to allocate memory for output");
//         fclose(temp_file);
//         return NULL;
//     }
//     fgets(output, OUTPUT_BUFFER_SIZE, temp_file);
//     fclose(temp_file);

//     // Clean up
//     remove("/tmp/test_output.txt");
//     return output;
// }