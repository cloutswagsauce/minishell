/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:32:54 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/04 13:49:32 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	a;

	s1 = (unsigned char *)s;
	a = (unsigned char) c;
	while (n --)
	{
		if (*s1 == a)
			return ((void *)s1);
		s1 ++;
	}
	return (0);
}
