#include "main.h"


/**
 * put_pointer - Prints the value of a pointer variable
 * @types: arguments list
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision handle
 * @size: Size specifier
 * Return: int number of chars printed.
 */
int put_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char add_char = 0, pad = ' ';
	int index = BUFFER_SIZE - 2, padd_start = 1;
	int len = 2;  /* Account for -> '0x' */
	unsigned long address;
	char ptr_chars[] = "0123456789abcdef";
	void *vptr_addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (vptr_addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	address = (unsigned long)vptr_addrs;

	while (address > 0)
	{
		buffer[index--] = ptr_chars[address % 16];
		address /= 16;
		len++;
	}

	if ((flags & FL_ZERO) && !(flags & FL_MINUS))
		pad = '0';
	if (flags & FL_PLUS)
		add_char = '+', len++;
	else if (flags & FL_SPACE)
		add_char = ' ', len++;

	index++;
	return (write_pointer(buffer, index, len,
		width, flags, pad, add_char, padd_start));
}


/**
 * put_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: arguments list
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision handle
 * @size: Size specifier
 * Return: int number of chars printed.
 */
int put_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';
	return (write(1, buffer, i + offset));
}


/**
 * put_str_reverse - Prints string in reverse.
 * @types: arguments list
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision handle
 * @size: Size specifier
 * Return: int number of chars printed.
 */

int put_str_reverse(va_list types, char *buffer,
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}


/**
 * put_str_rot13 - Print string in rot13 format.
 * @types: arguments list
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision handle
 * @size: Size specifier
 * Return: int number of chars printed.
 */
int put_str_rot13(va_list types, char *buffer,
	int flags, int width, int precision, int size)
{
	char ch;
	char *str;
	unsigned int i, j;
	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == str[i])
			{
				ch = output[j];
				write(1, &ch, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			ch = str[i];
			write(1, &ch, 1);
			count++;
		}
	}
	return (count);
}
