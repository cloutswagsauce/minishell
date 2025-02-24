#include "../../minishell.h"


int	create_cmd_path(int *len, char **current_path_split, t_com *cmd,
		char **exec_path)
{
	*len = ft_strlen(*current_path_split) + ft_strlen(cmd->argv[0]) + 2;
	*exec_path = malloc(*len);
	ft_strlcpy(*exec_path, *current_path_split, *len);
	ft_strlcat(*exec_path, "/", *len);
	ft_strlcat(*exec_path, cmd->argv[0], *len);
	return (0);
}

void execute_command_from_path(char *exec_path, char **path_split, t_com *command, t_data *data)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        free(exec_path);
        free_double(path_split);
        store_exit_status(1);
        return;
    }
    if (pid == 0)
    {
        handle_command(exec_path, command, data);
        exit(126);
    }
    waitpid(pid, &status, 0);
    free(exec_path);
    free_double(path_split);
    store_exit_status(status);
}