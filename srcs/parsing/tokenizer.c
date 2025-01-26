/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:51:58 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/26 21:43:41 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc(ft_strlen(value) + 1);
	ft_memcpy(token->value, value, ft_strlen(value));
	token->value[ft_strlen(value)] = '\0';
	//token->value = ft_strdup(value);
	 // Duplicate string value
	token->type = type;
	token->next = NULL;
	return (token);
}

// Add token to linked list
void	add_token(t_token **tokens, char *value, int type)
{
	t_token *new;
	t_token *temp;

	new = new_token(value, type);
	if (!new)
		return ;
	if (!*tokens) // If list is empty, set first token
		*tokens = new;
	else
	{
		temp = *tokens;
		while (temp->next) // Traverse to last token
			temp = temp->next;
		temp->next = new;
	}
}
int handle_quotes(char *input, int *i, t_token **tokens)
{
	int	start;
	char quote;
	char buf[256];

	if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[(*i)++];
			start = i;
			while (input[*i] && input[*i] != quote)
				i++;
			if (!input[*i])
			{
				printf("you forgot to close the damn quote!\n");
				return 0;
			}
			// use libft function
			strncpy(buf, &input[start], i - start);
			buf[*i - start] = '\0';
			add_token(&tokens, buf, TOKEN_WORD);
			if (input[*i])
				i++;
		}
	
	
}
void handle_operators(char a)
{
	
}
t_token *tokenize_input(char *input)
{
	t_token *tokens;
	int		i;
	int		start;
	char	buf[256];

	tokens = 0;
	i = 0;

	while (input[i])
	{
		// Skip whitespace
		while (input[i] && isspace((char)input[i]))
			i++;
		if (!input[i])
			break;
		// Handle quotes
		if (input[i] == '"' || input[i] == '\'')
		{
			char quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				printf("you forgot to close the damn quote!\n");
				return 0;
			}
			// use libft function
			strncpy(buf, &input[start], i - start);
			buf[i - start] = '\0';
			add_token(&tokens, buf, TOKEN_WORD);
			if (input[i])
				i++;
			continue;
		}

		// Handle pipes and redirections
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (input[i] == '|')
			{
				add_token(&tokens, "|", TOKEN_PIPE);
				i++;
			}
			else if (input[i] == '<')
			{
				if (input[i + 1] == '<')
				{
					add_token(&tokens, "<<", TOKEN_HEREDOC);
					i += 2;
				}
				else
				{
					add_token(&tokens, "<", TOKEN_REDIRECT_IN);
					i++;
				}
			}
			else if (input[i] == '>')
			{
				if (input[i + 1] == '>')
				{
					add_token(&tokens, ">>", TOKEN_APPEND);
					i += 2;
				}
				else
				{
					add_token(&tokens, ">", TOKEN_REDIRECT_OUT);
					i++;
				}
			}
			continue;
		}

		// Handle words (commands, arguments, etc)
		start = i;
		while (input[i] && !isspace((char)input[i]) && 
			   input[i] != '|' && input[i] != '<' && input[i] != '>' &&
			   input[i] != '"' && input[i] != '\'')
			i++;
		// use libft function
		strncpy(buf, &input[start], i - start);
		buf[i - start] = '\0';
		add_token(&tokens, buf, TOKEN_WORD);
	}

	return tokens;
}
