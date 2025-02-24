#include "../../minishell.h"

char *handle_word(char *input, int *i)
{
    int start = *i;
    while (input[*i] && !isspace((char)input[*i]) && 
           input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && 
           input[*i] != '"' && input[*i] != '\'')
        (*i)++;
    return (ft_substr(input, start, *i - start));
}

t_token *new_token(char *value, int type, int take_ownership)
{
    t_token *token;
    size_t len;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    if (take_ownership)
        token->value = value;
    else
    {
        len = ft_strlen(value);
        token->value = malloc(len + 1);
        if (!token->value)
        {
            free(token);
            return (NULL);
        }
        ft_memcpy(token->value, value, len);
        token->value[len] = '\0';
    }
    token->type = type;
    token->next = NULL;
    return (token);
}

void add_token(t_token **tokens, char *value, int type, int take_ownership)
{
    t_token *new = new_token(value, type, take_ownership);
    if (!new) {
        if (take_ownership) free(value);
        return;
    }
    if (!*tokens)
        *tokens = new;
    else {
        t_token *temp = *tokens;
        while (temp->next) temp = temp->next;
        temp->next = new;
    }
}

// Free a single token (helper)
void free_single_token(t_token *token)
{
    if (token) {
        free(token->value); // Safe if NULL
        free(token);
    }
}