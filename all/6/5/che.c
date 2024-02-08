#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Run a command that sets the exit status
    int ret = system("ls /nonexistent");

    // Get the exit status using wait()
    int status;
    wait(&status);
    int exit_status = WEXITSTATUS(status);

    // Print the exit status
    printf("%dn", exit_status);

    return exit_status;
}

