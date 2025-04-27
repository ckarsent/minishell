/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:35:05 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/27 00:07:21 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_check_heredoc(t_data *data, char **args, char **env)
{
	if (exec_heredoc(data) == -1)
	{
		ft_putstr_fd("heredoc : malloc\n", 2);
		free_full(data, args, env);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	exit_error(char **args, char *mess)
{
	ft_putstr_fd(mess, 2);
	free_split(args);
	exit(EXIT_FAILURE);
}

void	exit_cmd_not_found(t_data *data, char **args, char **env)
{
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": Command not found\n", 2);
	free_full(data, args, env);
	exit(127);
}

void	exit_cmd_not_exec(t_data *data, char **args, char **env)
{
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_full(data, args, env);
	exit(126);
}

void	setup_pipes(t_cmd *current, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (pipe_fd[0] > -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] > -1)
		close(pipe_fd[1]);
}
