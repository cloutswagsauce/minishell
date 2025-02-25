/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:49:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 20:18:24 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_commands(t_com *cmd)
{
	t_com	*temp;
    t_squote *quotes;

	while (cmd)
	{
		temp = cmd->next;
		free_double(cmd->argv);
        if (cmd->delim)
            free(cmd->delim);
        if (cmd->output_file)
            free(cmd->output_file);
        if (cmd->s_quote)
        {
            quotes = cmd->s_quote;
            while(quotes)
            {
                quotes = cmd->s_quote->next;
                free(cmd->s_quote);
            }
        }
		free(cmd);
		cmd = temp;
	}
    cmd = NULL;
}

void free_lists(t_data *data)
{
    t_list *current;
    t_list *next;

  
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
        printf("freeing token: %s\n", tokens->value);
        tmp = tokens->next;
        if (tokens->value) 
            free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}
