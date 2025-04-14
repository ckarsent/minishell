/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:37:02 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/13 19:20:02 by qboutel          ###   ########.fr       */
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
	bool			*fquotes; // 1 quote enleve
	int				size;
	char			*infile;
	char			*outfile;
	bool			is_append;
	bool			is_heredoc;
	//int				redir_in; // -1 par default 0 = redirin 1 = heredoc
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ########## [builtins] ########## */

/* echo.c */
//void    builtin_echo(t_token *htoken)
void    builtin_pwd();
void	builtin_env(t_env *env);
void	builtin_echo(char **args);
void	builtin_export(t_env *env, char **args);
void	builtin_unset(t_env **env, char *key);
int		builtin_cd(char **args, t_env *env);
void	builtin_exit(char **args, int last_exit);

/* ########## [execution.c] ########## */

/* cmd.c */
char	*ft_env(char **envp);
char	*get_cmd(char *cmd, char **envp);

/* heredoc.c */
int		set_heredoc(char *delimiter, bool fquote,  int last_exit, char *name);
void    exec_heredoc(t_cmd **hcmd, int last_exit);

/* execution.c */
int		openfile_output(char *file, bool append);
int		redirect(t_cmd *hcmd);// retour etat 0 bon -1 erreur fd
int		exec_fork(t_cmd **hcmd);
int	supp_heredoc(int nbr);
int		execution(t_cmd **hcmd, int last_exit, char **env, t_env **envp);

/* ########## [expansion] ########## */

/* expansion.c */
int		len_var(char *token, int *i);
int		len_expansion(char *token, int last_exit);
char	*var_expansion(char *token, int *i);
void	process_expansion(char *token, int *var, char **result, int last_exit);
char	*expansion(char *token, int last_exit);

/* ########## [parsing] ########## */

/* errors.c */
int		error_malloc_token(t_token *htoken);
int		error_syntaxe(t_token *htoken);

/* init_cmd.c */
int		count_after_pipe(t_token *htoken);
int		set_node_cmd(t_cmd *hcmd, t_token *htoken, int count);
t_cmd	*allocate_node_cmd(int count);
void	append_node_cmd(t_cmd **hcmd, t_cmd *node);
int		init_cmd(t_token *htoken, t_cmd **hcmd);

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

/* parsing */
int		parsing_line(char *line, t_token **htoken, t_cmd **hcmd, int last_exit);

/* quote.c */
int		check_quote(char *line);
bool	handle_quotes(char c, bool *squote, bool *dquote);
int		len_quote(char *token);
char	*delete_quote(char *token);
bool	flag_quote(char *token);

/* tokenize */
char	*extract_operator(char *line, int *i);
char	*extract_word(char *line, int *i);
char	*handle_token(char *line, t_token **head, bool *fheredoc, int last_exit);
int		tokenize(char *line, t_token **htoken, int last_exit);

/* type.c */
int		check_cmd(char *cmd);
int		check_arg(char *arg);
int		check_builtins(char *token, char *next);
void	which_type(t_token **htoken);

/* main.c */
void	signal_handler(int sig);
int		main(int argc, char **argv, char **env);

/* ########## [utils] ########## */

/* debug.c */
void	print_list_token(t_token *htoken);
void	print_list_cmd(t_cmd *hcmd);
void	print_list_env(t_env *env_list);

/* free.c */
void	free_list_token(t_token **htoken);
void	free_list_cmd(t_cmd **hcmd);
void	free_list_env(t_env **henv);
char	*free_split(char **split);

/* pingouin.c */
void	print_logo(void);
void	print_minishell(void);

/* ############################## */

#endif
