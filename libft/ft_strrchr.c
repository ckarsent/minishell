/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 02:34:33 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/15 02:48:06 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	cc;
	size_t			len;

	cc = (unsigned char) c;
	len = ft_strlen(str);
	while (*str != '\0')
		str++;
	while (len > 0 && cc != *str)
	{
		str--;
		len--;
	}
	if (cc == *str)
		return ((char *) str);
	return (0);
}
