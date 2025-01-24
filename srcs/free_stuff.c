/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:49:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/21 15:35:24 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command(t_com *command)
{
	char	**temp;
	int i = 0;

	while (i < command[0].total_commands)
	{
		temp = command[i].argv;
		while (*temp)
			free(*temp++);
	free(command[i].argv);
	i++;
	}
	

	
	
	
}
