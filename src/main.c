/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:45:42 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/14 10:35:04 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_heredoc(t_token *htoken)
{
	int count = 0;

	while (htoken)
	{
		if (!ft_strncmp(htoken->token, "<<", 2) && ft_strlen(htoken->token) == 2 && htoken->fquote == 0)
			count++;
		htoken = htoken->next;
	}
	return (count);
}


void	signal_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n./minishell$ ", 12);
}

int	main(int argc, char **argv, char **env)
{
	t_token	*htoken;
	t_cmd	*hcmd;
	t_env	*henv;
	int		last_exit;
	char	*line;

	(void)argv;
	htoken = NULL;
	hcmd = NULL;
	henv = NULL;
	last_exit = 258;
	if (argc > 1)
		return (ft_putstr_fd("minishell: No arguments expected\n", 2), 1);
	//print_logo();
	//print_minishell();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	init_env(env, &henv);
	//print_list_env(henv);

	printf("\n\n\n\n");
	while (1)
	{
		line = readline("./minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			parsing_line(line, &htoken, &hcmd, last_exit);
			last_exit = execution(&hcmd, last_exit, env, &henv);
			if (supp_heredoc(nbr_heredoc(htoken)) == -1)
				perror("eroor malloc");
			free_list_token(&htoken);
			free_list_cmd(&hcmd);
		}
		free(line);
	}
	free_list_env(&henv);
	return (0);
}
