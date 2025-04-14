/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:46:33 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/08 11:53:53 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_node_token(char *tk, int t, int flag)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = tk;
	node->type = t;
	node->fquote = flag;
	node->next = NULL;
	return (node);
}

void	append_node_token(t_token **htoken, char *tk, int t, int flag)
{
	t_token	*node;
	t_token	*tmp;

	node = create_node_token(tk, t, flag);
	if (!node)
		return ;
	if (*htoken == NULL)
	{
		*htoken = node;
		return ;
	}
	tmp = *htoken;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
