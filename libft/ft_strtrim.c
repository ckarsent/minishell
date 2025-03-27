/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:50:17 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/28 15:30:59 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		right;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	right = ft_strlen(s1);
	while (s1 && ft_strchr(set, s1[right]))
		right--;
	return (ft_substr(s1, 0, right + 1));
}
