#include "main.h"

/**
 * fetch_flags - a function fetches the current flag
 * @format: the formatted string which is to print the argument
 * @q: it contains the arguments
 * Return: the flag integer value
 */
int fetch_flags(const char *format, int *q)
{
	int n, active_q;
	int flagg = 0;

	const char flag_character[] = {'-', '+', '0', '#', ' ', '\0'};
	const char flag_array[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	active_q = *q + 1;
	while (format[active_q] != '\0')
	{
		n = 0;
		while (flag_character[n] != '\0')
		{
			if (format[active_q] == flag_character[n])
			{
				flagg |= flag_array[n];
				break;
			}
			n++;
		}

		if (flag_character[n] == 0)
			break;

		active_q++;
	}

	*q = active_q - 1;

	return (flagg);
}
