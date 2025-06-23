/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:39:10 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/17 16:30:50 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		while (env)
		{
			if (ft_strcmp(env->key, "PWD") == 0)
			{
				free(env->value);
				env->value = ft_strdup(cwd);
				break ;
			}
			env = env->next;
		}
		free(cwd);
		return (EXIT_SUCCESS);
	}
	perror("getcwd");
	return (EXIT_FAILURE);
}
