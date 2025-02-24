/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/24 22:48:06 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_exit_status = 0;


void	call_child_action(t_com command, t_data *data)
{
	if (!ft_strncmp(command.argv[0], "<<", ft_strlen(command.argv[0])))
		exit(0);
	path_split_append(&command, data);
	perror("execve failed");  // Only reached if path_split_append fails
	exit(1);  // Exit with error if we get here
}



void finish_execution(t_com *command, char *input, t_data *data)
{
    add_history(input);
    free(input);
	(void)(data);
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


int setup_main(t_data **data, char **envp, t_list **local_env)
{
    int ret;

    ret = 0;
    *local_env = NULL;
    *data = NULL;
    ret = init_data(data, envp, *local_env);
    if (ret)
        return (1);
    if (isatty(STDIN_FILENO))
        signal_handler_interactive();
    else
        signal_handler_non_interactive();
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
    if (setup_main(&data, envp, &local_env))
        return (1);
    while (1)
    {
        input = handle_input();
        if (input == NULL)
        {
            free_lists(data);
            free(data);
            rl_clear_history();
            exit(0);
        }
        execute_input(input, &commands, data);
    }
    return (0);
}

