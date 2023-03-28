#ifndef MAIN_H
#define MAIN_H

/* INCLUDES */
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define UNUSED(x) (void)(x)

/* FLAGS */
#define FL_HASH 8
#define FL_MINUS 1
#define FL_PLUS 2
#define FL_SPACE 16
#define FL_ZERO 4

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - format structure
 * @fmt: The format.
 * @fn: function pointer associated with fmt
 */
typedef struct fmt
{
	char fmt;
	int (*fn)(va_list, char*, int, int, int, int);
} fmt_struct;

/****************** MAIN FUNCTIONS *************/
int _printf(const char *format, ...);
void print_buffer(char buffer[], int *buff_index);
int implement_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);


/****************** FUNCTIONS ******************/
/* Funtions to print chars and strings */
int put_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int put_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int put_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int put_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int put_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int put_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int put_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int put_hexadecimal_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int put_hexadec_anycase(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int put_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int put_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int put_str_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int put_str_rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int write_string(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
