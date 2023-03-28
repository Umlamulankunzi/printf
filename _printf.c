#include "main.h"



/**
 * _printf - Format and print data
 * @fmt: fmt.
 * Return: number of bytes printed.
 */
int _printf(const char *fmt, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_index = 0;

	va_list list;
	char buffer[BUFFER_SIZE];

	if (fmt == NULL)
		return (-1);

	va_start(list, fmt);
	for (i = 0; fmt && fmt[i] != '\0'; i++)
	{
		if (fmt[i] != '%')
		{
			buffer[buff_index++] = fmt[i];
			if (buff_index == BUFFER_SIZE)
				print_buffer(buffer, &buff_index);
			/* write(1, &fmt[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(fmt, &i);
			width = get_width(fmt, &i, list);
			precision = get_precision(fmt, &i, list);
			size = get_size(fmt, &i);
			++i;
			printed = implement_print(fmt, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buff_index);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_index: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index = 0;
}
