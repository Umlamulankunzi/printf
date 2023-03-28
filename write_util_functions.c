#include "main.h"



/**
 * write_string - Prints a string
 * @c: char.
 * @buffer: Buffer array
 * @flags: active flags.
 * @width: get width.
 * @precision: precision handler
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int write_string(char c, char *buffer,
	int flags, int width, int precision, int size)
{
	int i = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & FL_ZERO)
		pad = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = pad;

		if (flags & FL_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}



/**
 * write_number - Prints a number
 * @is_negative: arguments list
 * @index: index
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width.
 * @precision: precision handler
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFFER_SIZE - index - 1;
	char pad = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & FL_ZERO) && !(flags & FL_MINUS))
		pad = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & FL_PLUS)
		extra_ch = '+';
	else if (flags & FL_SPACE)
		extra_ch = ' ';

	return (write_num(index, buffer, flags, width, precision,
		len, pad, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @index: Index where number starts on buffer
 * @bufr: Buffer array
 * @flags: Flags
 * @width: width
 * @prec: Precision handler
 * @len: Number len
 * @pad: Pading char
 * @add_char: Extra char
 * Return: Number of printed chars.
 */
int write_num(int index, char bufr[],
	int flags, int width, int prec,
	int len, char pad, char add_char)
{
	int i, padd_start = 1;

	if (prec == 0 && index == BUFFER_SIZE - 2 && bufr[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFFER_SIZE - 2 && bufr[index] == '0')
		bufr[index] = pad = ' ';
	if (prec > 0 && prec < len)
		pad = ' ';
	while (prec > len)
		bufr[--index] = '0', len++;
	if (add_char != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			bufr[i] = pad;
		bufr[i] = '\0';
		if (flags & FL_MINUS && pad == ' ')
		{
			if (add_char)
				bufr[--index] = add_char;
			return (write(1, &bufr[index], len) + write(1, &bufr[1], i - 1));
		}
		else if (!(flags & FL_MINUS) && pad == ' ')
		{
			if (add_char)
				bufr[--index] = add_char;
			return (write(1, &bufr[1], i - 1) + write(1, &bufr[index], len));
		}
		else if (!(flags & FL_MINUS) && pad == '0')
		{
			if (add_char)
				bufr[--padd_start] = add_char;
			return (write(1, &bufr[padd_start], i - padd_start) +
				write(1, &bufr[index], len - (1 - padd_start)));
		}
	}
	if (add_char)
		bufr[--index] = add_char;
	return (write(1, &bufr[index], len));
}


/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFFER_SIZE - index - 1, i = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFFER_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buffer[--index] = '0';
		len++;
	}

	if ((flags & FL_ZERO) && !(flags & FL_MINUS))
		pad = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = pad;

		buffer[i] = '\0';

		if (flags & FL_MINUS)
		{
			return (write(1, &buffer[index], len) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], len));
		}
	}

	return (write(1, &buffer[index], len));
}


/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @len: len of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @pad: Char representing the padding
 * @add_char: Char representing extra char
 * @padd_start: Index at which padding should start
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int index, int len,
	int width, int flags, char pad, char add_char, int padd_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & FL_MINUS && pad == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (add_char)
				buffer[--index] = add_char;
			return (write(1, &buffer[index], len) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & FL_MINUS) && pad == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (add_char)
				buffer[--index] = add_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], len));
		}
		else if (!(flags & FL_MINUS) && pad == '0')
		{
			if (add_char)
				buffer[--padd_start] = add_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[index], len - (1 - padd_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (add_char)
		buffer[--index] = add_char;
	return (write(1, &buffer[index], BUFFER_SIZE - index - 1));
}
