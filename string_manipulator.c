#include "main.h"

/**
 * prints_thepointer - Prints the value of a pointer variable
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculates the current flags
 * @width: get width
 * @precision: Precision specification
 * @size: Specifies the size
 * Return: The number of characters that is printed
 */
int prints_thepointer(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	char extras = 0, padding = ' ';
	int q = BUFF_SIZE - 2, len = 2, padding_start = 1;
	unsigned long number_addrs;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(lists, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	number_addrs = (unsigned long)address;

	while (number_addrs > 0)
	{
		buff[q--] = map_to[number_addrs % 16];
		number_addrs /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (flags & F_PLUS)
		extras = '+', len++;
	else if (flags & F_SPACE)
		extras = ' ', len++;

	q++;

	return (write_the_pointer(buff, q, len, width, flags,
	padding, extras, padding_start));
}

/**
 * print_the_unprintable - Prints ascii codes in hexa of non printable chars
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculates the current flags
 * @width: get width
 * @precision: Precision specification
 * @size: Specifies the size
 * Return: The number of characters that is printed
 */
int print_the_unprintable(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	int index = 0, offsett = 0;
	char *strng = va_arg(lists, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strng == NULL)
		return (write(1, "(null)", 6));

	while (strng[index] != '\0')
	{
		if (is_printable(strng[index]))
			buff[index + offsett] = strng[index];
		else
			offsett += append_hexa_code(strng[index], buff, index + offsett);
		index++;
	}

	buff[index + offsett] = '\0';

	return (write(1, buff, index + offsett));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse_str - Prints a reverse string.
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculates the current flags
 * @width: get width
 * @precision: Precision specification
 * @size: Specifies the size
 * Return: The number of characters that is printed
 */
int print_reverse_str(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	char *strng;
	int n, q, char_count = 0;

	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	strng = va_arg(lists, char *);

	if (strng == NULL)
	{
		UNUSED(precision);
		strng = ")Null(";
	}

	for (n = 0; strng[n]; n++)
		;

	for (q = n - 1; q >= 0; q--)
	{

		char s = strng[q];

		write(1, &s, 1);

		char_count++;

	}
	return (char_count);
}

/**
 * print_the_rot13string - Print strings in rot13.
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculates the current flags
 * @width: get width
 * @precision: precision specification
 * @size: Specifies the size
 * Return: The number of characters that is printed
 */
int print_the_rot13string(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	char s;
	char *strng;
	unsigned int q, n = 0;
	int char_count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	strng = va_arg(lists, char *);
	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strng == NULL)
		strng = "(AHYY)";
	for (q = 0; strng[q]; q++)
	{

		while (in[n])
		{
			if (in[n] == strng[q])
			{
				s = out[n];
				write(1, &s, 1);
				char_count++;
				break;
			}
			n++;
		}
		if (!in[n])
		{
			s = strng[q];
			write(1, &s, 1);
			char_count++;
		}
	}
	return (char_count);
}
