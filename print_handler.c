#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @index: index.
 * @lists: Contains the the list of arguments
 * @buff: the buff array to handle the printing
 * @flags: it calculate the current flags
 * @width: get width
 * @precision: Precision specification
 * @size: Specifies the size
 * Return: 1 or 2;
 */

int handle_print(const char *format, int *index, va_list lists, char buff[],
		int flags, int width, int precision, int size)
{
	int q, unknownlen = 0, chars_printed = -1;

	fmt_t format_types[] = {
		{'c', print_character}, {'s', print_string}, {'%', print_percentage},
		{'i', print_integer}, {'d', print_integer}, {'b', print_binaryNum},
		{'u', print_unsignedNum}, {'o', print_octalNum}, {'x', print_hexadecimal},
		{'X', print_hexaNum_upper}, {'p', prints_thepointer},
		{'S', print_the_unprintable}, {'r', print_reverse_str},
		{'R', print_the_rot13string}, {'\0', NULL}
	};

	for (q = 0; format_types[q].format != '\0'; q++)
		if (format[*index] == format_types[q].format)
			return (format_types[q].func(lists, buff, flags, width, precision, size));

	if (format_types[q].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknownlen += write(1, "%%", 1);

		if (format[*index] == ' ')
			unknownlen += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		else
		{
			unknownlen += write(1, &format[*index], 1);
			return (unknownlen);
		}
	}

	return (chars_printed);
}
