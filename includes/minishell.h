/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:06:30 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 20:24:46 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_muti/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

extern int	g_is_execute;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	char			*file;
	int				fd;
	int				type;
	char			*tmp_filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	struct s_cmd	*next;
	t_redir			*redirs;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	int				last_return ;
	t_cmd			*cmds;
	int				stdin_backup;
	int				stdout_backup;
	int				exit_status;	
	int				exit_requested;
}					t_shell;

typedef enum e_quote_state
{
	NONE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}					t_QuoteState;

// builtins.c
int					is_builtin(char *cmd[]);
int					execute_builtin(char *cmd[], t_shell *shell);

//BUILTINS
int					builtin_pwd(void);
int					builtin_echo(char **args);
int					builtin_exit(char **cmd, t_shell *shell);
int					builtin_cd(char **cmd, t_shell *shell);
int					builtin_env(char **envp, char **args);
void				builtin_export(char **env);
int					builtin_unset(t_shell *shell, char **args);

// tokenization.C
int					token_length(const char *line, int start);
int					count_token(char *line, t_shell *shell);
char				**tokenize(char *line, t_shell *shell);
t_cmd				*parse_tokens(char **tokens, t_shell *shell);
char				*clear_quotes(char *str);
char				**add_to_argv(char **argv, char *token);
void				add_redir(t_cmd *cmd, char *file, int type);

// executor.c
void				execute_cmd(t_shell *shell);
// int					execute_builtin(char *cmd[], t_shell *shell);
void				fork_and_execute_cmd(t_shell *shell);

// minishell.c
char				**copy_env(char **envp);
int					do_export(t_shell *shell, char **argv);
void				fork_and_execute_builtin(t_cmd *cmd, t_shell *shell);
void				init_signals(void);
void				init_shell(t_shell *shell, char **envp);

// pipeline.c
void				execute_pipeline(t_shell *shell);

// signal.c
void				handle_sig(int sig);
void				handle_sig_heredoc(int sig);

// get_path.c
char				*get_paths(t_shell *shell);
char				*check_paths(t_shell *shell, char **cmd, char *name);
char				*find_correct_path(t_shell *shell, char **cmd, char *name);
int					is_redir(char *str);
int					get_redir_type(char *str);
t_cmd				*init_cmd(t_cmd **head, t_cmd **curr);
// cleanup.c
void				free_tab(char **t);
void				exit_helper(t_shell *shell, bool fd);

// export.c
char				**add_to_env(char **old_env, char *new_var);
int					find_var(char **env, char *var_to_find);
char				**modify_env(char **env, char *new);
int					do_export(t_shell *shell, char **argv);

// free.c

char				**free_env_error(char **env, int i);
void				free_shell(t_shell *shell);
void				free_cmd_list(t_cmd *cmds);
void				sort_env(char **copy, int count);

// var.c

char				*expand_variable(char *str, t_shell *shell);
void				expansion_cmds(t_shell *shell);
int					is_valid(char c);
char				*get_env_value(char *var_name, char **env);

// heredoc.c
int					heredoc(char *delimiter, t_shell *shell, char *filename);
int					prepare_heredocs(t_shell *shell);

int					output(t_redir *redir, t_shell *shell);
int					redirections(t_cmd *cmd, t_shell *shell);
void				execute(t_cmd *cmd, t_shell *shell);
void				cleanup_child(t_shell *shell);
void				cleanup_child_and_exit(t_shell *shell, int status);
void				try_execute(char *path, char **argv,
						char **envp, t_shell *shell);

void				handle_command(t_cmd *cmd, t_shell *shell);
void				update_exit(t_shell *shell, int status);

//heredoc_quotes.c
char				*remove_quotes(char *str);
int					is_quoted(char *str);

// utils.c
void				print_errors(char *cmd, t_shell *shell, int status);
char				*extract_val(char *var_name, t_shell *shell);

// count.c
int					pipe_count(char **tokens, t_shell *shell);
int					redirections_count(char **tokens, t_shell *shell);
int					put_error(char *msg, t_shell *shell);
int					process_error(char **tokens, t_shell *shell, int i);

// heredoc_quotes.c
int					is_quoted(char *str);
char				*remove_quotes(char *str);

// minishell2.c
int					parse(char *rl, t_shell *shell);
void				process_argv_quotes(t_cmd *cmd);
int					loop(t_shell *shell);
void				process(t_shell *shell);
void				process_redir_quotes(t_cmd *cmd);
void				flag_process(t_shell *shell);

//minishell3.c
void				cmds_quotes(t_cmd *cmds);
void				free_env(char **envp);
void				exit_shell(t_shell *shell, int status);
int					match_env_key(const char *env, const char *key);
void				replace_env_var(t_shell *shell, const char *key,
						const char *value);
void				update_shlvl(t_shell *shell);
void				update_pwd(t_shell *shell);
void				init_shell(t_shell *shell, char **envp);

//heredoc_utils.c
void				close_heredocs(t_cmd *cmds);
char				*get_unique_filename(int index);
int					heredoc_wait_and_open(pid_t pid, char *filename,
						t_shell *shell);

// heredoc.c
void				handle(t_shell *shell, char *delimiter, int fd);

// minishell4.c
void				update_pwd(t_shell *shell);
void				update_shlvl(t_shell *shell);
void				replace_env_var(t_shell *shell, const char *key,
						const char *value);
int					match_env_key(const char *env, const char *key);
char				**copy_env(char **envp);

int					find_var(char **env, char *var_to_find);
int					is_valid_env_name(char *str);
int					handle_delimiter(char *line, int *i);
int					is_delimitor(char c);
int					ft_printf(int fd, const char *str, ...);

#endif
