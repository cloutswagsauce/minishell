/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:57:09 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/22 12:15:56 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void del_node_contents(void *vars)
{
    t_list *node;

    node = (t_list *)vars;
    if (node->name)
        free(node->name);
    if (node->value)
        free(node->value);
}

void check_local(t_com *com, t_list **vars)
{
    t_list *temp;
    t_list *prev;

    temp = *vars;
    prev = NULL;

    printf("the arg is %s\n", com->argv[1]);
    
    while (temp)
    {
        if (!ft_strncmp(com->argv[1], temp->name, ft_strlen(com->argv[1])))
        {
            printf("we found variable name: %s\n", temp->name);
            if (prev) // If temp is not the head
                prev->next = temp->next;
            else // If temp is the head
                *vars = temp->next;
            ft_lstdelone(temp, del_node_contents);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
}

void	check_env(t_com *com, t_data *data)
{

	(void)com;
	(void)data;
}

int	ft_unset(t_com *com, t_data *data)
{
	if (!com->argv[1])
		return (0);
	check_local(com, &data->local_env);
	check_env(com, data);
	return (0);
}
