/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/23 20:37:42 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_exit_status = 0;
// now: make envp into a t_list


// crtl D on heredoc caused leak
// crtl c on heredoc causes leak

void	call_child_action(t_com command, t_data *data)
{
	if (!ft_strncmp(command.argv[0], "<<", ft_strlen(command.argv[0])))
		exit(0);
	path_split_append(&command, data);
	exit(0);
}



void finish_execution(t_com *command, char *input, t_data *data)
{
    add_history(input);
    free(input);
	//free_lists(data);
	(void)data;
    free_commands(command);
}

int init_data(t_data **data, char **envp, t_list *local_env)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->envp = NULL;
	set_env(&(*data)->envp, envp);


	
	(*data)->local_env = local_env;
	return (0);
	
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_list  *local_env;
    t_com   *commands;
    t_data  *data;

    (void)argc;
    (void)argv;
    local_env = 0;
    data = 0;
    if (init_data(&data, envp, local_env))
        return (1);

    if (isatty(STDIN_FILENO))
        signal_handler_interactive();
    else
        signal_handler_non_interactive();

    while (1)
    {
        if (isatty(STDIN_FILENO))
            signal_handler_interactive();
        else
            signal_handler_non_interactive();
        rl_on_new_line();
        input = readline("mini$hell 🤖: ");
        if (input == NULL)
        {
            free_lists(data);
            free(data);
            rl_clear_history();
            exit(0);
        }
        if (*input)
        {
            commands = parse_input(input);
            if (commands && commands->has_outpipe)
                execute_pipeline(commands, data);
            else if (commands)
                execute_process(commands, data);
            wait(0);
            finish_execution(commands, input, data);
			
        }
        else
            free(input);
    }
    return (0);
}
