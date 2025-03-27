/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:58:23 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/26 00:06:57 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **split, int n)
{
	while (n--)
		free(split[n]);
	free(split);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	find;
	int	count;

	i = 0;
	find = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && find == 0)
		{
			find = 1;
			count++;
		}
		else if (s[i] == c)
			find = 0;
		i++;
	}
	return (count);
}

static int	ft_2strlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*little_split(char const *s, int len)
{
	char	*st;
	int		i;

	i = 0;
	st = malloc(sizeof(char) * (len + 1));
	if (!st)
		return (NULL);
	while (i < len)
	{
		st[i] = s[i];
		i++;
	}
	st[i] = '\0';
	return (st);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;
	int		j;
	int		len;

	words = count_words(s, c);
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (*s && j < words)
	{
		if (*s != c)
		{
			len = ft_2strlen(s, c);
			str[j] = little_split(s, len);
			if (!str[j])
				return (ft_free(str, j), NULL);
			s += len;
			j++;
		}
		s++;
	}
	str[j] = (NULL);
	return (str);
}
