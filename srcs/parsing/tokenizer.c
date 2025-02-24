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

int is_operator_start(char *input, int *i)
{
    int is_op;

    is_op = 0;
    if (*i == 0 || isspace((char)input[*i - 1]))
        is_op = 1;
    return (is_op);
}

void handle_pipe(char *input, int *i, t_token **tokens)
{
	(void)input;
    add_token(tokens, "|", TOKEN_PIPE, 0);
    (*i)++;
}

void handle_redirect_it(char *input, int *i, t_token **tokens)
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

void handle_redirect_ot(char *input, int *i, t_token **tokens)
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

void handle_non_operator(char *input, int *i, t_token **tokens)
{
    char *word;

    word = handle_word(input, i);
    if (word)
        add_token(tokens, word, TOKEN_WORD, 1);
}

void handle_operators(char *input, int *i, t_token **tokens)
{
    int is_op;

    is_op = is_operator_start(input, i);
    if (is_op && input[*i] == '|')
        handle_pipe(input, i, tokens);
    else if (is_op && input[*i] == '<')
        handle_redirect_it(input, i, tokens);
    else if (is_op && input[*i] == '>')
        handle_redirect_ot(input, i, tokens);
    else
        handle_non_operator(input, i, tokens);
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

int process_quoted_string(char *input, int *i, t_token **tokens, char **buf)
{
    t_token *last;

    if (*buf)
    {
        add_token(tokens, *buf, TOKEN_WORD, 1);
        *buf = NULL;
    }
    if (!handle_quotes(input, i, tokens))
        return (0);
    while (input[*i] && !isspace((char)input[*i]) && 
           input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
    {
        last = get_last_token(*tokens);
        if (input[*i] == '"' || input[*i] == '\'')
        {
            if (!join_quoted_token(input, i, tokens, last))
                return (0);
        }
        else
        {
            if (!join_word_token(input, i, tokens, last))
                return (0);
        }
    }
    return (1);
}

int process_operator(char *input, int *i, t_token **tokens, char **buf)
{
    if (*buf)
    {
        add_token(tokens, *buf, TOKEN_WORD, 1);
        *buf = NULL;
    }
    handle_operators(input, i, tokens);
    return (1);
}

int process_word(char *input, int *i, t_token **tokens, char **buf)
{
    char *temp = handle_word(input, i);
    char *new_buf;

    if (!temp)
        return (1);
    if (!*buf)
        *buf = temp;
    else
    {
        new_buf = ft_strjoin(*buf, temp);
        free(*buf);
        free(temp);
        *buf = new_buf;
    }
    if (input[*i] && !isspace((char)input[*i]) && 
        (input[*i] == '"' || input[*i] == '\''))
        return (1);
    if (*buf)
    {
        add_token(tokens, *buf, TOKEN_WORD, 1);
        *buf = NULL;
    }
    return (1);
}


void init_tokenize_vars(t_token **tokens, char **buf, int *i)
{
    *tokens = NULL;
    *buf = NULL;
    *i = 0;
}

int process_next_char(char *input, int *i, t_token **tokens, char **buf)
{
    if (input[*i] == '"' || input[*i] == '\'')
    {
        if (!process_quoted_string(input, i, tokens, buf))
            return (0);
    }
    else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
    {
        if (!process_operator(input, i, tokens, buf))
            return (0);
    }
    else
    {
        if (!process_word(input, i, tokens, buf))
            return (0);
    }
    return (1);
}

void handle_remaining_buffer(t_token **tokens, char **buf)
{
    if (*buf)
        add_token(tokens, *buf, TOKEN_WORD, 1);
}

t_token *tokenize_input(char *input)
{
    t_token *tokens;
    int i;
    char *buf;

    init_tokenize_vars(&tokens, &buf, &i);
    while (input[i])
    {
        skip_spaces(input, &i);
        if (!input[i])
            break;
        if (!process_next_char(input, &i, &tokens, &buf))
        {
            free_tokens(tokens);
            return (NULL);
        }
    }
    handle_remaining_buffer(&tokens, &buf);
    return (tokens);
}
