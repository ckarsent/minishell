/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:23:02 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/27 00:39:05 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

void	signaux_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_putstr_fd("\n", 1);
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signaux(int is_parent)
{
	if (is_parent)
	{
		signal(SIGINT, signaux_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
