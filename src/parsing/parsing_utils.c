/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:44:09 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/06 18:41:17 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbrlen(int nb, int *idx)
{
	int			count;
	long int	i;

	count = 1;
	i = nb;
	if (nb < 0)
	{
		i *= (-1);
		count++;
	}
	while (i >= 10)
	{
		i /= 10;
		count++;
	}
	(*idx)+=2; // decal lindex de i pour le len
	return (count);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && i < n)
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (0);
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
