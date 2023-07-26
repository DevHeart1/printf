#include "main.h"

/**
 * print_character - This Prints character
 * @lists: This List all arguments
 * @buff: This represents Buffer array
 * @flags:  This Calculates the active flags
 * @width: This represents Width
 * @precision: This represents Precision specification
 * @size: This represents the Size specifier
 * Return: Number of characters printed
 */
int print_character(va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(lists, int);

	return (handle_write_char(c, buff, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - This Prints a string
 * @lists: This List all arguments
 * @buff: This represents Buffer array
 * @flags:  This Calculates the active flags
 * @width: This represents Width
 * @precision: This represents Precision specification
 * @size: This represents the Size specifier
 * Return: Number of characters printed
 */

int print_string(va_list lists, char buff[],
	int flags, int width, int precision, int size)
{
	int length = 0, q;
	char *str = va_arg(lists, char *);

	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 7)
			str = "       ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (q = width - length; q > 0; q--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (q = width - length; q > 0; q--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percentage - This Prints percentage symbol
 * @lists: This List all arguments
 * @buff: This represents Buffer array
 * @flags:  This Calculates the active flags
 * @width: This represents Width
 * @precision: This represents Precision specification
 * @size: This represents the Size specifier
 * Return: Number of characters printed
 */
int print_percentage(va_list lists, char buff[],
	int flags, int width, int precision, int size)
{
	UNUSED(lists);
	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INTEGER *************************/
/**
 * print_integer - This Prints integer
 * @lists: This List all arguments
 * @buff: This represents Buffer array
 * @flags:  This Calculates the active flags
 * @width: This represents Width
 * @precision: This represents Precision specification
 * @size: This represents the Size specifier
 * Return: Number of characters printed
 */

int print_integer(va_list lists, char buff[],
	int flags, int width, int precision, int size)
{
	int q = BUFF_SIZE - 2;
	int isNegative = 0;
	long int m = va_arg(lists, long int);
	unsigned long int num;

	m = convert_size_number(m, size);

	if (m == 0)
		buff[q--] = '0';

	buff[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		isNegative = 1;
	}

	while (num > 0)
	{
		buffer[q--] = (num % 10) + '0';
		num /= 10;
	}
	q++;

	return (write_number(isNegative, q, buff, flags, width, precision, size));
}

/************************* PRINT BINARY Numbers *************************/
/**
 * print_binaryNum - This Prints an unsigned number
 * @lists: This List all arguments
 * @buff: This represents Buffer array
 * @flags:  This Calculates the active flags
 * @width: This represents Width
 * @precision: This represents Precision specification
 * @size: This represents the Size specifier
 * Return: Number of characters printed
 */

int print_binaryNum(va_list lists, char buff[],
	int flags, int width, int precision, int size)
{
	unsigned int p, m, q, sum = 0;
	unsigned int a[32];
	int count = 0;

	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	p = va_arg(lists, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = p / m;

	for (q = 1; q < 32; q++)
	{
		m /= 2;
		a[i] = (p / m) % 2;
	}

	for (q = 0; q < 32; q++)
	{
		sum += a[q];

		if (sum || q == 31)
		{
			char k = '0' + a[i];

			write(1, &k, 1);
			count++;
		}
	}

	return (count);
}
