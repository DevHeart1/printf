#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/*Flags*/
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/*size*/
#ifdef __SIZEOF_LONG__
#define S_LONG __SIZEOF_LONG__
#else
#define S_LONG 2
#endif

#ifdef __SIZEOF_SHORT__
#define S_SHORT __SIZEOF_SHORT__
#else
#define S_SHORT 1
#endif

/**
 * struct fmt - struct
 *
 * @format: format
 * @func: function associated
 */

struct fmt
{
	char format;
	int (*func)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - struct
 *
 * @format: format
 * @fmt_t: function associated
 */

typedef struct fmt fmt_t;

/*These prototypes are for printf functions*/
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *index, va_list lists, char buff[],
		int flags, int width, int precision, int size);

/*These Functions handles other specifiers*/
int fetch_flags(const char *format, int *q);
int fetch_width(const char *format, int *q, va_list lists);
int fetch_precision(const char *format, int *i, va_list args);
int fetch_size(const char *format, int *i);

/********* FUNCTIONS ***************/

/* These Funtions prints characters and strings */
int print_character(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_string(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_percentage(va_list lists, char buff[],
		int flags, int width, int precision, int size);


/* These Functions prints numbers */
int print_integer(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_binaryNum(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_unsignedNum(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_octalNum(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_hexadecimal(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_hexaNum_upper(va_list lists, char buff[],
		int flags, int width, int precision, int size);
int print_hexaNum(va_list lists, char map_to[],
		char buff[], int flags, char flagCh, int width, int precision, int size);

/* This Function prints non printable characters */
int print_the_unprintable(va_list lists, char buff[],
		int flags, int width, int precision, int size);

/* This Funcion prints memory address */
int prints_thepointer(va_list lists, char buff[],
		int flags, int width, int precision, int size);

/*This Function prints string in reverse*/
int print_reverse_str(va_list lists, char buff[],
		int flags, int width, int precision, int size);

/*This is a Function to print a string in rot 13*/
int print_the_rot13string(va_list lists, char buff[],
		int flags, int width, int precision, int size);

/* These are width handlers */
int handle_write_char(char s, char buff[],
		int flags, int width, int precision, int size);
int write_number(int is_positive, int index, char buff[],
		int flags, int width, int precision, int size);
int write_the_num(int ind, char buff[], int flags,
		int width, int prec, int length, char padd, char extra_c);
int write_the_pointer(char buff[], int index, int length,
		int width, int flags, char padd, char extra_c, int padd_start);

int write_the_unsignd(int is_negative, int index,
		char buff[],
		int flags, int width, int precision, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);
#endif /*MAIN_H*/
