/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/02 19:22:45 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command(t_com command)
{
	while (*command.argv)
		free(command.argv++);
	free(command.argv);
}
void path_split_append(t_com command)
{
    char	**path_split;
	char	*exec_path;
	int		len;


    path_split = ft_split(getenv("PATH"), ':');

	while (*path_split)
	{
		len = join_len(*path_split, command.argv[0]) + 2;
		exec_path = malloc(len); // 1  for null and 1 for /;
		ft_memcpy(exec_path, *path_split, ft_strlen(*path_split));
		ft_strlcat(exec_path, "/", len);
		ft_strlcat(exec_path, command.argv[0], len);
		exec_path[len-1] = '\0';
		if (!access(exec_path, F_OK))
		{
			printf("found it: %s\n", exec_path);
			execv(exec_path, command.argv);
			free(exec_path);
			break;
		}
			
		else
		{
			path_split++;
		}
			
	}
}
t_com	parse_input(char *str)
{
	t_com	command;

	command.argv = ft_split(str, ' ');
	path_split_append(command);
	

	return (command);
	
}
