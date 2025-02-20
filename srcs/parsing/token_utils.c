/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:46:41 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/20 14:01:31 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void handle_redirections_in(char *input, int *i, t_token **tokens)
{
    if (input[*i] == '<' && input[*i + 1] == '<')
    {
        add_token(tokens, "<<", TOKEN_HEREDOC, 0); 
        (*i) += 2;
    }
    else
    {
        add_token(tokens, "<", TOKEN_REDIRECT_IN, 0); 
        (*i)++;
    }
}
