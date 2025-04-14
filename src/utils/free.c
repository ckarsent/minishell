/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:43:34 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/11 13:44:06 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list_token(t_token **htoken)
{
	t_token	*tmp;

	while (*htoken)
	{
		tmp = *htoken;
		*htoken = (*htoken)->next;
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

void	free_list_cmd(t_cmd **hcmd)
{
	t_cmd	*tmp;

	while (*hcmd)
	{
		tmp = *hcmd;
		*hcmd = (*hcmd)->next;
		if (tmp->tokens)
			free_split(tmp->tokens);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);		
		free(tmp->types);
		free(tmp->fquotes);
		free(tmp);
	}
}

void	free_list_env(t_env **henv)
{
	t_env	*tmp;

	while (*henv)
	{
		tmp = *henv;
		*henv = (*henv)->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

char	*free_split(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = 0;
	while (split[i] != NULL)
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
