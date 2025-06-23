/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:38:47 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/20 20:40:53 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*target_path(t_env *env, char **args)
{
	if (args[1] == NULL)
		return (ft_getenv(env, "HOME"));
	else if (!ft_strcmp(args[1], "-"))
		return (ft_getenv(env, "OLDPWD"));
	else if (args[1] && args[2] == NULL)
		return (args[1]);
	else
		return (NULL);
}

void	update_pwd(t_env *env, char *old_pwd, char *new_pwd)
{
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(old_pwd);
		}
		else if (ft_strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_pwd);
		}
		env = env->next;
	}
}

int	builtin_cd(char **args, t_env *env)
{
	char	*path;
	char	*old_pwd;
	char	*current_pwd;

	path = target_path(env, args);
	if (!path)
		return (perror("cd"), EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd OLDPWD not set"), EXIT_FAILURE);
	if (chdir(path) != 0)
		return (perror("cd"), free(old_pwd), EXIT_FAILURE);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("cd"), free(old_pwd), EXIT_FAILURE);
	update_pwd(env, old_pwd, current_pwd);
	free(old_pwd);
	free(current_pwd);
	return (EXIT_SUCCESS);
}
