/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:13 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/15 13:18:40 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void expand_variable(t_com *com, int i, t_list *vars)
{
    char    *new_value;

    if (getenv(com->argv[i] + 1))
    {
        new_value = ft_strdup(getenv(com->argv[i] + 1));
        if (!new_value)
            return ;
        free(com->argv[i]);
        com->argv[i] = new_value;
        return ;
    }
    while (vars)
    {
        if (!ft_memcmp(com->argv[i] + 1, vars->name, ft_strlen(com->argv[i])))
        {
            new_value = ft_strdup(vars->value);
            free(com->argv[i]);
            com->argv[i] = new_value;
            return ;
        }
        vars = vars->next;
    }
    free(com->argv[i]);
	com->argv[i] = ft_strdup("");
}


void	command_has_variable(t_com *com, t_list *local_env)
{
	int	i;

	i = 0;
	while (com->argv[i])
	{
		if (ft_strchr(com->argv[i], '$'))
			expand_variable(com, i, local_env);
		i++;
	}
	
}
