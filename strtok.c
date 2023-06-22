#include "monty.h"
char *__strtok(char *string, const char *deli, char **save_ptr)
{
	int i , j, found;
	char *word = NULL, *end = NULL;

	if (string != NULL)
	{
		*save_ptr = string;
	}

	if (*save_ptr == NULL || **save_ptr == '\0')
	{
		return (NULL);
	}

	while (**save_ptr == ' ')
	{
		(*save_ptr)++;
	}

	word = *save_ptr;
	i = 0;
	found = 0;
	while (word[i] != '\0')
	{
		for (j = 0; deli[j] != '\0'; j++)
		{
			if (word[i] == deli[j])
			{
				word[i] = '\0';
				*save_ptr = &word[i + 1];
				found = 1;
				break;
			}
		}
		if (found)
		{
			break;
		}
		i++;
	}
	if (!found)
	{
		*save_ptr = NULL;
	}
	end = word + strlen(word) - 1;
	while (end > word && *end == ' ')
	{
		*end = '\0';
		end--;
	}
	return (word);
}
