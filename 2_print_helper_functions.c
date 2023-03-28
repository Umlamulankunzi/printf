#include "main.h"


/**
 * put_unsigned - Print unsigned number
 * @types: arguments list
 * @buffer: Buffer array
 * @flags: Calculates active flags
 * @width: width
 * @precision: Precision handling
 * @size: Size specifier
 * Return: int
 */
int put_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


/**
 * put_octal - Prints an unsigned number in octal notation
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: width
 * @precision: Precision handling
 * @size: Size specifier
 * Return: int
 */
int put_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & FL_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


/**
 * put_hexadecimal - Print unsigned number in hexadecimal
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: width
 * @precision: Precision handling
 * @size: Size specifier
 * Return: int
 */
int put_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (put_hexadec_anycase(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}


/**
 * put_hexadecimal_upper - Print unsigned number in upper hexadecimal
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: width
 * @precision: Precision handling
 * @size: Size specifier
 * Return: Number of chars printed
 */
int put_hexadecimal_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (put_hexadec_anycase(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}


/**
 * put_hexadec_anycase - Print hexadecimal number lower or upper case
 * @types: arguments list
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array
 * @flags: flag int
 * @flag_ch: flag char
 * @width: width
 * @precision: Precision handling
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int put_hexadec_anycase(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & FL_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
