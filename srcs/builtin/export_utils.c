

#include "../../minishell.h"

int	set_variable(char **name_and_value, char *equals, t_data *data, t_com *cmd)
{
	char	*name;
	char	*value;
	t_list	*new;


	name = get_name((*(name_and_value + 1)), equals);
	value = get_value(equals);
	if (!value && (cmd->d_quote || cmd->s_quote))
		value = (*(name_and_value + 2));
	if (!value)
		return (1);
	if (update_var(name, value, &data->local_env))
	{
		free(name);
		free(value);
		return (0);
	}
		
	if (!name)
	{
		free(name);
		return (1);
	}
	new = ft_lstnew(name, value);
	free(name);
	if (!(cmd->d_quote) && !(cmd->s_quote))
		free(value);
	ft_lstadd_back(&data->local_env, new);
	return (0);
}

void	print_local(t_data *data)
{
	t_list	*temp;

	temp = data->local_env;
	while (temp)
	{
		ft_printf("declare -x %s", temp->name);
		if (temp->value)
			ft_printf("=\"%s\"\n", temp->value);
		ft_printf("\n");
		temp = temp->next;
	}
}

void	case_equals(char *equals, char **temp_env)
{
	char	*name;
	char	*value;

	name = get_name(*temp_env, equals);
	value = get_value(equals);
	ft_printf("declare -x %s", name);
	if (value)
	{
		ft_printf("=\"%s\"", value);
		free(value);
	}
	else
		ft_printf("=\"\"");
	ft_printf("\n");
	free(name);
}

void	handle_no_args(t_data *data)
{
	t_list	*temp_env;

	temp_env = data->envp;
	while (temp_env)
	{
		ft_printf("declare -x %s = %s\n", temp_env->name,temp_env->value);
		temp_env = temp_env->next;
	}
	print_local(data);
}

int	handle_both_cases(char *equals, char **name_and_value, t_com *cmd,
		t_data *data)
{
	char	*name;
	t_list	*new;


	if (equals)
	{
		if (!set_variable(name_and_value, equals, data, cmd))
			return (1);
	}
	else
	{
		name = ft_strdup(name_and_value[1]);
		if (!name)
			return (1);
		new = ft_lstnew(name, "");
		if (!new)
		{
			free(name);
			return (1);
		}
		ft_lstadd_back(&data->local_env, new);
		free(name);
	}
	return (0);
}
