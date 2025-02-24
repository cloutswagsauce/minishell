#include "../../minishell.h"

char *handle_input(void)
{
    char *input;

    if (isatty(STDIN_FILENO))
        signal_handler_interactive();
    else
        signal_handler_non_interactive();
    rl_on_new_line();
    input = readline("mini$hell 🤖: ");
    return (input);
}

void execute_input(char *input, t_com **commands, t_data *data)
{
    if (*input)
    {
        *commands = parse_input(input);
        if (*commands && (*commands)->has_outpipe)
            execute_pipeline(*commands, data);
        else if (*commands)
            execute_process(*commands, data);
        wait(0);
        finish_execution(*commands, input, data);
    }
    else
        free(input);
}