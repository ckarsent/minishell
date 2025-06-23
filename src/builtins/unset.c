/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:28:38 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/27 00:05:19 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env_node(t_env **env, t_env *prec, t_env *tmp)
{
	if (prec)
		prec->next = tmp->next;
	else
		*env = tmp->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

int	builtin_unset(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prec;

	tmp = *env;
	prec = NULL;
	if (!key)
		return (EXIT_SUCCESS);
	while (tmp)
	{
		if (!is_valid(key))
			return (ft_putstr_fd(" not a valid identifier\n", 2), EXIT_SUCCESS);
		if (ft_strcmp(tmp->key, key) == 0)
		{
			delete_env_node(env, prec, tmp);
			return (EXIT_SUCCESS);
		}
		else
			prec = tmp;
		tmp = prec->next;
	}
	return (EXIT_SUCCESS);
}
