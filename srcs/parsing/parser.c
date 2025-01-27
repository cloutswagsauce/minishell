/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/27 18:29:50 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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

int create_new_arg(int *arg_count, t_com *current_cmd, t_token *cur_token)
{
	char **temp_argv;
	int	i;

	i = 0;
	(*arg_count)++;
				temp_argv = malloc(sizeof(char *) * ((*arg_count) + 1));
				if (!temp_argv)
				{
					perror("temp argv failed:");
					return (1);
				}
				while (i < (*arg_count) - 1)
				{
					//fix this - its no bueno
					temp_argv[i] = current_cmd->argv[i];
					i++;
				}
				//use a libft function instead of strdup
				temp_argv[(*arg_count) - 1] = strdup(cur_token->value);
				temp_argv[(*arg_count)] = NULL;
				free(current_cmd->argv);
				current_cmd->argv = temp_argv;
				return (0);
}

int create_new_command(t_com **current_cmd, int *arg_count, t_token *cur_token)
{
	// Create new command
	*current_cmd = malloc(sizeof(t_com));
	if (!*current_cmd)
		return 1;			
	(*current_cmd)->argv = malloc(sizeof(char *) * 2);	
	(*current_cmd)->argv[0] = ft_strdup(cur_token->value);					
	(*current_cmd)->argv[1] = NULL;			
	(*current_cmd)->has_inpipe = 0;			
	(*current_cmd)->has_outpipe = 0;			
	(*current_cmd)->is_builtin = 0;			
	(*current_cmd)->next = NULL;			
	*arg_count = 1;
	return (0);									
}
int handle_pipe_token(t_com **current_cmd, int *arg_count)
{
	t_com *new_cmd;
	(*current_cmd)->has_outpipe = 1;
				// Create new command for after pipe
				new_cmd = malloc(sizeof(t_com));
				if (!new_cmd)
					return (1);
				new_cmd->has_inpipe = 1;
				new_cmd->has_outpipe = 0;
				new_cmd->next = NULL;
				(*current_cmd)->next = new_cmd;
				(*current_cmd) = new_cmd;
				(*arg_count) = 0;
				return (0);
}
int handle_redirect_token(t_com *current_cmd, t_token *cur_token)
{
	int fd;

	
	if (cur_token->type == TOKEN_REDIRECT_OUT)
	{
		current_cmd->output_file = ft_strdup(cur_token->value);
		current_cmd->append_output = 0;
		fd =  open(cur_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd <1)
		{
			perror("faild to read file");
			return -1 ;
		}
	
	}
	return (0);
	
	
}
t_com *parse_input(char *str)
{
	t_token *tokens = tokenize_input(str);
	t_token *cur_token = tokens;
	t_com   *commands = NULL;
	t_com   *current_cmd = NULL;
	int     arg_count;

	arg_count = 0;
	while (tokens)
	{
		printf("token value: %s\n", tokens->value);
		printf("token type: %d\n", tokens->type);
		tokens = tokens->next;
	}
	
	while (cur_token)
	{
		if (cur_token->type == TOKEN_WORD)
		{
			if (!current_cmd)
			{
				create_new_command(&current_cmd, &arg_count, cur_token);
				if (!commands)
					commands = current_cmd;
			}
			else
				create_new_arg(&arg_count, current_cmd, cur_token);
		}
		else if (cur_token->type == TOKEN_PIPE)
		{
			if (current_cmd)
				handle_pipe_token(&current_cmd, &arg_count);
		}
		/*else if (cur_token->type == TOKEN_REDIRECT_OUT || cur_token->type == TOKEN_REDIRECT_IN 
				|| cur_token->type == TOKEN_APPEND || cur_token->type == TOKEN_HEREDOC 
				)
			
			{
				printf("token redirect");
				//handle_redirect_token(current_cmd, cur_token);
		}*/
			
		cur_token = cur_token->next;
	}
	if (current_cmd)
		current_cmd->is_builtin = is_command_builtin(current_cmd);
	free_tokens(tokens);
	return commands;
}





