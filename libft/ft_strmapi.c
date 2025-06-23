/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:45:52 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/26 00:05:41 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*mapi;

	i = 0;
	len = ft_strlen(s);
	mapi = (char *) malloc((len + 1) * sizeof(char));
	if (mapi != NULL)
	{
		while (*s)
		{
			mapi[i] = f(i,*s);
			i++;
			s++;
		}
		mapi[i] = '\0';
	}
	return (mapi);
}
