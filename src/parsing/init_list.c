/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:27:49 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/24 17:27:50 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_node(char *tk, int t)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = tk;
	node->type = t;
	node->next = NULL;
	return (node);
}

void	append_node(t_token **head, char *tk, int t)
{
	t_token	*node;
	t_token	*tmp;

	node = create_node(tk, t);
	if (!node)
		return ;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
