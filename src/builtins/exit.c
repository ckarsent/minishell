/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:03:51 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/13 19:21:53 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FREE A METTRE
void	builtin_exit(char **args, int last_exit)
{
	int i;
	int	ret;

	i = 0;
	if (args[1] == NULL)
		exit(last_exit);
	else if (args[1] && args[2] == NULL)
	{
		if (args[1][i] == '-' || args[1][i] == '+')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				perror("error exit");
				exit(2);
			}
			i++;
		}
		ret = ft_atoi(args[1]);
		if (!ret)
		{
			perror("error malloc exit");
			return ;
		}
		exit((unsigned char)ret);
	}
	else
		perror("trop arg");
}
