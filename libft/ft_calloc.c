/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 04:20:59 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/22 04:08:13 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	if ((n * (size)) <= 0)
		return (NULL);
	p = malloc(n * (size));
	if (!p)
		return (NULL);
	ft_bzero(p, n * size);
	return (p);
}
