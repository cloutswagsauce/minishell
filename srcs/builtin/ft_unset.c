/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:57:09 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/24 13:11:29 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void	del_node_contents(void *vars)
{
	t_list	*node;

	node = (t_list *)vars;
	free(node->name);
	free(node->value);
}

void	check_local(t_com *com, t_list **vars)
{
	while (*vars)
	{
		if (!ft_memcmp(com->argv[1] + 1, (*vars)->name, ft_strlen(com->argv[1]
					+ 1)))
		{
			ft_lstdelone(*vars, del_node_contents);
			break ;
		}
		(*vars) = (*vars)->next;
	}
}

void	ft_unset(t_com *com, t_list **lenv, char **envp)
{
	(void)envp;
	check_local(com, lenv);
}
