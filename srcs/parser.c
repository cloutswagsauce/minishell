/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/08 15:20:34 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_command_builtin(t_com *com)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(com->argv[0], g_builtin_list[i],
				ft_strlen(com->argv[0])))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_path(char *exec_path, t_com *command)
{
	if (!access(exec_path, F_OK))
	{
		handle_command(exec_path, command);
		free(exec_path);
		return (1);
	}
	else
	{
		return (0);
	}
}

void	path_split_append(t_com *command)
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
		if (is_valid_path(exec_path, command))
			break ;
		else
			free(exec_path);
		current_path_split++;
	}
	free_double(path_split);
}

void	parse_input(char *str, t_com *command)
{
	command->argv = ft_split(str, ' ');
	if (!command->argv)
	{
		printf("split failed");
	}
	if (is_command_builtin(command))
		command->is_builtin = 1;
	else
		command->is_builtin = 0;
	return ;
}
