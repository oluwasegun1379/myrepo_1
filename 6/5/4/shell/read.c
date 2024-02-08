#include "shell.h"
size_t read_cmd(char **cmd) {
    size_t bufsize = 0;
    ssize_t cmdlen = 0;

    cmdlen = _getline(cmd, &bufsize, stdin);
    if (cmdlen == -1) {
        perror("getline");
        return NULL;
    }

    // Remove the trailing newline character, if present
    if (*cmd[cmdlen - 1] == '\n')
        *cmd[cmdlen - 1] = '\0';
    return cmdlen;
}
