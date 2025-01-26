/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:49:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/24 18:19:22 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void	free_commands(t_com *cmd)
{
	t_com *temp;

	while (cmd)
	{
		temp = cmd->next;
		free_double(cmd->argv);
		free(cmd);
		cmd = temp;
	}
}

void free_tokens(t_token *tokens)
{
	t_token *temp;
	
	while (tokens)
	{
		temp = tokens->next;
		free(tokens);
		tokens = temp;
	}
}
