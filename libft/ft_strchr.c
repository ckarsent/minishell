/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:36:29 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/28 14:54:16 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	cc;

	cc = (unsigned char) c;
	while (*str != '\0' && cc != *str)
		str++;
	if (cc == *str)
		return ((char *) str);
	return (0);
}
