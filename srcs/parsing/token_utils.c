/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:46:41 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 14:15:41 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"


int process_quoted_string(char *input, int *i, t_token **tokens, char **buf)
{
    t_token *last;
    if (*buf) {
        add_token(tokens, *buf, TOKEN_WORD, 1);
        *buf = NULL;
    }
    if (!handle_quotes(input, i, tokens))
        return (0);
    while (input[*i] && !isspace((char)input[*i]) && 
           input[*i] != '|' && input[*i] != '<' && input[*i] != '>') {
        last = get_last_token(*tokens);
        if (input[*i] == '"' || input[*i] == '\'') {
            if (!join_quoted_token(input, i, tokens, last))
                return (0);
        } else {
            if (!join_word_token(input, i, tokens, last))
                return (0);
        }
    }
    return (1);
}

int process_operator(char *input, int *i, t_token **tokens, char **buf)
{
    printf("process operator was called\n");
    if (*buf) {
        add_token(tokens, *buf, TOKEN_WORD, 1);
        *buf = NULL;
    }
    handle_operators(input, i, tokens);
    return (1);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *result = ft_strjoin(s1, s2);
    free(s1);
    return (result);
}

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
