#include "shell.h"
ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
    ssize_t nread;
    size_t len = 0;
    char *buf = NULL;

    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    if (*lineptr == NULL) {
        *n = 120;
        buf = malloc(*n);
        if (buf == NULL) {
            return -1;
        }
        *lineptr = buf;
    } else {
        buf = *lineptr;
    }

    while ((nread = read(fileno(stream), buf + len, *n - len)) > 0) {
        len += (size_t) nread;
        if (len >= *n) {
            *n *= 2;
            buf = realloc(*lineptr, *n);
            if (buf == NULL) {
                return -1;
            }
            *lineptr = buf;
        }
        if (buf[len - 1] == '\n') {
            break;
        }
    }

    if (nread == -1) {
        return -1;
    }

    if (len == 0) {
        return -1;
    }

    buf[len] = '\0';

    return (ssize_t) len;
}

