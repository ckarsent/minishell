/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:26:18 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/16 17:34:00 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t n)
{
	unsigned char	cc;
	unsigned char	*b;

	cc = (unsigned char) c;
	b = (unsigned char *) buf;
	while (n --)
	{
		if (cc == *b)
			return ((void *) b);
		b ++;
	}
	return (0);
}
