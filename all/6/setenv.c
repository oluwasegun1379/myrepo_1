#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to set an environment variable
int set_env_variable(const char *name, const char *value) {
    // Check if both name and value are provided
    if (name == NULL || value == NULL) {
        printf("Usage: setenv <name> <value>\n");
        return 1;
    }
    
    // Set the environment variable using the setenv function
    int result = setenv(name, value, 1);
    
    // Check if setenv was successful
    if (result != 0) {
        printf("Error setting environment variable.\n");
        return 1;
    }
    
    printf("Environment variable '%s' set to '%s'\n", name, value);
    
    // Print the current value of the environment variable
    char *env_value = getenv(name);
    if (env_value != NULL) {
        printf("Current value of '%s' is '%s'\n", name, env_value);
    } else {
        printf("'%s' is not set.\n", name);
    }
    
    return 0;
}

// Function to unset an environment variable
int unset_env_variable(const char *name) {
    // Check if name is provided
    if (name == NULL) {
        printf("Usage: unsetenv <name>\n");
        return 1;
    }
    
    // Unset the environment variable using the unsetenv function
    int result = unsetenv(name);
    
    // Check if unsetenv was successful
    if (result != 0) {
        printf("Error unsetting environment variable.\n");
        return 1;
    }
    
    printf("Environment variable '%s' unset.\n", name);
    
    // Print the current value of the environment variable
    char *env_value = getenv(name);
    if (env_value != NULL) {
        printf("Current value of '%s' is '%s'\n", name, env_value);
    } else {
        printf("'%s' is not set.\n", name);
    }
    
    return 0;
}

// ...

// Continue with the remaining code (main function, etc.)

int main() {
    char command[100];
    char *token;
    
    while (1) {
        printf("Enter a command (setenv/unsetenv): ");
        fgets(command, sizeof(command), stdin);
        
        // Remove the newline character from the input
        if (strlen(command) > 0 && command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }
        
        // Tokenize the command to extract the arguments
        token = strtok(command, " ");
        
        // Check the command type and call the appropriate function
        if (strcmp(token, "setenv") == 0) {
            // Extract the name and value arguments
            char *name = strtok(NULL, " ");
            char *value = strtok(NULL, " ");
            set_env_variable(name, value);
        } else if (strcmp(token, "unsetenv") == 0) {
            // Extract the name argument
            char *name = strtok(NULL, " ");
            unset_env_variable(name);
        } else if (strcmp(token, "exit") == 0) {
            // Exit the shell program
            break;
        } else {
            printf("Invalid command.\n");
        }
    }
    
    return 0;
}

