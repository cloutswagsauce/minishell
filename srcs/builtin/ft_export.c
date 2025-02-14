/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:40:16 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/14 16:36:12 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

char	*get_name(char *str, char *equal)
{
	int		i;
	char	*name;

	if (equal)
	{
		i = equal - str;
		name = malloc(i + 1);
		if (!name)
			return (NULL);
		ft_memmove(name, str, i);
		name[i] = '\0';
	}
	else
	{
		name = malloc(ft_strlen(str) + 1);
		name[ft_strlen(str)] = '\0';
	}
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
int	update_var(char *name, char *value, t_list **local_env)
{
	t_list	**current;
	char	*new_value;

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
		(*current) = (*current)->next;
	}
	return (0);
}

void	handle_no_args(t_data *data)
{
	char	*equals;
	t_list	*temp;

	while (*data->envp)
	{
		equals = ft_strchr(*data->envp, '=');
		ft_printf("declare -x %s=\"%s\"\n", get_name(*data->envp, equals),
				get_value(equals));
		data->envp++;
	}
	temp = data->local_env;
	while (temp)
	{
		ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	ft_export(char **name_and_value, t_com *cmd, t_data *data,
		int flag)
{
	// local env is **
	char	*equals;
	char	*name;
	char	*value;
	t_list	*new;

	printf("is command in quotes: %d\n", cmd->d_quote);

	if (flag)
	{
		handle_no_args(data);
		return ;
	}
	equals = ft_strchr((*(name_and_value + 1)), '=');
	if (equals)
	{
		name = get_name((*(name_and_value + 1)), equals);
		value = get_value(equals);
		if (!value)
		{
			printf("in here");
			value = (*(name_and_value + 2));
		}
			
		if (update_var(name, value, &data->local_env))
			return ;
		if (!name)
		{
			free(name);
			return ;
		}
		new = ft_lstnew(name, value);
		ft_lstadd_back(&data->local_env, new);
	}
	else
	{
		name = ft_strdup((*(name_and_value + 1)));
		new = ft_lstnew(name, "");
		ft_printf("envp: %s", new->name);
		ft_lstadd_back(&data->local_env, new);
	}
}
