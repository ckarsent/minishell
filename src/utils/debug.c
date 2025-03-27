/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:39:03 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/26 13:50:21 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_full_list(t_token *head)
{
	while (head)
	{
		printf("[%s](%d) -> ", head->token, head->type);
		head = head->next;
	}
	printf("NULL\n");
}

void	print_full_list_cmd(t_cmd *head)
{
	int	i;

	while (head)
	{
		i = 0;
		printf("\n");
		while (*(head->token))
		{
			printf("sous string : [%s], ", *(head->token)++);
		}
		printf("\n");
		while (i < head->size)
		{
			printf("int : (%d), ", head->type[i++]);
		}
		head = head->next;
	}
	printf("NULL\n");
}

// void	print_nbr_args(t_data d)
// {
// 	printf("\n------------------------------------\n");
// 	printf("nbr args : %d\n\n", d.count);
// }

void	print_env(char **env)
{
	printf("\n");
	while (*env != NULL)
		printf("%s\n", *env++);
	printf("\n");
}

void	print_list(t_token *head)
{
	while (head)
	{
		printf("[%s] -> ", head->token);
		head = head->next;
	}
	printf("NULL\n");
}
