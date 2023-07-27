#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @s: character types.
 * @buff: Buffer array to handle print
 * @flags: Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char s, char buff[],
		int flags, int width, int precision, int size)
{
	int q = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buff[q++] = s;
	buff[q] = '\0';

	if (width > 1)
	{
		buff[BUFF_SIZE - 1] = '\0';
		for (q = 0; q < width - 1; q++)
			buff[BUFF_SIZE - q - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFF_SIZE - q - 1], width - 1));
		else
			return (write(1, &buff[BUFF_SIZE - q - 1], width - 1) +
					write(1, &buff[0], 1));
	}

	return (write(1, &buff[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buff: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */

int write_number(int is_negative, int index, char buff[],
		int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - index - 1;
	char padding = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_the_num(index, buff, flags, width, precision,
				len, padding, extra_char));
}
/**
 * write_the_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buff: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Padding character
 * @extra_ch: Extra character
 *
 * Return: Number of printed chars.
 */

int write_the_num(int index, char buff[],
		int flags, int width, int prec,
		int length, char padding, char extra_ch)
{
	int q, padding_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buff[index] == '0' && width == 0)
		return (0); /* printf(".0d", 0) no char is printed */
	if (prec == 0 && index == BUFF_SIZE - 2 && buff[index] == '0')
		buff[index] = padding = ' ';
	if (prec > 0 && prec < length)
		padding = ' ';
	while (prec > length)
		buff[--index] = '0', length++;
	if (extra_ch != 0)
		length++;
	if (width > length)
	{
		for (q = 1; q < width - length + 1; q++)
			buff[q] = padding;
		buff[q] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			if (extra_ch)
				buff[--index] = extra_ch;
			return (write(1, &buff[index], length) + write(1, &buff[1], q - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (extra_ch)
				buff[--index] = extra_ch;
			return (write(1, &buff[1], q - 1) + write(1, &buff[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_ch)
				buff[--padding_start] = extra_ch;
			return (write(1, &buff[padding_start], q - padding_start) +
					write(1, &buff[index], length - (1 - padding_start)));
		}
	}
	if (extra_ch)
		buff[--index] = extra_ch;
	return (write(1, &buff[index], length));
}

/**
 * write_the_unsignd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buff: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */

int write_the_unsignd(int is_negative, int index,
		char buff[],
		int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - index - 1, q = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buff[index] == '0')
		return (0); /* printf(".0d", 0) no char is printed */

	if (precision > 0 && precision < len)
		padding = ' ';

	while (precision > len)
	{
		buff[--index] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > len)
	{
		for (q = 0; q < width - len; q++)
			buff[q] = padding;

		buff[q] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buff[index], len) + write(1, &buff[0], q));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buff[0], q) + write(1, &buff[index], len));
		}
	}

	return (write(1, &buff[index], len));
}

/**
 * write_the_pointer - a function Writes the memory address
 * @buff: Represenys the arrays of character
 * @index: Index at which the number starts in the buffer
 * @len: Length of number
 * @width: It specifies the width specifier
 * @flags: Flags specification
 * @padding:  representing the padding of the printing
 * @extra_ch: representing an extra character
 * @padding_start: The Index at which the padding would begin
 * Return: Number of characters printed.
 */
int write_the_pointer(char buff[], int index, int len,
		int width, int flags, char padding, char extra_ch, int padding_start)
{
	int q;

	if (width > len)
	{
		for (q = 3; q < width - len + 3; q++)
			buff[q] = padding;
		buff[q] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			buff[--index] = 'x';
			buff[--index] = '0';
			if (extra_ch)
				buff[--index] = extra_ch;
			return (write(1, &buff[index], len) + write(1, &buff[3], q - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buff[--index] = 'x';
			buff[--index] = '0';
			if (extra_ch)
				buff[--index] = extra_ch;
			return (write(1, &buff[3], q - 3) + write(1,
						&buff[index], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_ch)
				buff[--padding_start] = extra_ch;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[padding_start], q - padding_start) +
					write(1, &buff[index], len - (1 - padding_start) - 2));
		}
	}
	buff[--index] = 'x';
	buff[--index] = '0';
	if (extra_ch)
		buff[--index] = extra_ch;
	return (write(1, &buff[index], BUFF_SIZE - index - 1));
}
