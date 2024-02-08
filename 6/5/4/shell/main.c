#include "shell.h"
int main(void) {
    char *input;
    char *command;
    char *cmd;
    char *args[MAX_INPUT_SIZE];

    while (1) {
        printf("$ ");
        fflush(stdout);

        
	read_cmd(input);
        parse_cmd(input, args);

	if (strcmp(args[0], "exit") == 0)
		break;

	if (strcmp(args[0], "env") == 0)
		print_env();

	if (commandExists(args[0]))
	{
        // Execute the command
	execute_cmd(args[0], args);
	}
	else
	{
		printf("%s: command not found\n", command);
	}
    }
    return 0;
}
