/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:08:48 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/08 18:24:46 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(char *env_var)
{
    if (!getenv(env_var))
    {
        ft_printf("env: %s is not a env variable!\n", env_var);
        return ;
    }
   ft_putstr_fd(getenv(env_var), 1);
   write(1, "\n", 1);
}