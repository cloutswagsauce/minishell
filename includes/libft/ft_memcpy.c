/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:14:49 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/05 13:14:08 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char	*dest;
	char	*source;

	if (!dst && !src && n)
		return (0);
	source = (char *) src;
	dest = (char *) dst;
	while (n > 0)
	{
		*dest = *source;
		dest ++;
		source ++;
		n --;
	}
	return (dst);
}
