/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/14 16:06:15 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"



void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD", ft_strlen("PWD")))
		{
			ft_printf("PWD=");
			ft_pwd();
			i++;
		}
		if (!ft_strncmp(data->envp[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			ft_printf("OLDPWD=%s", getenv("OLDPWD"));
			write(1, "\n", 1);
			i++;
		}
		ft_printf(data->envp[i++]);
		write(1, "\n", 1);
	}
	while (data->local_env)
	{
		if (data->local_env->name && *data->local_env->value)
		{
			ft_printf(data->local_env->name);
			write(1, "=", 1);
			ft_printf(data->local_env->value);
			write(1, "\n", 1);
		}
		data->local_env = data->local_env->next;
	}
}
