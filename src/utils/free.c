/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:43:34 by ckarsent          #+#    #+#             */
/*   Updated: 2025/03/27 12:39:51 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_list(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

void	free_list_cmd(t_cmd **head)
{
	t_cmd	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (*(tmp->token))
			free_split(tmp->token);
		if (tmp->type)
			free(tmp->type);
		free(tmp);
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}
