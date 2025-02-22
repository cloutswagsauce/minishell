#include "../../minishell.h"


char **env_list_to_envp(t_list *env_list)
{
    int count = 0;
    t_list *tmp = env_list;
	char **envp;

    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    // Allocate memory for the char ** array (+1 for NULL terminator)
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL); // Handle allocation failure

    // Fill the array with "name=value" strings
    tmp = env_list;
    int i = 0;
    while (tmp)
    {
        // Calculate the length needed for "name=value"
        size_t len = ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2; // +1 for '=', +1 for '\0'
        envp[i] = malloc(len);
        if (!envp[i])
        {
            // Free previously allocated strings and the array if allocation fails
            while (i > 0)
                free(envp[--i]);
            free(envp);
            return (NULL);
        }
        // Manually construct "name=value" using ft_strlcpy and ft_strlcat
        ft_strlcpy(envp[i], tmp->name, len);          // Copy name
        ft_strlcat(envp[i], "=", len);               // Append '='
        ft_strlcat(envp[i], tmp->value, len);        // Append value
        tmp = tmp->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}
