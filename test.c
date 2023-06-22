#include "monty.h"

stack_t *stack = NULL;

void push(stack_t **stack, int value)
{
        stack_t *new_node = malloc(sizeof(stack_t));
        if (new_node == NULL)
        {
                fprintf(stderr, "Error: malloc failed\n");
                exit(EXIT_FAILURE);
        }

        new_node->n = value;
        new_node->prev = NULL;
        new_node->next = *stack;

        if (*stack != NULL)
                (*stack)->prev = new_node;

        *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
        stack_t *current;

        for (current = *stack; current != NULL; current = current->next)
                printf("%d\n", current->n);

        (void)line_number; /* Unused parameter */
}

void free_stack(stack_t *stack)
{
        stack_t *current = stack;
        while (current != NULL)
        {
                stack_t *temp = current;
                current = current->next;
                free(temp);
        }
}

size_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
        size_t pos = 0;
	char *new_lineptr;
        int c;

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

int main(int argc, char *argv[])
{
	char *filename;
	char *line = NULL;
	char *opcode;
	char *arg;
        size_t len = 0;
        unsigned int line_number = 0;
	FILE *file;

        if (argc != 2)
        {
                fprintf(stderr, "USAGE: monty file\n");
                exit(EXIT_FAILURE);
        }

        filename = argv[1];
        file = fopen(filename, "r");
        if (file == NULL)
        {
                fprintf(stderr, "Error: Can't open file %s\n", filename);
                exit(EXIT_FAILURE);
        }

        while (custom_getline(&line, &len, file) != (size_t)-1)
        {
                line_number++;
                opcode = strtok(line, " \t\n");

                if (opcode != NULL && strcmp(opcode, "push") == 0)
                {
                        arg = strtok(NULL, " \t\n");
                        if (arg == NULL || atoi(arg) == 0)
                        {
                                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                                free(line);
                                free_stack(stack);
                                fclose(file);
                                exit(EXIT_FAILURE);
                        }
                        push(&stack, atoi(arg));
                }
                else if (opcode != NULL && strcmp(opcode, "pall") == 0)
                {
                        pall(&stack, line_number);
                }
                free(line);
                line = NULL;
                len = 0;
        }

        free(line);
        free_stack(stack);
        fclose(file);
        return 0;
}