/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/22 13:21:52 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int	handle_PWD(t_list *envp)
{
	t_list *temp;

	temp = envp;
	if (!ft_strncmp(temp->name, "PWD", ft_strlen(temp->name)))
	{
		ft_printf("PWD=");
		ft_pwd();
		return (1);
	}
	if (!ft_strncmp(temp->name, "OLDPWD", ft_strlen(temp->name)))
	{
		ft_printf("OLDPWD=%s", getenv("OLDPWD"));
		return (1);
	}
	return (0);
}
int	update_env_var(char *name, char *value, t_list **envp)
{
	t_list	**current;
	char	*new_value;

	current = envp;
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
int	set_env_variable(char *name_and_value, char *equals, t_list **env_list)
{
	char	*name;
	char	*value;
	t_list	*new;

	name = get_name(name_and_value, equals);
	value = get_value(equals);
	if (!value)
		return (1);
	if (!name)
	{
		free(name);
		return (1);
	}
	new = ft_lstnew(name, value);
	ft_lstadd_back(env_list, new);
	return (0);
}
int set_env(t_list **env_list, char **envp)
{
	char *equals;
	
	while (*envp)
	{
		equals = ft_strchr(*envp, '=');
		set_env_variable(*envp, equals, env_list);
		envp++;
	}
	return (0);
}

int	ft_env(t_data *data)
{
	t_list	*temp;
	t_list	*envp_temp;

	
	envp_temp = data->envp;

	printf("callend env\n");
	
	while (envp_temp)
	{
		if (handle_PWD(envp_temp))
			envp_temp = envp_temp->next;
		printf("%s=%s\n", envp_temp->name, envp_temp->value);
		envp_temp = envp_temp->next;
	}
	temp = data->local_env;
	while (temp)
	{
		if (temp->name && *temp->value)
		{
			ft_printf(temp->name);
			write(1, "=", 1);
			ft_printf(temp->value);
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}
