/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:04:36 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/24 04:08:21 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd(char *res, char *name)
{
	int	fd;

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
	char	*new_res;
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		return (NULL);
	new_res = ft_strjoin(res, tmp);
	free(tmp);
	free(res);
	if (!new_res)
		return (NULL);
	return (new_res);
}

char	*random_name(int index)
{
	char	*num;
	char	*name;

	num = ft_itoa(index);
	if (!num)
		return (NULL);
	name = ft_strjoin(".tmp_", num);
	if (!name)
		return (NULL);
	free(num);
	return (name);
}

int	supp_heredoc(int nbr)
{
	char	*num;
	char	*name;

	while (nbr)
	{
		num = ft_itoa(nbr);
		if (!num)
			return (-1);
		name = ft_strjoin(".tmp_", num);
		free(num);
		if (!name)
			return (-1);
		if (access(name, F_OK) == 0)
			unlink(name);
		free(name);
		nbr--;
	}
	return (0);
}

int	nbr_heredoc(t_token *htoken)
{
	int	count;

	count = 0;
	while (htoken)
	{
		if (!ft_strcmp(htoken->token, "<<") && htoken->fquote == 0)
			count++;
		htoken = htoken->next;
	}
	return (count);
}
