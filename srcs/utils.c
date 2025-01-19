/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:53 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/18 17:28:17 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int	join_len(char *s1, char *s2)
{
	return ((int)ft_strlen(s1) + ft_strlen(s2));
}
int num_commands(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
 t_com *malloc_commands(char **str)
{
	t_com *commands;
	int	i;

	i = 0;
	while(str[i])
		i++;
	
	
	commands = malloc(sizeof(t_com) * (i+1));
	
	return (commands);
	
}

void	free_double(char **arr)
{
	char	**temp;

	if (!arr)
		return ;
	temp = arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(arr);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
	{
		del(lst->name);
		del(lst->value);
	}
	else
	{
		free(lst->name);
		free(lst->value);
	}
	free(lst);
}
