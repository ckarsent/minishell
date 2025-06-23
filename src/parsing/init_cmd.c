/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:48:46 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/17 11:08:08 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_after_pipe(t_token *htoken)
{
	int	count;

	count = 0;
	while (htoken && htoken->type != PIPE)
	{
		count++;
		htoken = htoken->next;
	}
	return (count);
}

int	set_node_cmd(t_cmd *hcmd, t_token *htoken, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		hcmd->tokens[i] = ft_strdup(htoken->token);
		if (!hcmd->tokens[i])
			return (-1);
		hcmd->types[i] = htoken->type;
		hcmd->fquotes[i] = htoken->fquote;
		htoken = htoken->next;
		i++;
	}
	hcmd->size = count;
	hcmd->tokens[count] = NULL;
	return (0);
}

t_cmd	*allocate_node_cmd(int count)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->tokens = malloc(sizeof(char *) * (count + 1));
	if (!node->tokens)
		return (NULL);
	node->types = malloc(sizeof(int) * count);
	if (!node->types)
		return (free(node->tokens), NULL);
	node->fquotes = malloc(sizeof(int) * count);
	if (!node->fquotes)
		return (free(node->tokens), free(node->types), NULL);
	node->size = count;
	node->infile = NULL;
	node->outfile = NULL;
	node->is_append = false;
	node->is_heredoc = false;
	node->next = NULL;
	return (node);
}

void	append_node_cmd(t_cmd **hcmd, t_cmd *node)
{
	t_cmd	*tmp;

	if (!*hcmd)
		*hcmd = node;
	else
	{
		tmp = *hcmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	init_cmd(t_data *d)
{
	t_cmd	*node;
	int		count;
	t_token	*htoken;

	htoken = d->tlst;
	d->clst = NULL;
	while (htoken)
	{
		count = count_after_pipe(htoken);
		node = allocate_node_cmd(count);
		if (!node)
			return (-1);
		if (set_node_cmd(node, htoken, count) == -1)
			return (-1);
		append_node_cmd(&d->clst, node);
		while (htoken && htoken->type != PIPE)
			htoken = htoken->next;
		if (htoken && htoken->type == PIPE)
			htoken = htoken->next;
	}
	return (0);
}
