/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:38:47 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/13 19:34:47 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *target_path(t_env *env, char **args)
{
	if (args[1] == NULL)
		return (ft_getenv(env, "HOME"));
	else if (!ft_strncmp(args[1], "-", ft_strlen(args[1])))
		return ft_getenv(env, "OLDPWD");
	else if (args[1] && args[2] == NULL)
		return (args[1]);
	else
		return (NULL);
}

void	update_pwd(t_env *env, char *old_pwd, char *new_pwd)
{
	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = old_pwd;
		}
		else if (ft_strncmp(env->key, "PWD", 3) == 0)
		{
			free(env->value);
			env->value = new_pwd;
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
		return (perror("cd"), 1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd OLDPWD not set"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), free(old_pwd), 1);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("cd"), free(old_pwd), 1);
	update_pwd(env, old_pwd, current_pwd);
	return (0);
}