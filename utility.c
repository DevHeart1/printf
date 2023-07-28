#include "main.h"

/**
 * is_printable - This function Evaluates if a character is printable
 * @s: Represents Character to be evaluated.
 * Return: 1 if c is printable, 0 if not
 */

int is_printable(char s)
{
	if (s >= 32 && s < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - This Appends ascci in hexadecimal code to buffer
 * @buff: This represents Array of chars.
 * @q: Index at which to start appending.
 * @ascii_code: ASSCI code.
 * Return: Always 3.
 */

int append_hexa_code(char ascii_code, char buff[], int q)
{
	char mapTo[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buff[q++] = '\\';
	buff[q++] = 'x';

	buff[q++] = mapTo[ascii_code / 16];
	buff[q++] = mapTo[ascii_code % 16];

	return (3);
}

/**
 * is_digit - This Verifies if a character is a digit
 * @s: Represents Character to be evaluated
 * Return: 1 if c is a digit, 0 if not
 */

int is_digit(char s)
{
	if (s >= 48 && s <= 57)
		return (1);

	return (0);
}

/**
 * convert_size_number - This Casts a number to the specified size
 * @num: Represents Number to be casted.
 * @size: This represents Number indicating the type to be casted.
 * Return: Casted value of num
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - This Casts a number to the specified size
 * @num: Represents Number to be casted
 * @size: Represents Number indicating the type to be casted
 * Return: Casted value of num
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
