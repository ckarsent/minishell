/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:00:49 by ckarsent          #+#    #+#             */
/*   Updated: 2025/03/27 12:37:26 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type != PIPE)
	{
		count++;
		head = head->next;
	}
	return (count);
}

t_cmd	*allocate_new_node(int count)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->token = malloc(sizeof(char *) * (count + 1));
	new->type = malloc(sizeof(int) * count);
	new->size = count;
	if (!new->token || !new->type)
	{
		free(new->token);
		free(new->type);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	new_node(t_cmd *cmd, t_token **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		cmd->token[i] = (*tokens)->token;
		cmd->type[i] = (*tokens)->type;
		*tokens = (*tokens)->next;
		i++;
	}
	cmd->size = count;
	cmd->token[count] = NULL;
}

void	append_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*split_pipe(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new;
	int		count;

	cmd_list = NULL;
	new = NULL;
	while (tokens)
	{
		count = count_tokens(tokens);
		new = allocate_new_node(count);
		if (!new)
		{
			free_list_cmd(&cmd_list);
			return (NULL);
		}
		new_node(new, &tokens, count);
		append_cmd(&cmd_list, new);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmd_list);
}
