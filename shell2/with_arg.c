#include "shell.h"

/**
 * with_arg - Execute commands with arguments
 * @line: pointer to the input command
 *
 * Execute the command with arguments using the system function,
 * and print an error message if the command is not found.
 */
void with_arg(char *line) {
    if (strchr(line, '/') != NULL) {
        int status = system(line);  // Execute the command using system

        if (status == -1) {
            printf("./shell: No such file or directory\n");  // Handle command not found error
        }
    }
    else
	    printf("./shell: No such file or directory\n");

}

