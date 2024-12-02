/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:26:41 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/11/13 12:43:05 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// use write to count the number of bytes written.

static int	handle_printing(const char c, va_list args)
{
	if (c == 'c')
		return (write(1, &(char){(char)va_arg(args, int)}, 1));
	else if (c == 's')
		return (print_s(va_arg(args, char *)));
	else if (c == 'u')
		return (print_u(va_arg(args, unsigned int)));
	else if (c == 'd' || c == 'i')
		return (print_di(va_arg(args, int)));
	else if (c == 'x')
		return (print_hex(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (print_hex(va_arg(args, unsigned int), 1));
	else if (c == 'p')
		return (print_p(va_arg(args, void *)));
	else
		return (write(1, &c, 1));
}

int	ft_printf(const char *format, ...)
{
	va_list	args_p;
	int		count;

	va_start(args_p, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				count++;
				ft_putchar_fd(*format, 1);
			}
			else
				count += handle_printing(*format, args_p);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args_p);
	return (count);
}
