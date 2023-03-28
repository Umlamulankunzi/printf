#include "main.h"


/**
 * put_char - Prints single char
 * @args: arguments list
 * @buffer: Buffer array
 * @flags:  finds active flags
 * @width: Width
 * @precision: Precision handling
 * @size: Size specifier
 * Return: number of chars printed
 */
int put_char(va_list args, char *buffer,
	int flags, int width, int precision, int size)
{
	char ch = va_arg(args, int);

	return (write_string(ch, buffer, flags, width, precision, size));
}


/**
 * put_string - Print a string
 * @args: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int put_string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (*(str + len) != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags && FL_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}


/**
 * print_percent - Prints a percent sign
 * @args: arguments list
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision handling
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}



/**
 * put_int - Print int
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int put_int(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}


/**
 * put_binary - Prints an unsigned number
 * @args: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision handling
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int put_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int i, j, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	i = va_arg(args, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	a[0] = i / j;
	for (k = 1; k < 32; k++)
	{
		j /= 2;
		a[k] = (i / j) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char ch = '0' + a[k];

			write(1, &ch, 1);
			count++;
		}
	}
	return (count);
}
