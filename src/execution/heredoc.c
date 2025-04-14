/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:14:08 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/12 19:09:54 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_fd (char *res, char *name)
{
	int fd;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(res), -1);
	write(fd, res, ft_strlen(res));
	close(fd);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (free(res), -1);
	return (free(res), fd);
}

char	*append_line(char *res, char *line)
{
	char *new_res;
	char *tmp = ft_strjoin(line, "\n");
	new_res = ft_strjoin(res, tmp);
	free(tmp);
	free(res);
	return (new_res);
}

int	set_heredoc(char *delimiter, bool fquote, int last_exit, char *name)
{
	char	*line;
	char	*res = ft_strdup("");
	int		fd;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			break ;
		if (!fquote)
			line = expansion(line, last_exit);
		res = append_line(res, line);
		free(line);
	}
	fd = open_fd(res, name);
	if (fd > -1)
		return (close(fd), 0);
	return (-1);
}

char *random_name(int index)
{
    char *num;
    char *name;

	num = ft_itoa(index);
	if (!num)
		return (NULL);
	name = ft_strjoin("tmp_", num);
	if (!name)
		return (NULL);
    free(num);
    return (name);
}

void	exec_heredoc(t_cmd **hcmd, int last_exit)
{
	t_cmd	*tmp;
	int     i;
	int     j = 1;
	char	*name;

	tmp = *hcmd;
	while (tmp)
	{
		i = 0;
		while (i < tmp->size)
		{
			if (tmp->types[i] == REDIR_IN && !tmp->fquotes[i] && (tmp->size - i) > 1)
			{
				tmp->is_heredoc = false;
				i++;
			}
			else if (tmp->types[i] == HEREDOC && !tmp->fquotes[i] && (tmp->size - i) > 1)
			{
				tmp->is_heredoc = true;

				if (tmp->infile)
					free(tmp->infile);

				name = random_name(j++);
				//if (!name)
					// EROOR MALLOC
				tmp->infile = ft_strdup(name);
				//free(name);
				if (set_heredoc(tmp->tokens[i + 1], tmp->fquotes[i + 1], last_exit, name) == -1)
					perror("heredoc failed");

				i++;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
