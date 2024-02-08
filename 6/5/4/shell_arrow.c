#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_CMD_LEN 100

void enable_raw_mode();
void disable_raw_mode();
char *read_cmd();
void handle_arrow_keys(char *cmd);

int main(void)
{
    enable_raw_mode();

    while (1)
    {
        char *cmd = read_cmd();

        if (strcmp(cmd, "exit") == 0)
            break;

        handle_arrow_keys(cmd);

        // Do something with the command
        printf("Command: %s\n", cmd);

        free(cmd);
    }

    disable_raw_mode();

    return 0;
}

void enable_raw_mode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char *read_cmd()
{
    char *cmd = malloc(MAX_CMD_LEN);
    fgets(cmd, MAX_CMD_LEN, stdin);
    int len = strlen(cmd);
    if (cmd[len - 1] == '\n')
        cmd[len - 1] = '\0';
    return cmd;
}

void handle_arrow_keys(char *cmd)
{
    const char escape = 27;
    const char left_bracket = 91;
    const char arrow_up = 65;
    const char arrow_down = 66;
    const char arrow_right = 67;
    const char arrow_left = 68;

    char c1 = getchar();

    if (c1 == escape)
    {
        char c2 = getchar();
        char c3 = getchar();

        if (c2 == left_bracket)
        {
            if (c3 == arrow_up)
            {
                // Handle arrow up key
                printf("Arrow Up\n");
            }
            else if (c3 == arrow_down)
            {
                // Handle arrow down key
                printf("Arrow Down\n");
            }
            else if (c3 == arrow_right)
            {
                // Handle arrow right key
                printf("Arrow Right\n");
            }
            else if (c3 == arrow_left)
            {
                // Handle arrow left key
                printf("Arrow Left\n");
            }
        }
    }
}

