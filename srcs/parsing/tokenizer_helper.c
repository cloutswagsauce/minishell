#include "../../minishell.h"

void handle_operators(char *input, int *i, t_token **tokens)
{
    printf("handle opps\n");
    int is_op = is_operator_start(input, i);
    if (is_op && input[*i] == '|')
    {
        printf("1\n");
        handle_pipe(input, i, tokens);
    }
        
    else if (is_op && input[*i] == '<')
    {
        printf("2\n");
        handle_redirect_it(input, i, tokens);
    }
    else if (is_op && input[*i] == '>')
    {
        printf("3\n");
        handle_redirect_ot(input, i, tokens);
    }
        
    else
    {
        printf("4\n");
        handle_non_operator(input, i, tokens);
    }
        
}

void skip_spaces(char *input, int *i)
{
    while (input[*i] && isspace((char)input[*i]))
        (*i)++;
}

t_token *get_last_token(t_token *tokens)
{
    t_token *last = tokens;
    while (last && last->next)
        last = last->next;
    return (last);
}

int join_quoted_token(char *input, int *i, t_token **tokens, t_token *last)
{
    t_token *new_last;

    if (!handle_quotes(input, i, tokens))
        return (0);
    if (last)
    {
        new_last = get_last_token(*tokens);
        char *joined = ft_strjoin(last->value, new_last->value);
        free(last->value);
        free(new_last->value);
        last->value = joined;
        last->next = new_last->next;
        free(new_last);
    }
    return (1);
}

int join_word_token(char *input, int *i, t_token **tokens, t_token *last)
{
    char *temp = handle_word(input, i);
    if (!temp)
        return (0);
    if (last)
    {
        char *joined = ft_strjoin(last->value, temp);
        free(last->value);
        free(temp);
        last->value = joined;
    }
    else
    {
        add_token(tokens, temp, TOKEN_WORD, 1);
    }
    return (1);
}
