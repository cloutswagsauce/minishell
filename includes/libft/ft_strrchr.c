/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:23:42 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/04 10:24:08 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = ft_strlen(str);
	if (ch == '\0' || ch == 0)
		return ((char *)str + i);
	i --;
	while (i >= 0)
	{
		if (str[i] == ch)
			return ((char *)str + i);
		i --;
	}
	return (0);
}
