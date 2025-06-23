/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:38:09 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/26 18:05:39 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*cmd_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_cmd;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_cmd)
			return (NULL);
		if (access(full_cmd, F_OK) == 0)
			return (full_cmd);
		free(full_cmd);
	}
	return (NULL);
}

char	*get_cmd(char *cmd, char **envp)
{
	char	**path;
	char	*result;

	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (!ft_env(envp))
		return (NULL);
	path = ft_split(ft_env(envp), ':');
	if (!path)
		return (NULL);
	result = cmd_path(path, cmd);
	free_split(path);
	return (result);
}

/*
char	*get_cmd(char *cmd, char **envp)
{
	int		i;
	char	*full_cmd;
	char	*tmp;
	char	**path;

	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (!ft_env(envp))
		return (NULL);
	path = ft_split(ft_env(envp), ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (free_split(path));
		full_cmd = ft_strjoin(tmp, cmd);
		if (!full_cmd)
			return (free(tmp), free_split(path), NULL);
		free(tmp);
		if (access(full_cmd, F_OK | X_OK) == 0)
			return (free_split(path), full_cmd);
		free(full_cmd);
	}
	return (free_split(path));
}
	*/