/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:53:11 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/15 14:55:58 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <curses.h> // Often provides termcap functionality
# include <dirent.h> // For opendir, readdir, closedir
# include <fcntl.h>  // For open
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // For signal, sigaction, sigemptyset, sigaddset, kill
# include <stdio.h>
# include <stdio.h>  // For printf
# include <stdlib.h> // For malloc, free
# include <string.h>
# include <sys/ioctl.h> // For ioctl
# include <sys/stat.h>  // For stat, lstat, fstat
# include <sys/types.h> // For types like pid_t
# include <sys/wait.h>  // For wait, waitpid, wait3, wait4
# include <termcap.h>   // Specific termcap header (may vary by system)
# include <termios.h>   // For tcsetattr, tcgetattr
# include <unistd.h>    // For write, access, read, close
# include <unistd.h>    // For getcwd, chdir, unlink

typedef struct s_com
{
	int				argc;
	char			**argv;
	int				is_builtin;
}					t_com;

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}					t_list;

void				parse_input(char *str, t_com *command);
int					join_len(char *s1, char *s2);
void				free_double(char **arr);
void				handle_command(char *str, t_com *command,
						t_list *local_env);
int					is_command_builtin(t_com *com);
void				execute_builtin_command(t_com *command, t_list **local_env,
						char **envp);
void				path_split_append(t_com *command, t_list *local_env);
void				free_command(t_com *command);
void				ft_echo(t_com command);
void				ft_env(char **envp, t_list *local_env);
void				ft_pwd(void);
void				ft_export(char *name_and_value, t_list **local_env);
void				ft_cd(t_com command);
void				ft_exit(void);
t_list				*ft_lstnew(char *name, char *value);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				command_has_variable(t_com *com, t_list *local_env);
void				ft_unset(t_com *com, t_list **lenv, char **envp);

#endif