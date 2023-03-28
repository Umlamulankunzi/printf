#include "main.h"


/**
 * get_flags - get flags from fmt string
 * @format: Formatted string to print the args
 * @i: parameter.
 * Return: number of flags
 */
int get_flags(const char *format, int *i)
{
	int j, index;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {
		FL_MINUS, FL_PLUS, FL_ZERO, FL_HASH, FL_SPACE, 0};

	for (index = *i + 1; format[index] != '\0'; index++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[index] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = index - 1;
	return (flags);
}
