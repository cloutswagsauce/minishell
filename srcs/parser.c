/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/21 15:52:13 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_com	*parse_input(char *str)
{
	char	**temp;
	int		i;
	t_com	*command;
	int		num_of_commands;
	
	temp = ft_split(str, '|');
	
	command = malloc_commands(temp);
	num_of_commands = num_commands(temp);
	i = 0;
	while (i < num_of_commands)
	{
		command[i].argv = ft_split(temp[i], ' ');
		if (!command[i].argv)
			printf("split failed");
		command[i].total_commands = num_of_commands;
		command[i].total_pipes = 0;
		command[i].total_redirects = 0;
		i++;
	}
	i = 0;
	while (i < num_of_commands)
	{
		if (is_command_builtin(&command[i]))
			command[i].is_builtin = 1;
		else
			command[i].is_builtin = 0;
		check_if_pipe(str, &command[i]);
		i++;
	}
	if (i == 1)
		command[0].is_stand_alone = 1;
	else
		command[0].is_stand_alone = 0;
	
	return (command);
}



