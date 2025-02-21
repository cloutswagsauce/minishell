
#include "../../minishell.h"

int heredoc_no_cmd(t_token *cur_token)
{
        char *line;
		char *delimiter;

		delimiter = ft_strdup(cur_token->next->value);
		if (!delimiter)
			return (1);
        while (1)
        {
            line = readline("heredoc> ");  // Prompt for input
            if (!line)  // EOF (Ctrl+D)
                break;
            if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
                && ft_strlen(line) == ft_strlen(delimiter))
            {
                free(line);
                break;  //
            }
            free(line);
        }
		return (0);
    }
