/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:20:18 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/08 13:53:41 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	size_t			i;
	size_t			rem_len;

	if ((start >= ft_strlen(s)) || !*s)
	{
		result = (char *) malloc(sizeof(char) * (1));
		if (!result)
			return (0);
		result[0] = '\0';
		return (result);
	}
	rem_len = ft_strlen(s) - start;
	if (rem_len < len)
		len = rem_len;
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < len && s[start])
		result[i++] = s[start++];
	result[i] = '\0';
	return ((char *)result);
}
