/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:40:16 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/19 16:49:26 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

char	*get_name(char *str, char *equal)
{
	int		i;
	char	*name;

	i = equal - str;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	ft_memmove(name, str, i);
	name[i] = '\0';
	return (name);
}

char	*get_value(char *equals)
{
	int		i;
	char	*value;

	if (!equals || !*(equals + 1))
		return (NULL);
	i = ft_strlen(equals + 1);
	value = malloc(i + 1);
	if (!value)
		return (NULL);
	ft_memmove(value, equals + 1, i);
	value[i] = '\0';
	return (value);
}
int update_var(char *name, char *value,  t_list **local_env)
{
	t_list **current;
	char *new_value;

	current = local_env;
	while (*current)
	{
		if (!ft_memcmp((*current)->name, name, ft_strlen(name)))
		{
			new_value = ft_strdup(value);
			free((*current)->value);
			(*current)->value = new_value;
			return (1);
		}
		(*current) = (*current) -> next;
	}
	return (0);
	
}

void	ft_export(char *name_and_value, t_list **local_env)
{
	char	*equals;
	char	*name;
	char	*value;
	t_list	*new;


	equals = ft_strchr(name_and_value, '=');
	
	if (!equals)
		return ;
	name = get_name(name_and_value, equals);
	value = get_value(equals);
	if (update_var(name, value, local_env))
		return ;
	if (!name || !value)
	{
		free(name);
		free(value);
		return ;
	}
	new = ft_lstnew(name, value);
	ft_lstadd_back(local_env, new);
}
