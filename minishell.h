/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:53:11 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 17:01:37 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h> // For signal, sigaction, sigemptyset, sigaddset, kill
# include "libft.h"
# include <ctype.h>
# include <curses.h> // Often provides termcap functionality
# include <dirent.h> // For opendir, readdir, closedir
# include <fcntl.h>  // For open
# include <readline/history.h>
# include <readline/readline.h>
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

# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIRECT_IN 3
# define TOKEN_REDIRECT_OUT 4
# define TOKEN_APPEND 6
# define TOKEN_HEREDOC 5
# define TOKEN_DQUOTES 7
# define TOKEN_SQUOTES 8

extern int	g_exit_status;

typedef struct s_com
{
	char			**argv;
	int				is_builtin;
	int				has_inpipe;
	int				has_outpipe;
	char			*output_file;
	int				append_output;
	int				d_quote;
	char			*delim;
	struct s_squote	*s_quote;
	struct s_com	*next;
}					t_com;

typedef struct s_data
{
	struct s_list	*envp;
	struct s_list	*local_env;

}					t_data;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_squote
{
	int				pos;
	struct s_squote	*next;
}					t_squote;

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}					t_list;

t_com				*parse_input(char *str);
int					join_len(char *s1, char *s2);
void				free_double(char **arr);
void				handle_command(char *str, t_com *command, t_data *data);
int					is_command_builtin(t_com *com);
void				execute_builtin_command(t_com *command, t_data *data);
void				path_split_append(t_com *command, t_data *data);
void				free_commands(t_com *cmd);
int					ft_echo(t_com command);
int					ft_env(t_data *data);
int					ft_pwd(void);
int					ft_export(char **name_and_value, t_com *cmd, t_data *data,
						int flag);
int					ft_cd(t_com command);
int					ft_exit(t_com *cmd, t_data *data);
t_list				*ft_lstnew(char *name, char *value);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				command_has_variable(t_com *com, t_list *local_env);
int					ft_unset(t_com *com, t_data *data);
t_com				*malloc_commands(char **str);
void				execute_process(t_com *cmd, t_data *data);
void				call_child_action(t_com command, t_data *data);
int					num_commands(char **str);
t_token				*tokenize_input(char *input);
void				free_tokens(t_token *tokens);
void				execute_pipeline(t_com *commands, t_data *data);
char				**get_builtin_list(void);
int					is_command_builtin(t_com *com);
int					is_valid_path(char *exec_path, t_com *command,
						t_data *data);
int					handle_redirect_out(t_com *cmd);
int					handle_pipe_token(t_com **current_cmd, int *arg_count);
int					handle_redirect_token(t_com *current_cmd,
							t_token **cur_token,
							int append);
int					handle_heredoc_token(t_com *current_cmd,
							t_token *cur_token);
int					handle_redirect_heredoc(t_com *cmd);
int					handle_squotes(t_com *cmd, int pos);
int					check_if_quotes(t_com *cmd, int nb);
int					token_dispatcher(t_com **commands, t_com **current_cmd,
						t_token **tokens, int *arg_count);
int					create_new_arg(int *arg_count, t_com *current_cmd,
						t_token *cur_token);
int					create_new_command(t_com **current_cmd, int *arg_count,
						t_token *cur_token);
int					arg_helper(t_token *cur_token, t_com *current_cmd,
						int *arg_count);
int					temp_arg_creator(t_com *current_cmd, char **temp_argv,
						int *arg_count);
int					handle_quotes(char *input, int *i, t_token **tokens);
void				handle_redirections_in(char *input, int *i,
						t_token **tokens);
void				add_token(t_token **tokens, char *value, int type, int owner);
int					set_variable(char **name_and_value, char *equals, t_data *data, t_com *cmd);
char				*get_value(char *equals);
char				*get_name(char *str, char *equal);
int					update_var(char *name, char *value, t_list **local_env);
void				signal_handler_interactive(void);
void				signal_handler_non_interactive(void);
void				signal_handler_heredoc(void);
void				store_exit_status(int status);
void				handle_no_args(t_data *data);
int					handle_both_cases(char *equals, char **name_and_value, t_com *cmd, t_data *data);
int					create_new_command(t_com **current_cmd, int *arg_count, t_token *cur_token);
int					set_variable(char **name_and_value, char *equals, t_data *data, t_com *cmd);
int					set_env(t_list **env_list, char **envp);
char				**env_list_to_envp(t_list *env_list);
int					find_path(t_data *data);
int					update_env_var(t_com *cmd, t_data *envp);
char				*get_value(char *equals);
void				handle_direct_path(t_com *cmd, t_data *data);
char				*ft_strjoin_free(char *s1, char *s2);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				free_lists(t_data *data);
void				free_single_token(t_token *token);
char				*handle_input(void);
void				execute_input(char *input, t_com **commands, t_data *data);
void				finish_execution(t_com *command, char *input, t_data *data);
void				handle_interactive(int sig);
void				handle_non_interactive(int sig);
void				ignore_sigquit(void);
int					create_cmd_path(int *len, char **current_path_split, t_com *cmd, char **exec_path);
void				execute_command_from_path(char *exec_path, char **path_split, t_com *command, t_data *data);
char				*handle_word(char *input, int *i);
t_token				*new_token(char *value, int type, int take_ownership);
void				add_token(t_token **tokens, char *value, int type, int take_ownership);
void				free_single_token(t_token *token);
int					is_operator_start(char *input, int *i);
void				handle_pipe(char *input, int *i, t_token **tokens);
void				handle_redirect_it(char *input, int *i, t_token **tokens);
void				handle_redirect_ot(char *input, int *i, t_token **tokens);
void				handle_non_operator(char *input, int *i, t_token **tokens);
void				handle_operators(char *input, int *i, t_token **tokens);
void				skip_spaces(char *input, int *i);
t_token				*get_last_token(t_token *tokens);
int 				join_quoted_token(char *input, int *i, t_token **tokens, t_token *last);
int					join_word_token(char *input, int *i, t_token **tokens, t_token *last);
int					process_operator(char *input, int *i, t_token **tokens, char **buf);
int					process_quoted_string(char *input, int *i, t_token **tokens, char **buf);
void				handle_word_tokens(t_com **commands, t_com **current_cmd, t_token *tokens, int *arg_count);















#endif