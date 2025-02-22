#include "../../minishell.h"

char **env_list_to_envp(t_list *env_list)
{
    // Step 1: Count the number of environment variables
    int count = 0;
    t_list *tmp = env_list;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    // Step 2: Allocate memory for the char ** array (+1 for NULL terminator)
    char **envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL); // Handle allocation failure

    // Step 3: Fill the array with "name=value" strings
    tmp = env_list;
    int i = 0;
    while (tmp)
    {
        // Calculate the length needed for "name=value"
        size_t len = strlen(tmp->name) + strlen(tmp->value) + 2; // +1 for '=', +1 for '\0'
        envp[i] = malloc(len);
        if (!envp[i])
        {
            // Free previously allocated strings and the array if allocation fails
            while (i > 0)
                free(envp[--i]);
            free(envp);
            return (NULL);
        }
        // Combine name and value into "name=value"
        snprintf(envp[i], len, "%s=%s", tmp->name, tmp->value);
        tmp = tmp->next;
        i++;
    }

    // Step 4: Null-terminate the array
    envp[i] = NULL;

    return (envp);
}