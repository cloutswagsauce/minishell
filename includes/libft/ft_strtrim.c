/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:33:51 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/08 09:34:21 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res_start;
	char	*res_end;
	char	*result;
	int		len;

	res_start = (char *)s1;
	while (*res_start && ft_strchr(set, *res_start))
		res_start ++;
	res_end = (char *)s1 + ft_strlen(s1) - 1;
	while (res_end > res_start && ft_strchr(set, *res_end))
		res_end --;
	len = res_end - res_start + 1;
	result = (char *) malloc((len + 1));
	if (!result)
		return (0);
	ft_memmove(result, res_start, len);
	result[len] = '\0';
	return (result);
}
