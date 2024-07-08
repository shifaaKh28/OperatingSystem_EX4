#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Main function to concatenate all command-line arguments into a single string.
 *
 * This program dynamically allocates memory to store the concatenated
 * command-line arguments and prints the resulting string. The program
 * ensures proper memory management and handles memory allocation failures.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status of the program.
 */
int main(int argc, char *argv[]) {
    char *string = NULL, *string_so_far = NULL;
    int i, length = 0;

    // Loop through each command-line argument
    for (i = 0; i < argc; i++) {
        // Calculate the required length for the new string
        length += strlen(argv[i]) + 1;

        // Allocate memory for the new string
        string = malloc(length + 1);
        if (string == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        // Copy the string built so far to the newly allocated memory
        if (string_so_far != NULL) {
            strcpy(string, string_so_far);
            // Free the old memory
            free(string_so_far);
        } else {
            // Initialize the new string if no previous string exists
            *string = '\0';
        }

        // Concatenate the current argument to the new string
        strcat(string, argv[i]);
        if (i < argc - 1) {
            // Add a space between arguments
            strcat(string, " ");
        }

        // Update the pointer to the new string
        string_so_far = string;
    }

    // Print the concatenated string
    printf("You entered: %s\n", string_so_far);

    // Free the final allocated memory
    free(string_so_far);

    return 0;
}

/**
 * Documentation of Changes:
 *
 * 1. Initialization of `string_so_far`:
 *    char *string = NULL, *string_so_far = NULL;
 *    - Both `string` and `string_so_far` are initialized to `NULL`.
 *
 * 2. Memory Allocation:
 *    string = malloc(length + 1);
 *    if (string == NULL) {
 *        fprintf(stderr, "Memory allocation failed\n");
 *        exit(1);
 *    }
 *    - Allocates memory for `string` with the required length.
 *    - Checks if `malloc` returns `NULL` and handles the failure by printing an error message and exiting.
 *
 * 3. Copying and Freeing Memory:
 *    if (string_so_far != NULL) {
 *        strcpy(string, string_so_far);
 *        free(string_so_far);
 *    } else {
 *        *string = '\0';
 *    }
 *    - Copies the content of `string_so_far` to `string`.
 *    - Frees the previously allocated memory pointed to by `string_so_far`.
 *    - Initializes `string` to an empty string if `string_so_far` is `NULL`.
 *
 * 4. Concatenation and Update:
 *    strcat(string, argv[i]);
 *    if (i < argc - 1) {
 *        strcat(string, " ");
 *    }
 *    string_so_far = string;
 *    - Concatenates the current argument `argv[i]` to `string`.
 *    - Adds a space between arguments if it is not the last argument.
 *    - Updates `string_so_far` to point to the newly allocated and concatenated `string`.
 *
 * 5. Final Cleanup:
 *    printf("You entered: %s\n", string_so_far);
 *    free(string_so_far);
 *    - Prints the final concatenated string.
 *    - Frees the memory allocated to `string_so_far` to prevent memory leaks.
 *
 * Summary:
 *
 * These changes ensure that memory is properly allocated and freed, preventing memory leaks and handling allocation failures.
 * The code is now robust and efficient in handling command-line arguments and dynamically managing memory.
 */
