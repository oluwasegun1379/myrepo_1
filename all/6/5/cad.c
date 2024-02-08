#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

int wildcard_match(const char *str, const char *pattern);
void handle_wildcard(const char *pattern);

int wildcard_match(const char *str, const char *pattern) {
    while (*str && *pattern != '*') {
        if (*pattern != *str && *pattern != '?')
            return 0;

        pattern++;
        str++;
    }

    const char *mp = NULL;
    const char *cp = NULL;

    while (*str) {
        if (*pattern == '*') {
            if (!*++pattern)
                return 1;

            mp = pattern;
            cp = str + 1;
        } else if (*pattern == *str || *pattern == '?') {
            pattern++;
            str++;
        } else {
            pattern = mp;
            str = cp++;
        }
    }

    while (*pattern == '*')
        pattern++;

    return !*pattern;
}

void handle_wildcard(const char *pattern) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (wildcard_match(entry->d_name, pattern))
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *pattern = (argc == 2) ? argv[1] : "*";
    handle_wildcard(pattern);
    return 0;
}

