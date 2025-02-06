/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:53:11 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/05 15:30:59 by lfaria-m         ###   ########.fr       */
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
# include <ctype.h>

# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIRECT_IN 3
# define TOKEN_REDIRECT_OUT 4
# define TOKEN_APPEND 6
# define TOKEN_HEREDOC 5
# define TOKEN_DQUOTES 7


typedef struct s_com
{
	int				argc;
	char			**argv;
	int				total_commands;
	int				is_builtin;
	int				has_inpipe;
	int				has_outpipe;
	char 			*output_file;
	char			*input_file;
	int				append_output;
	char			*delim;
	int				input_fd;
	struct s_com	*next;
}					t_com;

typedef struct s_token
{
	char	*value;
	int		type;
	struct s_token *next;
}				t_token;

typedef struct s_hdline
{
	char	*value;
	struct	s_hdline *next;
}				t_hdline;


typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}					t_list;

t_com				*parse_input(char *str);
int					join_len(char *s1, char *s2);
void				free_double(char **arr);
void				handle_command(char *str, t_com *command,
						t_list *local_env);
int					is_command_builtin(t_com *com);
void				execute_builtin_command(t_com *command, t_list **local_env,
						char **envp);
void				path_split_append(t_com *command, t_list *local_env);
void				free_commands(t_com *cmd);
void				ft_echo(t_com command);
void				ft_env(char **envp, t_list *local_env);
void				ft_pwd(void);
void				ft_export(char *name_and_value, t_list **local_env, char **envp, int flag);
void				ft_cd(t_com command);
void				ft_exit(void);
t_list				*ft_lstnew(char *name, char *value);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				command_has_variable(t_com *com, t_list *local_env);
void				ft_unset(t_com *com, t_list **lenv, char **envp);
t_com				*malloc_commands(char **str);
void				execute_process(t_com *cmd, t_list **local_env, char **envp);
void				call_child_action(t_com command, t_list *local_env);
int					num_commands(char **str);
t_token				*tokenize_input(char *input);
void				free_tokens(t_token *tokens);
void				execute_pipeline(t_com *commands, t_list **local_env, char **envp);
char				**get_builtin_list(void);
int					is_command_builtin(t_com *com);
int					is_valid_path(char *exec_path, t_com *command, t_list *local_env);
int					handle_redirect_out(t_com *cmd);
int					handle_pipe_token(t_com **current_cmd, int *arg_count);
int					handle_redirect_token(t_com *current_cmd, t_token *cur_token, int append);
int					handle_heredoc_token(t_com *current_cmd, t_token *cur_token);
int 				handle_redirect_heredoc(t_com *cmd);

#endif