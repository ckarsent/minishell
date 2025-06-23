/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:37:02 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/27 00:34:32 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define RST  	"\033[0m"
# define YELLOW  "\033[93m"
# define BLUE    "\033[34m"
# define WHITE   "\033[80m"
# define BOLD    "\033[1m"

# define CMD 0 //ls
# define ARG 1 // -l
# define PIPE 2 // |
# define REDIR_OUT 3 // >
# define REDIR_IN 4 // <
# define APPEND 5 // >>
# define HEREDOC 6 // <<
# define STR 7
# define EXPANSE 8

typedef struct s_token
{
	char			*token;
	int				type;
	int				fquote;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**tokens;
	int				*types;
	bool			*fquotes;
	int				size;
	char			*infile;
	char			*outfile;
	bool			is_append;
	bool			is_heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_token			*tlst;
	t_cmd			*clst;
	t_env			*elst;
	int				last_exit;
}	t_data;

typedef struct s_exec
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*current;
	pid_t	pid;
	pid_t	last_pid;
	char	**args;
}			t_exec;

extern int	g_signal;

/* ########## [builtins] ########## */

/* cd.c */
char	*target_path(t_env *env, char **args);
void	update_pwd(t_env *env, char *old_pwd, char *new_pwd);
int		builtin_cd(char **args, t_env *env);

/* echo.c */
int		verif(char *s);
int		builtin_echo(char **args);

/* env.c */
int		builtin_env(t_env *env);

/* exit.c */
void	check_numeric(char **args, t_data *d, char **env);
int		builtin_exit(char **args, t_data *d, char **env);

/* export_sort.c */
void	print_sort_export(int arc, char **arv);
void	sort_export(int argc, char **argv);
int		is_valid(char *key);

/* export.c */
void	update_existing(t_env *tmp, char *value);
t_env	*create_new_env(char *key, char *value);
void	update_env(t_env **env, char *key, char *value);
int		decoupe_export(t_env **env, char *arg);
int		builtin_export(t_env **env, char **args);

/* pwd.c */
int		builtin_pwd(t_env *env);

/* unset.c */
void	delete_env_node(t_env **env, t_env *prec, t_env *tmp);
int		builtin_unset(t_env **env, char *key);

/* ########## [execution.c] ########## */

/* cmd.c */
char	*ft_env(char **envp);
char	*cmd_path(char **path, char *cmd);
char	*get_cmd(char *cmd, char **envp);

/* execution.c */
t_exec	init_exec(t_data *data);
int		execution(char **env, t_data *data);

/* execution2.c */
bool	check_builtin(char *cmd);
int		openfile_input(char *file);
int		openfile_output(char *file, bool append);
int		redirect(t_cmd *hcmd);
char	**list_args(t_cmd *hcmd);

/* execution3.c */
int		first_cond(t_cmd *hcmd, int *i, int *fd);
int		second_cond(t_cmd *hcmd, int *i, int *fd);
char	*find_cmd(t_cmd *hcmd);
int		exec_builtin(char **args, t_data *d, char **env);
bool	is_parent(char *cmd);

/* execution4.c */
int		exec_check_heredoc(t_data *data, char **args, char **env);
void	exit_error(char **args, char *mess);
void	exit_cmd_not_found(t_data *data, char **args, char **env);
void	exit_cmd_not_exec(t_data *data, char **args, char **env);
void	setup_pipes(t_cmd *current, int prev_fd, int *pipe_fd);

/* execution5.c */
void	redirects(t_cmd *current, t_data *data, char **args, char **env);
void	exec_child(t_exec *ex, t_data *data, char **env);
void	exec_parent(t_exec *ex);
int		handle_wait(t_data *data, pid_t last_pid);
int		handle_builtins(t_exec *ex, t_data *data, char **env);

/* heredoc.c */
int		set_heredoc(char *delimiter, bool fquote, t_data *d, char *name);
int		handle_heredoc(t_cmd *cmd, int i, t_data *d, int *j);
int		exec_heredoc(t_data *d);

/* heredoc2.c */
int		open_fd(char *res, char *name);
char	*append_line(char *res, char *line);
char	*random_name(int index);
int		supp_heredoc(int nbr);
int		nbr_heredoc(t_token *htoken);

/* ########## [expansion] ########## */

/* expansion.c */
int		len_var(char *token, int *i, t_data *d);
int		len_expansion(char *token, t_data *d);
char	*var_expansion(char *token, int *i, t_data *d);
void	process_expansion(char *token, int *var, char **result, t_data *d);
char	*expansion(char *token, t_data *d);

/* ########## [parsing] ########## */

/* errors.c */
int		error_malloc_token(t_token *htoken);
int		error_syntaxe(t_token *htoken);

/* init_cmd.c */
int		count_after_pipe(t_token *htoken);
int		set_node_cmd(t_cmd *hcmd, t_token *htoken, int count);
t_cmd	*allocate_node_cmd(int count);
void	append_node_cmd(t_cmd **hcmd, t_cmd *node);
int		init_cmd(t_data *d);

/* init_env.c */
t_env	*allocate_node_env(char *key, char *value);
void	append_env_node(t_env **env, char *key, char *value);
void	init_env(char **env, t_env **henv);

/* init_token */
t_token	*create_node_token(char *tk, int t, int flag);
void	append_node_token(t_token **htoken, char *tk, int t, int flag);

/* parsing_utils */
int		nbrlen(int nb, int *idx);
char	*ft_strndup(const char *s, int n);
int		a(int c);
char	*extract_operator(char *line, int *i);
char	*extract_word(char *line, int *i);

/* parsing */
bool	arg(char *arg);
bool	cd(char *arg);
int		check_fullspace(char *line);
int		check_errors(t_data *d);
int		parsing_line(char *line, t_data *d);

/* quote.c */
int		check_quote(char *line);
bool	handle_quotes(char c, bool *squote, bool *dquote);
int		len_quote(char *token);
char	*delete_quote(char *token);
bool	flag_quote(char *token);

/* tokenize */
void	handle_operator(char *line, int *i, bool *fheredoc, t_data *d);;
void	handle_word(char *line, int *i, bool *fheredoc, t_data *d);
char	*handle_token(char *line, bool *fheredoc, t_data *d);
int		tokenize(char *line, t_data *d);

/* type.c */
int		process_type1(t_token *tmp, bool *flags);
int		process_type2(t_token *tmp, bool *flags);
int		process_type3(t_token *tmp, bool *flags);
void	which_type(t_data *d);

/* ########## [utils] ########## */

/* debug.c */
void	print_list_token(t_token *htoken);
void	print_list_cmd(t_cmd *hcmd);
void	print_list_env(t_env *env_list);

/* free.c */

void	free_full(t_data *d, char **split1, char **split2);
void	free_list_token(t_token **htoken);
void	free_list_cmd(t_cmd **hcmd);
void	free_list_env(t_env **henv);
char	*free_split(char **split);

/* pingouin.c */
void	print_logo(void);
void	print_minishell(void);

/* env_utils.c */
int		env_list_size(t_env *env);
char	*ft_getenv(t_env *env, char *key);
char	*process_e2t(t_env *env);
char	**env_to_tab(t_env *env);

/* main.c */
int		main(int argc, char **argv, char **env);

/* signaux.c */
void	signaux_parent(int sig);
void	signaux(int is_parent);

/* ############################## */

#endif
