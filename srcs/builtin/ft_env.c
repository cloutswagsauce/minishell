/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/15 13:15:05 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int	handle_PWD(t_data *data, int *i)
{
	if (!ft_strncmp(data->envp[*i], "PWD", ft_strlen("PWD")))
	{
		ft_printf("PWD=");
		ft_pwd();
		(*i)++;
	}
	if (!ft_strncmp(data->envp[*i], "OLDPWD", ft_strlen("OLDPWD")))
	{
		ft_printf("OLDPWD=%s", getenv("OLDPWD"));
		write(1, "\n", 1);
		(*i)++;
	}
	return (0);
}

void	ft_env(t_data *data)
{
	int		i;
	t_list	*temp;
	char	**envp_temp;
	printf("env was called");

	i = 0;
	envp_temp = data->envp;
	while (envp_temp[i])
	{
		handle_PWD(data, &i);
		ft_printf(envp_temp[i++]);
		write(1, "\n", 1);
	}
	i = 0;
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
}
