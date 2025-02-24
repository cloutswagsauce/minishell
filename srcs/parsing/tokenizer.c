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
    char *new_buf;
    t_token *last;

    while (input[i])
    {
        while (input[i] && isspace((char)input[i]))
            i++;
        if (!input[i])
            break;
        
        if (input[i] == '"' || input[i] == '\'')
        {
            if (buf)  // If we have a buffer, add it as a token first
            {
                add_token(&tokens, buf, TOKEN_WORD, 1);
                buf = NULL;
            }
            
            // Handle the first quoted string
            if (!handle_quotes(input, &i, &tokens))
                return (free_tokens(tokens), NULL);
            
            // Process any adjacent text without spaces
            while (input[i] && !isspace((char)input[i]) && 
                   input[i] != '|' && input[i] != '<' && input[i] != '>')
            {
                if (input[i] == '"' || input[i] == '\'')
                {
                    // Save the current last token before adding a new one
                    last = tokens;
                    while (last && last->next)
                        last = last->next;
                    
                    // Handle the next quoted string
                    if (!handle_quotes(input, &i, &tokens))
                        return (free_tokens(tokens), NULL);
                    
                    // Join with the previous token if there was one
                    if (last)
                    {
                        t_token *new_last = tokens;
                        while (new_last && new_last->next)
                            new_last = new_last->next;
                        
                        // Combine the values without adding a space
                        char *joined = ft_strjoin(last->value, new_last->value);
                        free(last->value);
                        free(new_last->value);
                        
                        // Update the last token and remove the new one
                        last->value = joined;
                        last->next = new_last->next;
                        free(new_last);
                    }
                }
                else
                {
                    temp = handle_word(input, &i);
                    if (temp)
                    {
                        last = tokens;
                        while (last->next)
                            last = last->next;
                        char *joined = ft_strjoin(last->value, temp);
                        free(last->value);
                        free(temp);
                        last->value = joined;
                    }
                }
            }
            continue;
        }
        
        // Handle operators
        if (input[i] == '|' || input[i] == '<' || input[i] == '>')
        {
            if (buf)
            {
                add_token(&tokens, buf, TOKEN_WORD, 1);
                buf = NULL;
            }
            handle_operators(input, &i, &tokens);
            continue;
        }
        
        // Handle regular words
        temp = handle_word(input, &i);
        if (!temp)
            continue;
        
        if (!buf)
            buf = temp;
        else
        {
            new_buf = ft_strjoin(buf, temp);
            free(buf);
            free(temp);
            buf = new_buf;
        }

        // Check if next char continues the argument
        if (input[i] && !isspace((char)input[i]) && 
            (input[i] == '"' || input[i] == '\''))
            continue;
        
        if (buf)
        {
            add_token(&tokens, buf, TOKEN_WORD, 1);
            buf = NULL;
        }
    }
    if (buf)
        add_token(&tokens, buf, TOKEN_WORD, 1);

    return (tokens);
}
