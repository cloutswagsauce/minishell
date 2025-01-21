/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:34:58 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/21 15:10:06 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_if_pipe(char *str, t_com *com)
{
	//int	i;
	//int	j;

	if (ft_strnstr(str, "|", ft_strlen(str)))
	{
		com->total_pipes++;
		printf("pipe found");
		return (1);
	}
	return (0);
		
}
void ft_pipex(t_com *commands)
{
	(void)commands;
	//pipe();
	//dup2(1, 3)
	
	
}