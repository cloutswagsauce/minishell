/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:40:16 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/15 13:41:57 by lfaria-m         ###   ########.fr       */
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
		printf("in this case");
		name = malloc(ft_strlen(str) + 1);
		name[ft_strlen(str)] = '\0';
	}
	return (name);
}

char	*get_value(char *equals)
{
	//problem - export no args is 
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
	char	**temp_env;

	temp_env = data->envp;

	while (*temp_env)
	{
		equals = ft_strchr(*temp_env, '=');
		// problem  - equals exist in both cases for temp env lets find another way to differentiate
		if (equals)
		{
			ft_printf("declare -x %s=", get_name(*temp_env, equals));
			ft_printf("\"%s\"\n", get_value(equals));
		}
		else
		{
			printf("hereeeeee");
			ft_printf("declare -x %s", get_name(*temp_env, equals));
		}
			
		temp_env++;
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
	char	*equals;
	char	*name;
	//char	*value;
	t_list	*new;

	if (flag)
	{
		printf("we are in this case");
		handle_no_args(data);
		return ;
	}
	equals = ft_strchr((*(name_and_value + 1)), '=');
	if (equals)
		set_variable(name_and_value, equals, data, cmd);
	else
	{
		name = ft_strdup((*(name_and_value + 1)));
		printf("name is: %s", name);
		new = ft_lstnew(name, "");
		ft_printf("envp: %s", new->name);
		ft_lstadd_back(&data->local_env, new);
	}
}
