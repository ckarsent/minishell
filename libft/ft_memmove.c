/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:12:35 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/20 17:41:10 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (s == 0 && d == 0)
		return (NULL);
	if (d > s)
		while (n--)
			d[n] = s[n];
	else
		return (ft_memcpy(d, s, n));
	return ((void *) d);
}
