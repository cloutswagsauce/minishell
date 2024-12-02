/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:07:33 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/11 12:56:38 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(char a)
{
	if (a == '\t' || a == '\n' || a == '\v' || a == '\f' || a == '\r')
		return (1);
	else if (a == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && isspace(str[i]))
	{
		i ++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + str[i] - '0';
		i ++;
	}
	number *= sign;
	return (number);
}
