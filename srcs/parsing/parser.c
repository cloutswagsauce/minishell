/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/24 18:41:28 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

char	**get_builtin_list(void)
{
	static char	*builtin_list[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};

	return ((char **)builtin_list);
}

int	is_command_builtin(t_com *com)
{
	int		i;
	char	**builtin_list;

	i = 0;
	builtin_list = get_builtin_list();
	while (i < 7)
	{
		if (!ft_strncmp(com->argv[0], builtin_list[i], ft_strlen(com->argv[0])))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_path(char *exec_path, t_com *command, t_list *local_env)
{
	if (!access(exec_path, F_OK))
	{
		handle_command(exec_path, command, local_env);
		free(exec_path);
		return (1);
	}
	else
		return (0);
}

void	path_split_append(t_com *command, t_list *local_env)
{
	char	**path_split;
	char	*exec_path;
	char	**current_path_split;
	int		len;

	path_split = ft_split(getenv("PATH"), ':');
	current_path_split = path_split;
	while (*current_path_split)
	{
		len = join_len(*current_path_split, command->argv[0]) + 2;
		exec_path = malloc(len);
		ft_memcpy(exec_path, *current_path_split, ft_strlen(*path_split));
		ft_strlcat(exec_path, "/", len);
		ft_strlcat(exec_path, command->argv[0], len);
		exec_path[len - 1] = '\0';
		if (is_valid_path(exec_path, command, local_env))
			break ;
		else
			free(exec_path);
		current_path_split++;
	}
	free_double(path_split);
}
void	print_commands(t_com *cmd)
{
	while (cmd)
	{
		printf("Command: ");
		for (int i = 0; cmd->argv[i]; i++)
			printf("%s ", cmd->argv[i]);
		printf("\nPiped: in=%d, out=%d\n", cmd->has_inpipe, cmd->has_outpipe);
		
		cmd = cmd->next;  // Move to the next command
	}
}

t_com *parse_input(char *str)
{
	t_token *tokens = tokenize_input(str);
	t_token *cur_token = tokens;
	t_com   *commands = NULL;
	t_com   *current_cmd = NULL;
	int     arg_count = 0;
	char    **temp_argv = NULL;

	while (tokens)
	{
		printf("Token: %s, Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}

	while (cur_token)
	{
		if (cur_token->type == TOKEN_WORD)
		{
			if (!current_cmd)
			{
				// Create new command
				current_cmd = malloc(sizeof(t_com));
				if (!current_cmd)
					return NULL;
				current_cmd->argv = malloc(sizeof(char *) * 2);
				current_cmd->argv[0] = strdup(cur_token->value);
				current_cmd->argv[1] = NULL;
				current_cmd->has_inpipe = 0;
				current_cmd->has_outpipe = 0;
				current_cmd->is_builtin = 0;
				current_cmd->next = NULL;
				arg_count = 1;

				// Add to command list
				if (!commands)
					commands = current_cmd;
			}
			else
			{
				// Add argument to current command
				arg_count++;
				temp_argv = malloc(sizeof(char *) * (arg_count + 1));
				for (int i = 0; i < arg_count - 1; i++)
					temp_argv[i] = current_cmd->argv[i];
				temp_argv[arg_count - 1] = strdup(cur_token->value);
				temp_argv[arg_count] = NULL;
				free(current_cmd->argv);
				current_cmd->argv = temp_argv;
			}
		}
		else if (cur_token->type == TOKEN_PIPE)
		{
			if (current_cmd)
			{
				current_cmd->has_outpipe = 1;
				// Create new command for after pipe
				t_com *new_cmd = malloc(sizeof(t_com));
				if (!new_cmd)
					return NULL;
				new_cmd->has_inpipe = 1;
				new_cmd->has_outpipe = 0;
				new_cmd->next = NULL;
				current_cmd->next = new_cmd;
				current_cmd = new_cmd;
				arg_count = 0;
			}
		}
		// Handle redirections here...
		
		cur_token = cur_token->next;
	}

	if (current_cmd)
		current_cmd->is_builtin = is_command_builtin(current_cmd);

	free_tokens(tokens);
	return commands;
}





