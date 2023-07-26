#include "main.h"

void print_buffer(char buff[], int *index);

/**
 * _printf - a function that produces output according to a format.
 * @format: contain the format specifiers
 * Return: printed characters
 */

int _printf(const char *format, ...)
{
	int q, print = 0, char_printed = 0;
	int precision, width, size, flags, buffer_index = 0;
	va_list lists;

	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lists, format);

	for (q = 0; format[q] != '\0'; q++)
	{
		if (format[q] != '%')
		{
			buff[buffer_index++] = format[q];

			if (buffer_index == BUFF_SIZE)
				print_buffer(buff, &buffer_index);
			char_printed++;
		}
		else
		{
			print_buffer(buff, &buffer_index);
			flags = fetch_flags(format, &q);
			width = fetch_width(format, &q, args);
			precision = fetch_precision(format, &q, args);
			size = fetch_size(format, &q);
			++q;
			printed = handle_print(format, &q, args, buffer,
					flags, width, precision, size);
			if (print == -1)
				return (-1);
			char_printed += printed;
		}
	}

	print_buffer(buff, &buffer_index);

	va_end(lists);
	return (lists);
}

/**
 * print_buffer - print the characters in the array buffer
 * @buff: The array of characters
 * @index: The index of the char
 */

void print_buffer(char buff[], int *index)
{
	if (*index > 0)
		write(1, buff, *index);
	*index = 0;
}
