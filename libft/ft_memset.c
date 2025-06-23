/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:54:37 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/15 01:07:13 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t count)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *) dst;
	i = 0;
	while (i < count)
		d[i++] = (unsigned char)c;
	return (dst);
}
