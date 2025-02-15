

#include "../../minishell.h"

int	set_variable(char **name_and_value, char *equals, t_data *data, t_com *cmd)
{
	char	*name;
	char	*value;
	t_list	*new;

	name = get_name((*(name_and_value + 1)), equals);
	value = get_value(equals);
	if (!value && cmd->d_quote)
	{
		value = (*(name_and_value + 2));
	}
	if (!value)
	{
		return (1);
	}
	if (update_var(name, value, &data->local_env))
		return (0);
	if (!name)
	{
		free(name);
		return (1);
	}
	new = ft_lstnew(name, value);
	ft_lstadd_back(&data->local_env, new);
	return (0);
}
