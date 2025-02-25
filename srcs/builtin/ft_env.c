/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 15:33:02 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int update_env_var(t_com *cmd, t_data *data)
{
	t_list *temp;
	char *name;
	char *value;
	
	name = get_name(cmd->argv[1], ft_strchr(cmd->argv[1], '='));
	if (cmd->d_quote || cmd->s_quote)
		value =cmd->argv[2];
	else
		value = ft_strchr(cmd->argv[1], '=') +  1;
	temp = data->envp;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
		{
			free(temp->value);
			free(name);
			temp->value = ft_strdup(value);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

int set_env_variable(char *name_and_value, char *equals, t_list **env_list)
{
    char *name;
    char *value;
    t_list *new;

    name = get_name(name_and_value, equals);
    if (!name)
        return (1);

    value = get_value(equals);
    if (!value)
    {
        free(name);  
        return (1);
    }
    new = ft_lstnew(name, value);
    if (!new) 
    {
        free(name);
        free(value);
        return (1);
    }
	free(name);
	free(value);
    ft_lstadd_back(env_list, new);
    return (0);
}
int set_env(t_list **env_list, char **envp)
{
    char *equals;
    
    while (*envp)
    {
        equals = ft_strchr(*envp, '=');
        if (set_env_variable(*envp, equals, env_list))
            return (1);
        envp++;
    }
    return (0);
}

int	ft_env(t_data *data)
{
	t_list	*temp;
	t_list	*envp_temp;

	
	envp_temp = data->envp;
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
