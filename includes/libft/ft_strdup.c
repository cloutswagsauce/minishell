/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:41:27 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/10/08 10:41:31 by lfaria-m         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	ft_memmove(result, s1, len + 1);
	return (result);
}
