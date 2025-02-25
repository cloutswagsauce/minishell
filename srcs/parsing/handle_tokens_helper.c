#include "../../minishell.h"


int handle_quotes(char *input, int *i, t_token **tokens)
{
    int     start;
    char    quote;
    char    *buf;

    if (input[*i] != '"' && input[*i] != '\'')
        return (1);
    quote = input[(*i)++]; 
    start = *i;
    while (input[*i] && input[*i] != quote)
        (*i)++;
    if (!input[*i])
    {
        ft_printf("you forgot to close the damn quote!\n");
        return (0);
    }
    buf = ft_substr(input, start, *i - start);
    if (!buf)
        return (0);
    if (quote == '\'')
        add_token(tokens, buf, TOKEN_SQUOTES, 1);
    else
        add_token(tokens, buf, TOKEN_DQUOTES, 1);
    (*i)++;
    return (1);
}


void handle_word_tokens(t_com **commands, t_com **current_cmd, t_token *tokens, int *arg_count)
{
    if (!*current_cmd)
    {
        create_new_command(current_cmd, arg_count, tokens);
        if (!*commands)
            *commands = *current_cmd;
    }
    else
        create_new_arg(arg_count, *current_cmd, tokens);
}