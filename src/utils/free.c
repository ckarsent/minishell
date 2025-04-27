/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:43:34 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/24 03:47:10 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_full(t_data *d, char **split1, char **split2)
{
	if (supp_heredoc(nbr_heredoc(d->tlst)) == -1)
		ft_putstr_fd("heredoc : malloc\n", 2);
	free_list_token(&d->tlst);
	free_list_cmd(&d->clst);
	free_list_env(&d->elst);
	free_split(split1);
	free_split(split2);
}

void	free_list_token(t_token **htoken)
{
	t_token	*tmp;

	if (!htoken)
		return ;
	while (*htoken)
	{
		tmp = *htoken;
		*htoken = (*htoken)->next;
		if (tmp->token)
		{
			free(tmp->token);
			tmp->token = NULL;
		}
		free(tmp);
	}
}

void	free_list_cmd(t_cmd **hcmd)
{
	t_cmd	*tmp;

	if (!hcmd)
		return ;
	while (*hcmd)
	{
		tmp = *hcmd;
		*hcmd = (*hcmd)->next;
		if (tmp->tokens)
			free_split(tmp->tokens);
		if (tmp->infile)
		{
			free(tmp->infile);
			tmp->infile = NULL;
		}
		if (tmp->outfile)
		{
			free(tmp->outfile);
			tmp->outfile = NULL;
		}
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
		{
			free(split[i]);
			split[i] = NULL;
		}
		i++;
	}
	free(split);
	split = NULL;
	return (NULL);
}
