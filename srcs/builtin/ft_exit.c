/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:00:00 by assistant         #+#    #+#             */
/*   Updated: 2025/02/23 20:22:39 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_valid_number(const char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static long long get_exit_code(const char *str)
{
    long long num;
    int sign;
    int i;

    num = 0;
    sign = 1;
    i = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i])
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return (num * sign);
}

int ft_exit(t_com *cmd, t_data *data)
{
    long long exit_code;

    ft_putendl_fd("exit", STDERR_FILENO);
    if (!cmd->argv[1])
    {
        free_lists(data);
        free(data);
        rl_clear_history();
        exit(g_exit_status);
    }
    if (!is_valid_number(cmd->argv[1]))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        free_lists(data);
        free(data);
        rl_clear_history();
        exit(2);
    }
    if (cmd->argv[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        return (1);
    }
    exit_code = get_exit_code(cmd->argv[1]);
    free_lists(data);
    free(data);
    rl_clear_history();
    exit(exit_code % 256);
}