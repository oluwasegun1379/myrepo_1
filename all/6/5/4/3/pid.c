#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[100];
    while (1) {
        printf("$ "); // display the prompt
        fgets(input, sizeof(input), stdin); // read user input
        input[strcspn(input, "\n")] = '\0'; // remove the newline character

	char *ptr = strtok(input, " ");
	while (ptr != NULL)
	{
		char *ag = ptr;
		ptr = strtok(NULL, " ");
	}
	
        pid_t pid = fork(); // create a child process
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // child process
            if (access(input, X_OK) == -1) { // check if the file is executable
                perror(input);
                exit(1);
            }
            char *ag[] = {input, NULL};
            execve(input, ag, environ); // execute the command
            perror("execve");
            exit(1);
        } else {
            // parent process
            waitpid(pid, NULL, 0); // wait for the child to complete
        }
    }
    return 0;
}
