/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:36:02 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/26 23:56:37 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirects(t_cmd *current, t_data *data, char **args, char **env)
{
	int	fd;

	if (redirect(current) == -1)
	{
		free_full(data, args, env);
		exit(EXIT_FAILURE);
	}
	if (current->infile)
	{
		fd = openfile_input(current->infile);
		if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
			exit_error(args, "");
		close(fd);
	}
	if (current->outfile)
	{
		fd = openfile_output(current->outfile, current->is_append);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
			exit_error(args, "");
		if (fd > -1)
			close(fd);
	}
}

void	exec_child(t_exec *ex, t_data *data, char **env)
{
	char	*path_cmd;

	signaux(0);
	setup_pipes(ex->current, ex->prev_fd, ex->pipe_fd);
	redirects(ex->current, data, ex->args, env);
	if (check_builtin(ex->args[0]) && !is_parent(ex->args[0]))
	{
		data->last_exit = exec_builtin(ex->args, data, NULL);
		free_full(data, ex->args, env);
		exit(data->last_exit);
	}
	if (!is_parent(ex->args[0]) && ft_strlen(ex->args[0]) > 0)
	{
		path_cmd = get_cmd(ex->args[0], env);
		if (!path_cmd || !ft_strcmp(ex->args[0], ".."))
			exit_cmd_not_found(data, ex->args, env);
		if (access(path_cmd, X_OK) == -1)
			return (exit_cmd_not_exec(data, ex->args, env));
		execve(path_cmd, ex->args, env);
		ft_putstr_fd("execve failed\n", 2);
		free_full(data, ex->args, env);
		free(path_cmd);
		exit(EXIT_FAILURE);
	}
	return (free_full(data, ex->args, env), exit(EXIT_SUCCESS));
}

void	exec_parent(t_exec *ex)
{
	ex->last_pid = ex->pid;
	if (ex->prev_fd != -1)
		close(ex->prev_fd);
	if (ex->current->next)
	{
		close(ex->pipe_fd[1]);
		ex->prev_fd = ex->pipe_fd[0];
	}
}

int	handle_wait(t_data *data, pid_t last_pid)
{
	int		exit_code;
	int		status;
	pid_t	wpid;

	status = -1;
	exit_code = 0;
	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (wpid == last_pid && WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit: \n", 1);
			exit_code = 128 + WTERMSIG(status);
		}
		wpid = waitpid(-1, &status, 0);
	}
	if (last_pid == -1)
		return (data->last_exit);
	return (exit_code);
}

int	handle_builtins(t_exec *ex, t_data *data, char **env)
{
	if (!ex->args[0])
	{
		data->last_exit = 0;
		if (redirect(ex->current) == -2)
		{
			free_full(data, ex->args, env);
			ft_putstr_fd("redirect : malloc\n", 2);
			exit(EXIT_FAILURE);
		}
		free_split(ex->args);
		return (1);
	}
	if (check_builtin(ex->args[0]) && !ex->current->next && ex->prev_fd == -1
		&& is_parent(ex->args[0]))
	{
		data->last_exit = exec_builtin(ex->args, data, env);
		free_split(ex->args);
		return (1);
	}
	return (0);
}
