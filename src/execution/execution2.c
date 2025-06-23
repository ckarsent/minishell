/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:33:28 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/26 22:47:01 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd) || !ft_strcmp("pwd",
			cmd) || !ft_strcmp("export", cmd) || !ft_strcmp("unset", cmd)
		|| !ft_strcmp("env", cmd) || !ft_strcmp("exit", cmd))
		return (true);
	return (false);
}

int	openfile_input(char *file)
{
	int	fd;

	if (access(file, F_OK | R_OK) == -1)
	{
		perror(file);
		return (-1);
	}
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		perror(file);
	return (fd);
}

int	openfile_output(char *file, bool append)
{
	int	fd;

	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
		{
			perror(file);
			return (-1);
		}
	}
	if (append == true)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(file);
	return (fd);
}

int	redirect(t_cmd *hcmd)
{
	int	fd;
	int	i;
	int	ret;

	i = 0;
	while (i < hcmd->size)
	{
		if (hcmd->types[i] == REDIR_IN && !hcmd->fquotes[i]
			&& (hcmd->size - i) > 1)
		{
			ret = first_cond(hcmd, &i, &fd);
			if (ret != 0)
				return (ret);
		}
		else if ((hcmd->types[i] == REDIR_OUT || hcmd->types[i] == APPEND)
			&& !hcmd->fquotes[i] && (hcmd->size - i) > 1)
		{
			ret = second_cond(hcmd, &i, &fd);
			if (ret != 0)
				return (ret);
		}
		i++;
	}
	return (0);
}

char	**list_args(t_cmd *hcmd)
{
	char	**args;
	int		vars[3];

	vars[0] = ((vars[1] = (vars[2] = 0)));
	args = (char **)malloc(sizeof(char *) * (hcmd->size + 1));
	if (!args)
		return (NULL);
	while (vars[0] < hcmd->size)
	{
		if ((hcmd->types[vars[0]] == 4 || hcmd->types[vars[0]] == 6)
			&& !hcmd->fquotes[vars[0]] && (hcmd->size - vars[0]) > 1)
			vars[0]++;
		else if ((hcmd->types[vars[0]] == 3 || hcmd->types[vars[0]] == 5)
			&& !hcmd->fquotes[vars[0]] && (hcmd->size - vars[0]) > 1)
			vars[0]++;
		else if (hcmd->types[vars[0]] == CMD)
		{
			vars[2] = 1;
			args[vars[1]++] = ft_strdup(hcmd->tokens[vars[0]]);
		}
		else if (vars[2] == 1)
			args[vars[1]++] = ft_strdup(hcmd->tokens[vars[0]]);
		vars[0]++;
	}
	return ((args[vars[1]] = NULL), args);
}

/*
char	**list_args(t_cmd *hcmd)
{
	char	**args;
	bool	flag_cmd;
	int		i;
	int		j;

	i = ((j = 0));
	flag_cmd = false;
	args = (char **)malloc(sizeof(char *) * (hcmd->size + 1));
	while (i < hcmd->size)
	{
		if ((hcmd->types[i] == REDIR_IN || hcmd->types[i] == HEREDOC)
			&& !hcmd->fquotes[i] && (hcmd->size - i) > 1)
			i++;
		else if ((hcmd->types[i] == REDIR_OUT || hcmd->types[i] == APPEND)
				&& !hcmd->fquotes[i] && (hcmd->size - i) > 1)
			i++;
		else if (hcmd->types[i] == CMD)
		{
			flag_cmd = true;
			args[j++] = ft_strdup(hcmd->tokens[i]);
		}
		else if (flag_cmd == true)
			args[j++] = ft_strdup(hcmd->tokens[i]);
		i++;
	}
	args[j] = NULL;
	return (args);
}
*/
