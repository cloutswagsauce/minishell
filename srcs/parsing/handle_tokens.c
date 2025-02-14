#include "../../minishell.h"

int	handle_quotes(char *input, int *i, t_token **tokens)
{
	int		start;
	char	quote;
	char	*buf;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[(*i)++];
		start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (!input[*i])
		{
			ft_printf("you forgot to close the damn quote!\n");
			return (0);
		}
		buf = ft_substr(input, start, (*i) - start);
		if (quote == '\'')
			add_token(tokens, buf, TOKEN_SQUOTES);
		else if (quote == '"')
			add_token(tokens, buf, TOKEN_DQUOTES);
		else
			add_token(tokens, buf, TOKEN_WORD);
		if (input[*i])
			(*i)++;
	}
	return (1);
}

int	token_dispatcher(t_com **commands, t_com **current_cmd, t_token *tokens,
		int *arg_count)
{
	if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_SQUOTES ||
		tokens->type == TOKEN_DQUOTES)
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
	else if (tokens->type == TOKEN_PIPE)
	{
		if (current_cmd)
			handle_pipe_token(current_cmd, arg_count);
	}
	else if (tokens->type == TOKEN_REDIRECT_OUT)
		handle_redirect_token(*current_cmd, tokens, 0);
	else if (tokens->type == TOKEN_APPEND)
		handle_redirect_token(*current_cmd, tokens, 1);
	else if (tokens->type == TOKEN_HEREDOC)
		handle_heredoc_token(*current_cmd, tokens);
	return (0);
}

int	handle_pipe_token(t_com **current_cmd, int *arg_count)
{
	t_com	*new_cmd;

	(*current_cmd)->has_outpipe = 1;
	new_cmd = malloc(sizeof(t_com));
	if (!new_cmd)
		return (1);
	ft_memset(new_cmd, 0, sizeof(t_com));
	new_cmd->argv = malloc(sizeof(char *) * 2);
	if (!new_cmd->argv)
	{
		free(new_cmd);
		return (1);
	}
	new_cmd->argv[0] = NULL;
	new_cmd->argv[1] = NULL;
	new_cmd->has_inpipe = 1;
	new_cmd->has_outpipe = 0;
	new_cmd->next = NULL;
	(*current_cmd)->next = new_cmd;
	(*current_cmd) = new_cmd;
	(*arg_count) = 0;
	return (0);
}

int	handle_redirect_token(t_com *current_cmd, t_token *cur_token, int append)
{
	if (cur_token->type == TOKEN_REDIRECT_OUT
		|| cur_token->type == TOKEN_APPEND)
	{
		if (!cur_token->next)
		{
			printf("file not provided");
			return (1);
		}
		current_cmd->output_file = ft_strdup(cur_token->next->value);
		if (append)
			current_cmd->append_output = 1;
	}
	else if (cur_token->type == TOKEN_HEREDOC)
		handle_heredoc_token(current_cmd, cur_token);
	*cur_token = *cur_token->next;
	return (0);
}

int	handle_heredoc_token(t_com *current_cmd, t_token *cur_token)
{
	if (cur_token->next->value)
		current_cmd->delim = ft_strdup(cur_token->next->value);
	*cur_token = *cur_token->next;
	return (0);
}
