/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:19:32 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/23 19:16:12 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_new_squote(t_com *cmd, int nb)
{
	printf("called squote\n");
	cmd->s_quote = malloc(sizeof(t_squote));
	if (!cmd->s_quote)
		return (1);
	cmd->s_quote->pos = nb;
	cmd->s_quote->next = NULL;
	return (0);
}

int	add_to_squote(t_com *cmd, int pos)
{
	t_squote	*tmp;
	t_squote	*new;

	if (cmd->s_quote == NULL)
		return (1);
	new = malloc(sizeof(t_squote));
	if (!new)
		return (1);
	new->pos = pos;
	new->next = NULL;
	tmp = cmd->s_quote;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int	check_if_quotes(t_com *cmd, int nb)
{
	t_squote	*tmp;

	tmp = cmd->s_quote;
	while (tmp)
	{
		if (nb == tmp-> pos - 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_squotes(t_com *cmd, int pos)
{
	printf("in this case\n");
	if (cmd->s_quote == NULL)
		return (create_new_squote(cmd, pos));
	else
		return (add_to_squote(cmd, pos));
}
