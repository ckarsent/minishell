/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:01:46 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/27 00:05:46 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*ft_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*process_e2t(t_env *env)
{
	char	*tmp;
	int		len;

	if (env->value)
	{
		len = ft_strlen(env->key) + 1 + ft_strlen(env->value) + 1;
		tmp = malloc(sizeof(char) * len);
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, env->key, len);
		ft_strlcat(tmp, "=", len);
		ft_strlcat(tmp, env->value, len);
	}
	else
		tmp = ft_strdup(env->key);
	return (tmp);
}

char	**env_to_tab(t_env *env)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (env_list_size(env) + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		tab[i] = process_e2t(env);
		if (!tab[i])
			return (NULL);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
