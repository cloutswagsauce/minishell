/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:40:16 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 16:58:12 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*get_name(char *str, char *equal)
{
	char	*name;
	int		i;

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
		if (!name)
			return (NULL);
		ft_memmove(name, str, ft_strlen(str));
		name[ft_strlen(str)] = '\0';
	}
	return (name);
}

int	is_valid_identifier(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (!*str)
		return (1);
	str++;
	if (!*str)
		return (1);
	if (*str == '<' || *str == '>' || *str == '|')
		return (0);
	return (1);
}

int	ft_export(char **name_and_value, t_com *cmd, t_data *data, int flag)
{
	char	*equals;

	if (flag)
	{
		handle_no_args(data);
		return (0);
	}
	if (!is_valid_identifier(name_and_value[1]))
	{
		ft_printf("export: `%s': not a valid identifier\n", name_and_value[1]);
		return (1);
	}
	equals = ft_strchr(name_and_value[1], '=');
	if (update_env_var(cmd, data))
		return (0);
	if (handle_both_cases(equals, name_and_value, cmd, data))
	{
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}
