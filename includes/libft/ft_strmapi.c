/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:43:09 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/08 14:43:14 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	result = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (0);
	i = 0;
	while (*s)
	{
		result[i] = f(i, *s);
		i ++;
		s ++;
	}
	result[i] = '\0';
	return (result);
}
