#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @fmt: Formatted string to print the args
 * @i: arguments to be printed.
 * @list: list of arguments.
 * Return: int precision.
 */
int get_precision(const char *fmt, int *i, va_list list)
{
	int index = *i + 1;
	int precision = -1;

	if (fmt[index] != '.')
		return (precision);

	precision = 0;

	for (index += 1; fmt[index] != '\0'; index++)
	{
		if (is_digit(fmt[index]))
		{
			precision *= 10;
			precision += fmt[index] - '0';
		}
		else if (fmt[index] == '*')
		{
			index++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = index - 1;
	return (precision);
}
