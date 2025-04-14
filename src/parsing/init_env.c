/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:33:59 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/08 12:00:21 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*allocate_node_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	append_env_node(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*tmp;

	node = allocate_node_env(key, value);
	if (!node)
		return ;
	if (!*env)
	{
		*env = node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	init_env(char **env, t_env **henv)
{
	int		i;
	int		n;
	char	*key;
	char	*value;

	i = 0;
	n = 0;
	while (env[i])
	{
		while (env[i][n] && env[i][n] != '=')
			n++;
		key = ft_strndup(env[i], n);
		if (!key)
			return ;
		value = ft_strdup(env[i] + n + 1);
		if (!value)
		{
			free(key);
			return ;
		}
		append_env_node(henv, key, value);
		n = 0;
		i++;
	}
}
