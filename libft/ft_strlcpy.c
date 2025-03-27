/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:14:16 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/16 17:46:21 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_s;

	i = 0;
	j = 0;
	len_s = 0;
	while (src[len_s])
		len_s ++;
	if (dstsize != 0)
	{
		while (i < (dstsize - 1) && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (len_s);
}
