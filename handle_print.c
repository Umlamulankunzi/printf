#include "main.h"



/**
 * implement_print - prints argument based type
 * @fmt: Formatted string to print arguments.
 * @list: of arguments list to be printed.
 * @index: index.
 * @buffer: Buffer array.
 * @flags: int flags
 * @width: width.
 * @precision: Precision handler
 * @size: Size specifier
 * Return: 1 or 2;
 */
int implement_print(const char *fmt, int *index, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, len = 0, printed_chars = -1;
	fmt_struct fmt_types[] = {
		{'c', put_char}, {'s', put_string},
		{'%', print_percent}, {'i', put_int},
		{'d', put_int}, {'b', put_binary},
		{'u', put_unsigned}, {'o', put_octal},
		{'x', put_hexadecimal}, {'X', put_hexadecimal_upper},
		{'p', put_pointer}, {'S', put_non_printable},
		{'r', put_str_reverse}, {'R', put_str_rot13},
		{'\0', NULL}
	};

	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*index] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		len += write(1, &fmt[*index], 1);
		return (len);
	}
	return (printed_chars);
}
