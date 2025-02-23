/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:56:01 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/23 19:01:18 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	arg_helper(t_token *cur_token, t_com *current_cmd, int *arg_count)
{
	int	i;

	if (cur_token->type == TOKEN_SQUOTES)
	{
		printf("token thinks its squote\n");
		handle_squotes(current_cmd, *arg_count);
	}
		
	if (cur_token->type == TOKEN_DQUOTES)
		current_cmd->d_quote = 1;
	if (current_cmd->argv)
	{
		i = 0;
		while (current_cmd->argv[i])
		{
			free(current_cmd->argv[i]);
			current_cmd->argv[i] = NULL;
			i++;
		}
		free(current_cmd->argv);
		current_cmd->argv = NULL;
	}
	return (0);
}

int	temp_arg_creator(t_com *current_cmd, char **temp_argv, int *arg_count)
{
	int i;
	i = 0;
	while (i < (*arg_count) - 1)
	{
		if (current_cmd->argv && current_cmd->argv[0])
			temp_argv[i] = ft_strdup(current_cmd->argv[i]);
		else
			temp_argv[i] = NULL;
		i++;
	}
	return (0);
}