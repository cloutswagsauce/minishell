/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/15 14:46:52 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

extern char	**environ;

void	ft_env(char **envp, t_list *local_env)
{
	int	i;

	i = 0;
	(void)local_env;
	while (envp[i])
	{
		ft_printf(envp[i++]);
		write(1, "\n", 1);
	}
	while (local_env)
	{
		ft_printf(local_env->name);
		write(1, "=", 1);
		ft_printf(local_env->value);
		write(1, "\n", 1);
		local_env = local_env->next;
	}
}
