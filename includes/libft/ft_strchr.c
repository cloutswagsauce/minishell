/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:47:14 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/04 13:48:12 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	if (ch == '\0')
	{
		i = ft_strlen(str);
		return ((char *)str + i);
	}
	ch = (unsigned char) c;
	while (str[i])
	{
		if (str[i] == ch)
			return ((char *)str + i);
		i ++;
	}
	return (0);
}
