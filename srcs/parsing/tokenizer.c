/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:51:58 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/13 11:22:27 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;
	size_t	len;

	len = ft_strlen(value);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc(len + 1);
	ft_memcpy(token->value, value, ft_strlen(value));
	token->value[len] = '\0';
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, char *value, int type)
{
	t_token	*new;
	t_token	*temp;

	new = new_token(value, type);
	if (!new)
	{
		free(value);
		return ;
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
			printf("you forgot to close the damn quote!\n");
			return (0);
		}
		buf = ft_substr(input, start, (*i) - start);
		if (quote == '\'')
			add_token(tokens, buf, TOKEN_SQUOTES);
		else
			add_token(tokens, buf, TOKEN_WORD);
		if (input[*i])
			(*i)++;
	}
	return (1);
}

void	handle_redirections_in(char *input, int *i, t_token **tokens)
{
	if (input[(*i) + 1] && input[(*i) + 1] == '<')
	{
		add_token(tokens, "<<", TOKEN_HEREDOC);
		(*i) += 2;
	}
	else
	{
		add_token(tokens, "<", TOKEN_REDIRECT_IN);
		(*i)++;
	}
}

void	handle_operators(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		add_token(tokens, "|", TOKEN_PIPE);
		(*i)++;
	}
	else if (input[*i] == '<')
		handle_redirections_in(input, i, tokens);
	else if (input[*i] == '>')
	{
		if (input[(*i) + 1] == '>')
		{
			add_token(tokens, ">>", TOKEN_APPEND);
			(*i) += 2;
		}
		else
		{
			add_token(tokens, ">", TOKEN_REDIRECT_OUT);
			(*i)++;
		}
	}
}

void	handle_word(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*buf;

	start = *i;
	while (input[*i] && !isspace((char)input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '"'
		&& input[*i] != '\'')
		(*i)++;
	buf = ft_substr(input, start, (*i) - start);
	add_token(tokens, buf, TOKEN_WORD);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && isspace((char)input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			handle_operators(input, &i, &tokens);
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!handle_quotes(input, &i, &tokens))
				return (NULL);
			continue ;
		}
		while (input[i] && isspace((char)input[i]))
			i++;
		handle_word(input, &i, &tokens);
	}
	return (tokens);
}
