

#include "../../minishell.h"

int is_operator_start(char *input, int *i)
{
    return (*i == 0 || isspace((char)input[*i - 1]));
}

void handle_pipe(char *input, int *i, t_token **tokens)
{
    t_token *pipe_token = new_token("|", TOKEN_PIPE, 0);
    (void)input;
    if (pipe_token) {
        // Add to list temporarily for dispatching
        if (!*tokens) *tokens = pipe_token;
        else {
            t_token *temp = *tokens;
            while (temp->next) temp = temp->next;
            temp->next = pipe_token;
        }
    }
    (*i)++;
}

void handle_redirect_it(char *input, int *i, t_token **tokens)
{
    t_token *token;
    if (input[*i + 1] == '<') {
        token = new_token("<<", TOKEN_HEREDOC, 0);
        (*i) += 2;
    } else {
        token = new_token("<", TOKEN_REDIRECT_IN, 0);
        (*i)++;
    }
    if (token) {
        if (!*tokens) *tokens = token;
        else {
            t_token *temp = *tokens;
            while (temp->next) temp = temp->next;
            temp->next = token;
        }
    }
}

void handle_redirect_ot(char *input, int *i, t_token **tokens)
{
    t_token *token;
    t_token *temp;

    if (input[*i + 1] == '>') {
        token = new_token(">>", TOKEN_APPEND, 0);
        (*i) += 2;
    } else {
        token = new_token(">", TOKEN_REDIRECT_OUT, 0);
        (*i)++;
    }
    if (token) {
        if (!*tokens) *tokens = token;
        else {
            temp = *tokens;
            while (temp->next)
                temp = temp->next;
            temp->next = token;
        }
    }
}

void handle_non_operator(char *input, int *i, t_token **tokens)
{
    char *word = handle_word(input, i);
    if (word)
        add_token(tokens, word, TOKEN_WORD, 1);
}