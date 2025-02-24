/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:49:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/24 16:33:16 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

void free_lists(t_data *data)
{
    t_list *current;
    t_list *next;

    if (!data)
        return;

	printf("free lists was called");
    // Free envp list
    current = data->envp;
    while (current)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
    data->envp = NULL;

    // Free local_env list
    current = data->local_env;
    while (current)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
    data->local_env = NULL;
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
