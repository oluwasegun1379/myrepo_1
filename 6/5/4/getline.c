#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *custom_getline() {
    static char buffer[BUFFER_SIZE];  // Static buffer to read input
    static size_t buffer_pos = 0;     // Position in the buffer
    static ssize_t bytes_read = 0;    // Number of bytes read from stdin
    static ssize_t line_len = 0;      // Current length of the line

    char *line = NULL;                // Pointer to store the line
    size_t line_size = 0;              // Size of the line

    while (1) {
        // Check if the buffer is empty or needs to be refilled
        if (buffer_pos == bytes_read) {
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            buffer_pos = 0;

            if (bytes_read == 0)
                break;  // End of input reached
            else if (bytes_read == -1)
                return NULL;  // Error occurred
        }

        // Find the end of the line in the buffer
        while (buffer_pos < bytes_read) {
            if (buffer[buffer_pos] == '\n') {
                line[line_len] = '\0';  // Null-terminate the line
                buffer_pos++;
                return line;  // Line complete, return it
            } else {
                // Append the character to the line
                line_size++;
                line = realloc(line, line_size);
                line[line_len] = buffer[buffer_pos];
                line_len++;
                buffer_pos++;
            }
        }
    }

    if (line != NULL)
        line[line_len] = '\0';  // Null-terminate the line

    return line;  // End of input reached, return the line (NULL if no input)
}

int main() {
    printf("Enter a line: ");
    fflush(stdout);

    char *line = custom_getline();

    if (line != NULL) {
        printf("Read line: %s\n", line);
        free(line);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}

