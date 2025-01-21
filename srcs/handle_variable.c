/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:13 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/21 14:57:07 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable(t_com *com, int j, t_list *vars)
{
	char	*new_value;

	printf("expand variable called");
	if (getenv(com->argv[j] + 1))
	{
		new_value = ft_strdup(getenv(com->argv[j] + 1));
		if (!new_value)
			return ;
		free(com->argv[j]);
		com->argv[j] = new_value;
		return ;
	}
	while (vars)
	{
		if (!ft_memcmp(com->argv[1] + 1, vars->name, ft_strlen(com->argv[j])))
		{
			new_value = ft_strdup(vars->value);
			free(com->argv[j]);
			com->argv[j] = new_value;
			return ;
		}
		vars = vars->next;
	}
	free(com->argv[j]);
	com->argv[j] = ft_strdup("");
}

void	command_has_variable(t_com *com, t_list *local_env)
{
	int	j;

	j = 0;
	while (com->argv[j])
	{
		if (com->argv[j] && ft_strchr(com->argv[j], '$'))
			expand_variable(com, j, local_env);
	j++;
	}
	
}
