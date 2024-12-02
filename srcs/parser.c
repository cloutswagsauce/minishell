/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/02 17:27:54 by lfaria-m         ###   ########.fr       */
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
	struct	stat *buff;
	char	*exec_path;

	buff = 0;

    path_split = ft_split(getenv("PATH"), ':');

	exec_path = *path_split;
	while (exec_path)
	{
		ft_strlcat(exec_path, "/", ft_strlen(exec_path) + 1);
		ft_strlcat(exec_path, command.argv[0], join_len(exec_path, command.argv[0]));
		if (!stat(exec_path, buff))
		{
			printf("found that shit");
		}
		exec_path++;
	}
	



}
t_com	parse_input(char *str)
{
	t_com	command;

	command.argv = ft_split(str, ' ');
	path_split_append(command);
	

	return (command);
	
}
