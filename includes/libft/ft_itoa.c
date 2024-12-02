/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:07:43 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/11 12:57:37 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	digit_count;

	digit_count = 0;
	if (n < 0)
		digit_count ++;
	while (n != 0)
	{
		n /= 10;
		digit_count ++;
	}
	return (digit_count);
}

static char	*handle_zero(void)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * 2);
	if (!result)
		return (0);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

static char	*handle_min(int n)
{
	char	*min;
	int		i;

	min = (char *) malloc(sizeof(char) * 12);
	if (!min)
		return (0);
	i = 10;
	while (i >= 0 && n)
	{
		min[i--] = -(n % 10) + '0';
		n /= 10;
	}
	min[0] = '-';
	min[11] = '\0';
	return (min);
}

static char	*handle_fill(int digit_count, int n, char *result, int is_negative)
{
	while (digit_count >= 0 && n)
	{
		result[digit_count --] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		result[0] = '-';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digit_count;
	int		str_len;
	int		is_negative;

	if (n == 0)
		return (handle_zero());
	if (n == -2147483648)
		return (handle_min(n));
	is_negative = 0;
	digit_count = count_digit(n);
	if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}
	str_len = digit_count;
	result = (char *) malloc (sizeof(char) * (digit_count + 1));
	if (!result)
		return (0);
	digit_count --;
	handle_fill(digit_count, n, result, is_negative);
	result[str_len] = '\0';
	return (result);
}
