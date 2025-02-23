#include "../../minishell.h"

char *handle_word(char *input, int *i)
{
    int start = *i;
    while (input[*i] && !isspace((char)input[*i]) && input[*i] != '|' 
           && input[*i] != '"' && input[*i] != '\'')
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
    t_token *new;
    t_token *temp;

    new = new_token(value, type, take_ownership);
    if (!new)
    {
        if (take_ownership)
            free(value);
        return;
    }
    if (!*tokens)
        *tokens = new;
    else
    {
        temp = *tokens;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}

void handle_operators(char *input, int *i, t_token **tokens)
{
    int is_operator = (*i == 0 || isspace((char)input[*i - 1]));
    
    if (is_operator && input[*i] == '|')
    {
        add_token(tokens, "|", TOKEN_PIPE, 0);
        (*i)++;
    }
    else if (is_operator && input[*i] == '<')
    {
        if (input[*i + 1] == '<')
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
    else if (is_operator && input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            add_token(tokens, ">>", TOKEN_APPEND, 0);
            (*i) += 2;
        }
        else
        {
            add_token(tokens, ">", TOKEN_REDIRECT_OUT, 0);
            (*i)++;
        }
    }
    else
    {
        char *word = handle_word(input, i);
        if (word)
            add_token(tokens, word, TOKEN_WORD, 1);
    }
}



t_token *tokenize_input(char *input)
{
    t_token *tokens = NULL;
    int i = 0;
    char *buf = NULL;
    char *temp;

    while (input[i])
    {
        while (input[i] && isspace((char)input[i]))
            i++;
        if (!input[i])
            break;

        buf = NULL;
        while (input[i] && !isspace((char)input[i]))
        {
            if (input[i] == '"' || input[i] == '\'')
            {
                if (!handle_quotes(input, &i, &tokens)) // Check int return
                    return (free_tokens(tokens), NULL);
                // No temp or merging—handle_quotes adds token
            }
            else if ((input[i] == '|' || input[i] == '<' || input[i] == '>') 
                     && (i == 0 || isspace((char)input[i - 1])))
            {
                if (buf)
                    add_token(&tokens, buf, TOKEN_WORD, 1);
                handle_operators(input, &i, &tokens);
                buf = NULL;
                break;
            }
            else
            {
                temp = handle_word(input, &i);
                if (!temp)
                    break;
                if (!buf)
                    buf = temp;
                else
                {
                    buf = ft_strjoin_free(buf, temp);
                    free(temp);
                }
            }
        }
        if (buf)
            add_token(&tokens, buf, TOKEN_WORD, 1);
    }
    return (tokens);
}
