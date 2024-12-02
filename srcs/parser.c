/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:34 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/02 14:00:57 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	free_command(t_com command)
{
	while (*command.argv)
		free(command.argv++);
	free(command.argv);
}

t_com	parse_input(char *str)
{
	t_com	command;

	command.argv = ft_split(str, ' ');
	return (command);
	//free_command(command);
}
