/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:49:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/21 17:42:24 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_commands(t_com *cmd)
{
	t_com	*temp;

	while (cmd)
	{
		temp = cmd->next;
		free_double(cmd->argv);
        if (cmd->delim)
            free(cmd->delim);
		free(cmd);
		cmd = temp;
	}
    cmd = NULL;
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;
    while (tokens)
    {
        tmp = tokens->next;
        if (tokens->value) 
            free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}
