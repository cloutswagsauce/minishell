#include "../../minishell.h"

int	handle_pipe_token(t_com **current_cmd, int *arg_count)
{
	t_com	*new_cmd;

	(*current_cmd)->has_outpipe = 1;
	// Create new command for after pipe
	new_cmd = malloc(sizeof(t_com));
	if (!new_cmd)
		return (1);
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
	if (cur_token->type == TOKEN_REDIRECT_OUT || cur_token->type == TOKEN_APPEND)
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
	else if(cur_token->type == TOKEN_HEREDOC)
		handle_heredoc_token(current_cmd, cur_token);
		
	// we skip next token so we dont add it to command list
	*cur_token = *cur_token->next;
	return (0);
}

int handle_heredoc_token(t_com *current_cmd, t_token *cur_token)
{
	printf("handling heredoc");
	if (cur_token->next->value)
		current_cmd->delim = ft_strdup(cur_token->next->value);
	*cur_token = *cur_token->next;
	return (0);

}
