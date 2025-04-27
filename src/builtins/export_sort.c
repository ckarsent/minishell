/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:49:42 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/26 23:59:15 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sort_export(int arc, char **arv)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	while (i < arc)
	{
		flag = false;
		write(1, "declare -x ", 11);
		j = 0;
		while (arv[i][j])
		{
			write(1, &arv[i][j], 1);
			if (arv[i][j] == '=' && flag == false)
			{
				flag = true;
				write(1, "\"", 1);
			}
			j++;
		}
		if (flag)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

void	sort_export(int argc, char **argv)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
			{
				tmp = argv[i];
				argv[i] = argv[j];
				argv[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_sort_export(argc, argv);
}

int	is_valid(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
