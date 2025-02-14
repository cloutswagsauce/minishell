

#include "../../minishell.h"

char	**get_builtin_list(void)
{
	static char	*builtin_list[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};

	return ((char **)builtin_list);
}

int	is_command_builtin(t_com *com)
{
	int		i;
	char	**builtin_list;

	i = 0;
	builtin_list = get_builtin_list();
	while (i < 7)
	{
		if (!ft_strncmp(com->argv[0], builtin_list[i], ft_strlen(com->argv[0])))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_path(char *exec_path, t_com *command, t_data *data)
{
	if (!access(exec_path, F_OK))
	{
		printf("the exec path is: %s\n", exec_path );
		handle_command(exec_path, command, data);
		free(exec_path);
		return (1);
	}
	else
	{
		printf("it didnt work\n");
		printf("the exec path is: %s\n", exec_path );
		return (0);
	}
		
}

