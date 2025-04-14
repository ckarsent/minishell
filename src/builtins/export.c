/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:50:23 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/14 01:25:36 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_list_size(t_env *env)
{
	int count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char **env_to_tab(t_env *env)
{
	char	**tab;
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tab = malloc(sizeof(char *) * (env_list_size(env) + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		if (env->value)
		{
			len = ft_strlen(env->key) + 1 + ft_strlen(env->value) + 1;
			tmp = malloc(strlen(env->key) + strlen(env->value) + 2);
			if (!tmp)
				return NULL;
			ft_strlcpy(tmp, env->key, len);
			ft_strlcat(tmp, "=", len);
			ft_strlcat(tmp, env->value, len);
		}
		else
			tmp = ft_strdup(env->key);
		tab[i++] = tmp;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	print_sort_export(int arc, char **arv)
{
	int	i;
	int	j;

	i = 1;
	while (i < arc)
	{
		write(1, "declare -x ", 11);
		j = 0;
		while (arv[i][j])
		{
			write(1, &arv[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	sort_export(int argc, char **argv)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
			{
				tmp = argv[i];
				argv[i] = argv[j];
				argv[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_sort_export(argc, argv);
}

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

int	is_valid(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	decoupe_export(t_env **env, char *arg)
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
		printf("ERROR\n");
	free(tmp);
}

void	builtin_export(t_env *env, char **args)
{
	int		i;

	if (!args[1])
		return (sort_export(env_list_size(env), env_to_tab(env)));
	i = 0;
	while (args[++i])
		decoupe_export(&env, args[i]);
}
