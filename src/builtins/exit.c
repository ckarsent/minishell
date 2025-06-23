/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:03:51 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/26 22:34:35 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_numeric(char **args, t_data *d, char **env)
{
	int	i;

	i = 0;
	if (args[1][i] == '-' || args[1][i] == '+')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_full(d, args, env);
			exit(2);
		}
		i++;
	}
}

int	check_alpha(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_data *d, char **env)
{
	int	ret;

	if (args[1] == NULL)
	{
		free_full(d, args, env);
		exit(d->last_exit);
	}
	else if ((args[1] && args[2] == NULL) || check_alpha(args[1]))
	{
		check_numeric(args, d, env);
		ret = ft_atoi(args[1]);
		if (!ret)
		{
			free_full(d, args, env);
			ft_putstr_fd("exit : malloc\n", 2);
			exit(1);
		}
		free_full(d, args, env);
		exit((unsigned char)ret);
	}
	else
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
}
