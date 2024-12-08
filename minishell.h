/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:53:11 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/08 17:51:18 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <readline/readline.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/history.h>
#include <stdio.h>      // For printf
#include <stdlib.h>     // For malloc, free
#include <unistd.h>     // For write, access, read, close
#include <fcntl.h>      // For open
#include <string.h> 
#include <sys/types.h>  // For types like pid_t
#include <sys/ioctl.h>  // For ioctl
#include <termios.h>    // For tcsetattr, tcgetattr
#include <sys/wait.h>   // For wait, waitpid, wait3, wait4
#include <signal.h>     // For signal, sigaction, sigemptyset, sigaddset, kill
#include <unistd.h>     // For getcwd, chdir, unlink
#include <sys/stat.h>   // For stat, lstat, fstat
#include <fcntl.h>      // For open
#include <dirent.h>     // For opendir, readdir, closedir
#include <curses.h>     // Often provides termcap functionality
#include <termcap.h>    // Specific termcap header (may vary by system)

typedef struct	s_com
{
	int		argc;
	char	**argv;
	int		is_builtin;
}				t_com;

extern const char *g_builtin_list[];

void	parse_input(char *str, t_com *command);
int		join_len(char *s1, char*s2);
void    free_double(char **arr);
void	handle_command(char *str, t_com *command);
int		is_command_builtin(t_com *com);
void	execute_builtin_command(t_com *command);
void	path_split_append(t_com *command);
void	free_command(t_com *command);
void	ft_echo(t_com command);




#endif