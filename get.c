#include "monty.h"
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
        size_t pos = 0;
        int c;
        char *new_lineptr;

        if (*lineptr == NULL || *n == 0)
        {
                *n = 128;
                *lineptr = malloc(*n * sizeof(char));
                if (*lineptr == NULL)
                        return -1;
        }

        while ((c = fgetc(stream)) != EOF)
        {
                if (pos >= *n - 1)
                {
                        *n *= 2;
                        new_lineptr = realloc(*lineptr, *n * sizeof(char));
                        if (new_lineptr == NULL)
                                return -1;
                        *lineptr = new_lineptr;
                }

                (*lineptr)[pos++] = c;

                if (c == '\n')
                        break;
        }

        (*lineptr)[pos] = '\0';

        return pos;
}
