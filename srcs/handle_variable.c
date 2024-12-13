/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:13 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/13 11:42:09 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_variable(t_com *com, int i)
{
    char *new_value;

    
    if (getenv(com->argv[i]+1))
    {
        new_value = ft_strdup(getenv(com->argv[i]+1));
        if (!new_value)
            return ;
        free(com->argv[i]);
        com->argv[i] = new_value;
    }
    return ;
}

void command_has_variable(t_com *com, t_list *local_env)
{
    int i;

    i = 0;
    while (com->argv[i])
    {
        if (strchr(com->argv[i], '$'))
            expand_variable(com, i);
        i++;
    }
    
}