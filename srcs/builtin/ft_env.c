/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/14 14:22:05 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

extern char	**environ;

void	ft_env(char **envp, t_list *local_env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD", ft_strlen("PWD")))
		{
			ft_printf("PWD=");
			ft_pwd();
			i++;
		}
		if (!ft_strncmp(envp[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			ft_printf("OLDPWD=%s", getenv("OLDPWD"));
			write(1, "\n", 1);
			i++;
		}
		ft_printf(envp[i++]);
		write(1, "\n", 1);
	}
	while (local_env)
	{
		if (local_env->name && *local_env->value)
		{
			ft_printf(local_env->name);
			write(1, "=", 1);
			ft_printf(local_env->value);
			write(1, "\n", 1);
		}
		local_env = local_env->next;
	}
}
