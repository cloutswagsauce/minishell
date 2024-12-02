/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:56:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/12 13:29:57 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*s3 != *s4)
			return ((unsigned char)*s3 - (unsigned char)*s4);
		s3 ++;
		s4 ++;
		n --;
	}
	return (0);
}
