#include <stdlib.h>
#include <stdio.h>

int main(void) {
    // Run a command
    int status = system("ls -l");

    // Check the exit status
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("Command succeededn");
    } else {
        printf("Command failedn");
    }

    return 0;
}

