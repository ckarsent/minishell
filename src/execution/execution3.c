/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:34:17 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/26 22:59:00 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_cond(t_cmd *hcmd, int *i, int *fd)
{
	if (hcmd->infile)
		free(hcmd->infile);
	hcmd->infile = ft_strdup(hcmd->tokens[*i + 1]);
	if (!hcmd->infile)
		return (-2);
	*fd = openfile_input(hcmd->infile);
	if (*fd < 0)
		return (-1);
	close(*fd);
	(*i)++;
	return (0);
}

int	second_cond(t_cmd *hcmd, int *i, int *fd)
{
	if (hcmd->outfile)
		free(hcmd->outfile);
	hcmd->outfile = ft_strdup(hcmd->tokens[*i + 1]);
	if (!hcmd->outfile)
		return (-2);
	if (hcmd->types[*i] == APPEND)
		hcmd->is_append = true;
	else
		hcmd->is_append = false;
	*fd = openfile_output(hcmd->outfile, hcmd->is_append);
	if (*fd < 0)
		return (-1);
	close (*fd);
	(*i)++;
	return (0);
}

char	*find_cmd(t_cmd *hcmd)
{
	int	i;

	i = 0;
	while (i < hcmd->size)
	{
		if (hcmd->types[i] == CMD)
			return (hcmd->tokens[i]);
		i++;
	}
	return (NULL);
}

int	exec_builtin(char **args, t_data *d, char **env)
{
	int	ret;

	ret = 0;
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "pwd"))
		ret = builtin_pwd(d->elst);
	else if (!ft_strcmp(args[0], "env"))
		ret = builtin_env(d->elst);
	else if (!ft_strcmp(args[0], "cd"))
		ret = builtin_cd(args, d->elst);
	else if (!ft_strcmp(args[0], "exit"))
		ret = builtin_exit(args, d, env);
	else if (!ft_strcmp(args[0], "echo"))
		ret = builtin_echo(args);
	else if (!ft_strcmp(args[0], "export"))
		ret = builtin_export(&d->elst, args);
	else if (!ft_strcmp(args[0], "unset"))
		ret = builtin_unset(&d->elst, args[1]);
	else
		return (1);
	d->last_exit = ret;
	return (ret);
}

bool	is_parent(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cd"))
		return (true);
	if (!ft_strcmp(cmd, "exit"))
		return (true);
	if (!ft_strcmp(cmd, "export"))
		return (true);
	if (!ft_strcmp(cmd, "unset"))
		return (true);
	return (false);
}
