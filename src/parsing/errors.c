/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:39:54 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/20 19:30:46 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_malloc_token(t_token *htoken)
{
	while (htoken)
	{
		if (htoken->token == NULL)
			return (-1);
		htoken = htoken->next;
	}
	return (0);
}

int	error_syntaxe(t_token *htoken)
{
	if (htoken->type == PIPE)
		return (-1);
	while (htoken)
	{
		if (htoken->type >= PIPE && htoken->type <= HEREDOC
			&& htoken->next == NULL)
			return (-1);
		if (htoken->type == PIPE && htoken->next->type == PIPE
			&& htoken->next != NULL)
			return (-1);
		if (htoken->type >= REDIR_OUT && htoken->type <= HEREDOC
			&& htoken->next != NULL)
		{
			if (htoken->next->type >= PIPE && htoken->next->type <= HEREDOC)
				return (-1);
		}
		htoken = htoken->next;
	}
	return (0);
}
