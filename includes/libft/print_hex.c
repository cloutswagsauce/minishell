/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:27:07 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/14 16:37:57 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits_hex(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count = 1;
		return (count);
	}
	while (n > 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static void	ft_puthex(unsigned int n, int uppercase)
{
	char	*hex_digits;

	if (uppercase)
		hex_digits = HEX_UPPER;
	else
		hex_digits = HEX_LOWER;
	if (n >= 16)
		ft_puthex(n / 16, uppercase);
	write(1, &hex_digits[n % 16], 1);
}

int	print_hex(unsigned int n, int uppercase)
{
	ft_puthex(n, uppercase);
	return (count_digits_hex(n));
}
