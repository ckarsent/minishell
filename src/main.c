/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:45:42 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/27 12:41:18 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n./minishell$ ", 12);
}

int	main(int argc, char **argv)
{
	t_token	*head;
	t_cmd	*cmd;
	char	*line;

	(void)argv;
	head = NULL;
	cmd = NULL;
	if (argc > 1)
		return (ft_putstr_fd("minishell: No arguments expected\n", 2), 1);
	print_logo();
	print_minishell();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
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
			parsing_line(line, &head, &cmd);
			free_list(&head);
			free_list_cmd(&cmd);
		}
		free(line);
	}
	return (0);
}
