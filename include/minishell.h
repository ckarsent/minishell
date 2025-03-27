/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:37:02 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/26 14:02:18 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
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
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**token;
	int				*type;
	int				size;
	struct s_cmd	*next;
}	t_cmd;

/* ########## [builtins] ########## */

/* echo.c */

/* ########## [builtins] ########## */

/* branch.c */
t_cmd	*split_pipe(t_token *head);

/* ########## [parsing] ########## */

/* errors.c */
int		error_malloc(t_token *head);
int		error_syntaxe(t_token *head);

/* expansion_len.c */
char	*extract_var(char *token, int start);
int		process_len(char *token, int *i, int last_exit);
int		get_var_length(char *token, int *i);
int		len_expansion(char *token, int last_exit);

/* expansion.c */
void	append_var_value(int *j, char *var, char **result);
void	handle_exit_status(int *j, char **result, int last_exit);
void	process_variable(char *token, int *var, char **result, int last_exit);
char	*expansion(char *token, int last_exit);

/* init_list */
t_token	*create_node(char *tk, int t);
void	append_node(t_token **head, char *tk, int t);

/* parsing_utils */
int		check_quote(char *line);
bool	handle_quotes(char c, bool *squote, bool *dquote);
int		len_quote(char *token);
char	*delete_quote(char *token);
int		ft_nbrlen(int nb);

/* parsing */
int		parsing_line(char *line, t_token **head, t_cmd **cmd);

/* tokenize */
char	*extract_operator(char *line, int *i);
char	*extract_word(char *line, int *i);
int		tokenize(char *line, t_token **head);

/* main.c */
void	signal_handler(int sig);
int		main(int argc, char **argv);

/* type.c */
int		check_cmd(char *cmd);
int		check_arg(char *arg);
void	which_type(t_token **head);

/* ########## [utils] ########## */

/* debug.c */
void	print_full_list(t_token *head);
void	print_env(char **env);
void	print_list(t_token *head);

/* free.c */
void	free_list(t_token **head);
void	free_list_cmd(t_cmd **head);
void	print_full_list_cmd(t_cmd *head);
void	free_split(char **split);

/* print.c */
void	print_logo(void);
void	print_minishell(void);

/* ############################## */

#endif
