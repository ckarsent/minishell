/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:39:54 by ckarsent          #+#    #+#             */
/*   Updated: 2025/03/27 12:34:32 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_malloc(t_token *head)
{
	while (head)
	{
		if (head->token == NULL)
			return (-1);
		head = head->next;
	}
	return (0);
}

int	error_syntaxe(t_token *head)
{
	if (head->type == PIPE)
		return (-1);
	while (head)
	{
		if (head->type >= PIPE && head->type <= HEREDOC && head->next != NULL)
		{
			if (head->next->type >= PIPE && head->next->type <= HEREDOC)
			{
				//last_exit = 2;
				return (-1);
			}
		}
		if (head->type == PIPE && head->next == NULL)
			return (-1);
		head = head->next;
	}
	return (0);
}
