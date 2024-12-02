/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:35:56 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/11 13:00:12 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (!result)
		return (0);
	ft_memmove(result, s1, s1_len);
	j = 0;
	while (j < s2_len)
	{
		result[s1_len + j] = s2[j];
		j++;
	}
	result[s1_len + j] = '\0';
	return (result);
}
