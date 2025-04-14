/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:38:09 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/10 17:56:02 by qboutel          ###   ########.fr       */
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
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_cmd, F_OK | X_OK) == 0)
			return (free_split(path), full_cmd);
		free(full_cmd);
	}
	return (free_split(path));
}

// void	exec_cmd(char *cmd, char **envp)
// {
// 	char	**args;
// 	char	*path;

// 	args = ft_split(cmd, ' ');
// 	if (!args)
// 		exit (1);
// 	path = get_cmd(args[0], envp);
// 	printf("ARG : %s\n", args[0]);
// 	if (!path)
// 	{
// 		free(path);
// 		free_split(args);
// 		perror("Command not found");
// 		exit(127);
// 	}
// 	execve(path, args, envp);
// 	perror("Execve failed");
// 	free_split(args);
// 	exit(1);
// }

