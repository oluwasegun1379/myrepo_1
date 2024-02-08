#include "shell.h"
int commandExists(const char *command)
{
    const char *path = getenv("PATH");
    char *pathCopy = strdup(path);
    char *dir = strtok(pathCopy, ":");

    while (dir != NULL) {
        // Construct the full path to the command
        char commandPath[MAX_INPUT_SIZE];
        strcpy(commandPath, dir);
        strcat(commandPath, "/");
        strcat(commandPath, command);

        if (access(commandPath, X_OK) == 0) {
            // Command exists and is executable
            return 1;
        }

        dir = strtok(NULL, ":");
    }

    // Command does not exist or is not executable
    return 0;
}
