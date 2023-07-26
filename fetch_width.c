#include "main.h"

/**
 * fetch_width - a function that calculate width for printing
 * @format: represents formatted string
 * @q: represents variadic list of arguments to print
 * @lists: list of argument
 * Return: width
 */
int fetch_width(const char *format, int *q, va_list lists)
{
	int active_q = *q + 1;
	int width = 0;

	for (; format[active_q] != '\0'; active_q++)
	{
		if (is_digit(format[active_q]))
		{
			width *= 10;
			width += format[active_q] - '0';
		}
		else if (format[active_q] == '*')
		{
			active_q++;
			width = va_arg(lists, int);
			break;
		}
		else
		{
			break;
		}
	}

	*q = active_q - 1;

	return (width);
}
