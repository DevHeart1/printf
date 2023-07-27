#include "main.h"

/*************** PRINTS POSITIVE NUMBER **********************/
/**
 * print_unsignedNum - Prints a positive number
 * @lists: contains the list of variadic arguments
 * @buff: the buff array to handle the printing
 * @flags: It checks for flag numbers if any
 * @width: get the width of the printing
 * @precision: Precision specification
 * @size: specifys the size of operation
 * Return: Number of characters printed.
 */

int print_unsignedNum(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	int q = BUFF_SIZE - 2;
	unsigned long int m = va_arg(lists, unsigned long int);

	m = convert_size_unsgnd(m, size);

	if (m == 0)
		buff[q--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (m > 0)
	{
		buff[q--] = (m % 10) + '0';
		q /= 10;
	}

	q++;

	return (write_the_unsignd(0, q, buff, flags, width, precision, size));
}

/************* PRINT POSITIVE NUMBER IN OCTAL ***************/
/**
 * print_octalNum - Prints an positive number in octal
 * @lists: contains the list of argument
 * @buff: the buff array to handle the printing
 * @flags: It checks for flag numbers if any
 * @width: get the width of the printing
 * @precision: Precision specification
 * @size: specifys the size of operation
 * Return: Number of characters printed.
 */

int print_octalNum(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	int q = BUFF_SIZE - 2;
	unsigned long int m = va_arg(lists, unsigned long int);
	unsigned long int num_to_convert = m;

	UNUSED(width);
	m = convert_size_unsgnd(m, size);

	if (m == 0)
		buff[q--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (m > 0)
	{
		buff[q--] = (m % 8) + '0';
		m /= 8;
	}

	if (flags & F_HASH && num_to_convert != 0)
		buff[q--] = '0';
	q++;

	return (write_the_unsignd(0, q, buff, flags, width, precision, size));
}

/************** PRINT POSITIVE NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculate the current flags
 * @width: get the width of the printing
 * @precision: get the width of the printing
 * @size: specifys the size of operation
 * Return: Number of characters printed.
 */
int print_hexadecimal(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	return (print_hexaNum(lists, "0123456789abcdef", buff,
				flags, 'x', width, precision, size));
}

/************* PRINT POSITIVE NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexaNum_upper - Prints an  number in upper hexadecimal notation
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculate the current flags
 * @width: get width
 * @precision: Precision specification
 * @size: Specifies the size
 * Return: The number of characters that is printed
 */
int print_hexaNum_upper(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	return (print_hexaNum(lists, "0123456789ABCDEF", buff,
				flags, 'X', width, precision, size));
}

/************** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER **************/
/**
 * print_hexaNum - Prints a hexadecimal number in lower or upper
 * @lists: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buff: Buff array to handle print
 * @flags: Calculates active flags
 * @flagCh: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */

int print_hexaNum(va_list lists, char map_to[], char buff[],
		int flags, char flagCh, int width, int precision, int size)
{
	int q = BUFF_SIZE - 2;
	unsigned long int m = va_arg(lists, unsigned long int);
	unsigned long int num_to_convert = m;

	UNUSED(width);

	m = convert_size_unsgnd(m, size);

	if (m == 0)
		buff[q--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (m > 0)
	{
		buff[q--] = map_to[m % 16];
		m /= 16;
	}

	if (flags & F_HASH && num_to_convert != 0)
	{
		buff[q--] = flagCh;
		buff[q--] = '0';
	}

	q++;

	return (write_the_unsignd(0, q, buff, flags, width, precision, size));
}
