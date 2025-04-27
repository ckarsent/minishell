/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:52:51 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/26 17:47:32 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	init_exec(t_data *data)
{
	t_exec	ex;

	ex.pipe_fd[0] = -1;
	ex.pipe_fd[1] = -1;
	ex.current = data->clst;
	ex.prev_fd = -1;
	ex.pid = -1;
	ex.last_pid = -1;
	ex.args = NULL;
	return (ex);
}

int	execution(char **env, t_data *data)
{
	t_exec	ex;

	ex = init_exec(data);
	exec_check_heredoc(data, NULL, env);
	while (ex.current)
	{
		ex.args = list_args(ex.current);
		if (handle_builtins(&ex, data, env))
		{
			ex.current = ex.current->next;
			continue ;
		}
		if (ex.current->next && pipe(ex.pipe_fd) == -1)
			exit_error(ex.args, "pipe failed\n");
		ex.pid = fork();
		if (ex.pid == -1)
			exit_error(ex.args, "fork failed\n");
		else if (ex.pid == 0)
			exec_child(&ex, data, env);
		else
			exec_parent(&ex);
		free_split(ex.args);
		ex.current = ex.current->next;
	}
	return (handle_wait(data, ex.last_pid));
}
