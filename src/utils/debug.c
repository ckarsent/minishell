/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:39:03 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/10 18:03:18 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_token(t_token *htoken)
{
	while (htoken)
	{
		printf("[%s](%d)/%d/ -> ", htoken->token, htoken->type,
			htoken->fquote);
		htoken = htoken->next;
	}
	printf("NULL\n");
}

void	print_list_cmd(t_cmd *hcmd)
{
	int	i;
	int	n;

	n = 0;
	printf("\n");
	while (hcmd)
	{
		i = 0;
		printf("--- NOEUD [%d] ---\n", n++);
		while (hcmd->tokens[i] && i < hcmd->size)
		{
			printf("[%s] (%d) /%d/\n", hcmd->tokens[i], hcmd->types[i],
				hcmd->fquotes[i]);
			i++;
		}
		printf("\n");
		hcmd = hcmd->next;
	}
	printf("NULL\n");
}

void	print_list_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("%s=%s\n\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
