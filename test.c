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
/**
 * pint - Prints the value at the top of the stack
 * @stack: Double pointer to the stack
 * @line_number: Line number of the instruction in the file
 */
void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}

int main(int argc, char *argv[])
{
	char *filename;
	char *line = NULL;
	char *opcode;
	char *arg;
	char *save_ptr;
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

        while (custom_getline(&line, &len, file) != (ssize_t)-1)
        {
                line_number++;
                opcode = __strtok(line, " \t\n", &save_ptr);

                if (opcode != NULL && strcmp(opcode, "push") == 0)
                {
                        arg = __strtok(NULL, " \t\n", &save_ptr);
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
		else
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free(line);
			free_stack(stack);
			fclose(file);
			exit(EXIT_FAILURE);
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
