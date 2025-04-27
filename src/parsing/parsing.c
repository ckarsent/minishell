/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:30:05 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/26 18:04:39 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	arg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (false);
	if (!arg[1])
		return (false);
	while (arg[i])
		if (!ft_isalpha(arg[i++]))
			return (false);
	return (true);
}

bool	cd(char *arg)
{
	if (!ft_strcmp(arg, ".."))
		return (true);
	while (*arg)
	{
		if (ft_strcmp(arg, "../"))
			return (false);
		arg += 3;
		if (ft_strlen(arg) == 2 && !ft_strcmp(arg, ".."))
			arg += 2;
	}
	return (true);
}

int	check_fullspace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (-1);
}

int	check_errors(t_data *d)
{
	if (error_malloc_token(d->tlst) == -1)
	{
		d->last_exit = 1;
		return (ft_putstr_fd("malloc token error\n", 2), -1);
	}
	if (error_syntaxe(d->tlst) == -1)
	{
		d->last_exit = 2;
		return (ft_putstr_fd("syntax error\n", 2), -1);
	}
	return (0);
}

int	parsing_line(char *line, t_data *d)
{
	if (check_quote(line) == -1)
	{
		d->last_exit = 2;
		return (ft_putstr_fd("Bad quote\n", 2), -1);
	}
	if (check_fullspace(line) == -1)
	{
		d->last_exit = 0;
		return (-1);
	}
	tokenize(line, d);
	which_type(d);
	if (check_errors(d) == -1)
		return (-1);
	if (init_cmd(d) == -1)
	{
		d->last_exit = 1;
		return (ft_putstr_fd("malloc cmd error\n", 2), -1);
	}
	return (0);
}
