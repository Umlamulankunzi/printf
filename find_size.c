#include "main.h"

/**
 * get_size - Calculate size to cast argument
 * @format: Formatted string to print the arguments
 * @i: arguments to be printed.
 * Return: size.
 */
int get_size(const char *format, int *i)
{
	int index = *i + 1;
	int size = 0;

	if (format[index] == 'l')
		size = S_LONG;
	else if (format[index] == 'h')
		size = S_SHORT;
	if (size == 0)
		*i = index - 1;
	else
		*i = index;

	return (size);
}
