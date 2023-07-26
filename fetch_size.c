#include "main.h"

/**
 * fetch_size - a function that calculates the size of the printing
 * @format: the formatted string to be iterated  through
 * @q: represents the list of arguments
 *Return: size_of
 */

int fetch_size(const char *format, int *q)
{
	int active_q = *q + 1;
	int size_of = 0;

	if (format[active_q] == 'l')
		size_of = S_LONG;
	else if (format[active_q] == 'h')
		size_of = S_SHORT;

	if (size_of == 0)
		*q = active_q - 1;
	else
		*q = current_q;

	return (size_of);
}
