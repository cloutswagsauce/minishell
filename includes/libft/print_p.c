/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:54:00 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/11/13 12:39:43 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_ptr_digits(unsigned long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static void	ft_putptr(unsigned long long n)
{
	if (n >= 16)
		ft_putptr(n / 16);
	write(1, &HEX_LOWER[n % 16], 1);
}

int	print_p(void *p)
{
	if (!p)
		return (write(1, "0x0", 3));
	write(1, "0x", 2);
	ft_putptr((unsigned long long)p);
	return (count_ptr_digits((unsigned long long)p) + 2);
}
