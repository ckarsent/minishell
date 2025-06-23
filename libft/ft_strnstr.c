/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 03:27:54 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/26 15:11:41 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	len_find;

	len_find = ft_strlen(find);
	if (len_find == 0)
		return ((char *)str);
	i = 0;
	while (i < n && str[i])
	{
		if (ft_strncmp(&str[i], find, len_find) == 0)
		{
			if (i + len_find > n)
				return (NULL);
			return ((char *) &str[i]);
		}
		i++;
	}
	return (NULL);
}
