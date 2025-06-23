/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:50:23 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/26 23:10:30 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing(t_env *tmp, char *value)
{
	if (tmp->value)
		free(tmp->value);
	if (value)
		tmp->value = ft_strdup(value);
	else
		tmp->value = NULL;
}

t_env	*create_new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (update_existing(tmp, value));
		tmp = tmp->next;
	}
	new = create_new_env(key, value);
	if (!new)
		return ;
	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	decoupe_export(t_env **env, char *arg)
{
	char	*tmp;
	char	*key;
	char	*value;
	char	*egal;

	tmp = ft_strdup(arg);
	value = NULL;
	egal = ft_strchr(tmp, '=');
	if (egal)
	{
		*egal = '\0';
		value = egal + 1;
	}
	key = tmp;
	if (is_valid(key))
		update_env(env, key, value);
	else
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		free(tmp);
		return (EXIT_FAILURE);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_env **env, char **args)
{
	int		i;
	bool	flag;
	char	**envp;

	flag = EXIT_SUCCESS;
	envp = env_to_tab(*env);
	if (!args[1])
		return (sort_export(env_list_size(*env),
				envp), free_split(envp), EXIT_SUCCESS);
	i = 0;
	while (args[++i])
	{
		if (decoupe_export(env, args[i]))
			flag = EXIT_FAILURE;
	}
	free_split(envp);
	return (flag);
}

/*
void	update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
*/