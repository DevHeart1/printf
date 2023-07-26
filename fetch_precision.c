#include "main.h"

/**
 * fetch_precision - calculates the precision to be printed to stdout stream
 * @format: foramtted string to fetch the precision
 * @q: list of the variadic arguments
 * @lists: this represents the arguments to be retrieved
 *
 * Return: precision
 */

int fetch_precision(const char *format, int *q, va_list lists)
{
	int active_q = *q + 1;
	int precision = -1;

	if (format[active_q] != '.')
		return (precision);

	precision = 0;

	while (format[active_q] != '\0')
	{
		active_q++;

		if (is_digit(format[active_q]))
		{
			precision *= 10;
			precision += format[active_q] - '0';
		}
		else if (format[active_q] == '*')
		{
			active_q++;
			precision = va_arg(lists, int);
			break;
		}
		else
			break;
	}

	*q = active_q - 1;

	return (precision);
}
