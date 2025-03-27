/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:03:42 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/15 01:17:26 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = 0;
	len_s = 0;
	i = 0;
	while (dst[len_d] && len_d < dstsize)
		len_d ++;
	while (src[len_s])
		len_s ++;
	if (dstsize <= len_d)
		return (dstsize + len_s);
	while (len_d + i < dstsize - 1 && src[i])
	{
		dst[i + len_d] = src[i];
		i ++;
	}
	dst[i + len_d] = '\0';
	return (len_s + len_d);
}
