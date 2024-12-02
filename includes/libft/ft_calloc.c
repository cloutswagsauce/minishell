/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:29:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/08 09:31:58 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(count * size);
	if (!result)
		return (0);
	i = 0;
	while (i < size * count)
	{
		result[i] = 0;
		i ++;
	}
	return ((void *)result);
}
