/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:45:42 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/27 00:38:47 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process(char *line, t_data *data)
{
	char	**env;

	if (g_signal == SIGINT)
	{
		data->last_exit = 130;
		g_signal = 0;
	}
	add_history(line);
	env = env_to_tab(data->elst);
	if (parsing_line(line, data) == 0)
	{
		data->last_exit = execution(env, data);
		if (supp_heredoc(nbr_heredoc(data->tlst)) == -1)
			ft_putstr_fd("heredoc : malloc\n", 2);
	}
	free_split(env);
	free_list_token(&data->tlst);
	free_list_cmd(&data->clst);
	return (env);
}

void	init_main(void)
{
	print_logo();
	print_minishell();
	signaux(1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	data.tlst = NULL;
	data.clst = NULL;
	data.elst = NULL;
	data.last_exit = 0;
	(void)argv;
	if (argc > 1)
		return (printf("minishell: No arguments expected\n"), 1);
	init_main();
	init_env(envp, &data.elst);
	while (1)
	{
		line = readline("./minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			process(line, &data);
		free(line);
	}
	return (free_list_env(&data.elst), 0);
}
