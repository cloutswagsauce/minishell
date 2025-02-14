/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/14 18:32:08 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int create_cmd_path(int *len, char **current_path_split, t_com *cmd, char **exec_path)
{
		*len = ft_strlen(*current_path_split) + ft_strlen(cmd->argv[0]) + 2;
		*exec_path = malloc(*len);
		ft_strlcpy(*exec_path, *current_path_split, *len);
		ft_strlcat(*exec_path, "/", *len);
		ft_strlcat(*exec_path, cmd->argv[0], *len);
		return (0);
}

void	path_split_append(t_com *command, t_data *data)
{
	char	**path_split;
	char	*exec_path;
	char	**current_path_split;
	int		len;
	
	if (!getenv("PATH"))
		return ;
	path_split = ft_split(getenv("PATH"), ':');
	current_path_split = path_split;
	while (*current_path_split)
	{
		create_cmd_path(&len, current_path_split, command, &exec_path);
		if (access(exec_path, X_OK) == 0)
		{
			handle_command(exec_path, command, data);
			free(exec_path);
			break ;
		}
		free(exec_path);
		current_path_split++;
	}
	free_double(path_split);
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(command->argv[0], 2);
	exit(127);
}

int	create_new_arg(int *arg_count, t_com *current_cmd, t_token *cur_token)
{
	char	**temp_argv;
	int		i;

	if (!current_cmd)
		return (1);
	i = 0;
	(*arg_count)++;
	temp_argv = malloc(sizeof(char *) * ((*arg_count) + 1));
	if (!temp_argv)
	{
		perror("temp argv failed:");
		return (1);
	}
	if (current_cmd->argv)
	{
		while (i < (*arg_count) - 1)
		{
			if (current_cmd->argv && current_cmd->argv[0])
				temp_argv[i] = ft_strdup(current_cmd->argv[i]);
			else
				temp_argv[i] = NULL;
			i++;
		}
	}
	temp_argv[(*arg_count) - 1] = ft_strdup(cur_token->value);
	temp_argv[(*arg_count)] = NULL;
	if (cur_token->type == TOKEN_SQUOTES)
		handle_squotes(current_cmd, *arg_count);
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
	current_cmd->argv = temp_argv;
	return (0);
}

int	create_new_command(t_com **current_cmd, int *arg_count, t_token *cur_token)
{
	// Create new command
	*current_cmd = malloc(sizeof(t_com));
	if (!*current_cmd)
		return (1);
	(*current_cmd)->argv = malloc(sizeof(char *) * 2);
	(*current_cmd)->argv[0] = ft_strdup(cur_token->value);
	(*current_cmd)->argv[1] = NULL;
	(*current_cmd)->has_inpipe = 0;
	(*current_cmd)->has_outpipe = 0;
	(*current_cmd)->d_quote = 0;
	(*current_cmd)->s_quote = NULL;
	(*current_cmd)->append_output = 0;
	(*current_cmd)->delim = 0;
	(*current_cmd)->output_file = 0;
	(*current_cmd)->is_builtin = 0;
	(*current_cmd)->next = NULL;
	*arg_count = 1;
	return (0);
}

t_com	*parse_input(char *str)
{
	t_token	*tokens;
	t_com	*commands;
	t_com	*current_cmd;
	int		arg_count;

	tokens = tokenize_input(str);
	commands = NULL;
	current_cmd = NULL;
	arg_count = 0;
	while (tokens)
	{
		token_dispatcher(&commands, &current_cmd, tokens, &arg_count);
		/*if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_SQUOTES ||
			tokens->type == TOKEN_DQUOTES)
		{
			if (!current_cmd)
			{
				create_new_command(&current_cmd, &arg_count, tokens);
				if (!commands)
					commands = current_cmd;
			}
			else
				create_new_arg(&arg_count, current_cmd, tokens);
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			if (current_cmd)
				handle_pipe_token(&current_cmd, &arg_count);
		}
		else if (tokens->type == TOKEN_REDIRECT_OUT)
			handle_redirect_token(current_cmd, tokens, 0);
		else if (tokens->type == TOKEN_APPEND)
			handle_redirect_token(current_cmd, tokens, 1);
		else if (tokens->type == TOKEN_HEREDOC)
			handle_heredoc_token(current_cmd, tokens);*/
		tokens = tokens->next;
	}
	if (current_cmd)
		current_cmd->is_builtin = is_command_builtin(current_cmd);
	free_tokens(tokens);
	return (commands);
}
