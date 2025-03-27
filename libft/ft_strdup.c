/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 04:14:10 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/28 14:55:14 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*copy;

	i = 0;
	len = 0;
	while (src[len])
		len ++;
	copy = (char *) malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	if (len > 0)
	{
		while (src[i])
		{
			copy[i] = src[i];
			i ++;
		}
	}
	copy[i] = '\0';
	return (copy);
}
