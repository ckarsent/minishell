/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 04:14:10 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/05 21:02:49 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*copy;

	i = 0;
	if (!src)
		return (NULL);
	copy = (char *) malloc((ft_strlen(src) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (src[i])
	{
		copy[i] = src[i];
		i ++;
	}
	copy[i] = '\0';
	return (copy);
}
