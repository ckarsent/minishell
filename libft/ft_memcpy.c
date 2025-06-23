/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:17:47 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/19 19:00:32 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (s == 0 && d == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i ++;
	}
	return (dst);
}
