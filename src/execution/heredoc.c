/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:14:08 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/27 00:35:03 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
	}
}

int	set_heredoc(char *delimiter, bool fquote, t_data *d, char *name)
{
	char	*line;
	char	*res;
	int		fd;

	res = ft_strdup("");
	signal(SIGINT, signal_here_doc);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (g_signal == SIGINT)
		{
			free(line);
			break ;
		}
		if (!fquote)
			line = expansion(line, d);
		res = append_line(res, line);
		free(line);
	}
	fd = open_fd(res, name);
	if (fd > -1)
		return (close(fd), 0);
	return (-1);
}

int	handle_heredoc(t_cmd *cmd, int i, t_data *d, int *j)
{
	char	*name;

	cmd->is_heredoc = true;
	if (cmd->infile)
		free(cmd->infile);
	name = random_name((*j)++);
	if (!name)
		return (-1);
	cmd->infile = ft_strdup(name);
	if (!cmd->infile)
		return (free(name), -1);
	if (set_heredoc(cmd->tokens[i + 1], cmd->fquotes[i + 1], d, name) == -1)
	{
		free(name);
		d->last_exit = 1;
		return (-1);
	}
	free(name);
	return (0);
}

int	exec_heredoc(t_data *d)
{
	t_cmd	*t;
	int		i;
	int		j;

	t = d->clst;
	j = 1;
	while (t)
	{
		i = 0;
		while (i < t->size)
		{
			if (t->types[i] == 4 && !t->fquotes[i] && t->size - i > 1)
				t->is_heredoc = false;
			else if (t->types[i] == 6 && !t->fquotes[i] && t->size - i > 1)
			{
				if (handle_heredoc(t, i, d, &j) == -1)
					return (-1);
				i++;
			}
			i++;
		}
		t = t->next;
	}
	d->last_exit = 0;
	return (0);
}
