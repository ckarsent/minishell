/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:52:34 by qboutel           #+#    #+#             */
/*   Updated: 2025/06/23 17:33:52 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-')
		i++;
	else
		return (0);
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	flag;

	flag = 1;
	i = 1;
	if (!args[1])
		return (printf("\n"), EXIT_FAILURE);
	while (args[i] && verif(args[i]))
	{
		flag = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
