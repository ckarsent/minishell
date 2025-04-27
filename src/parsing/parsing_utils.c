/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:44:09 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/24 03:12:00 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbrlen(int nb, int *idx)
{
	int			count;
	long int	i;

	count = 1;
	i = nb;
	if (nb < 0)
	{
		i *= (-1);
		count++;
	}
	while (i >= 10)
	{
		i /= 10;
		count++;
	}
	(*idx) += 2;
	return (count);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && i < n)
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (0);
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	a(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

char	*extract_operator(char *line, int *i)
{
	int	tmp;

	tmp = (*i);
	if (line[tmp + 1])
	{
		if (line[tmp] == '>' && line[tmp + 1] == '>')
		{
			(*i) += 2;
			return (ft_strdup(">>"));
		}
		if (line[tmp] == '<' && line[tmp + 1] == '<')
		{
			(*i) += 2;
			return (ft_strdup("<<"));
		}
	}
	(*i)++;
	if (line[tmp] == '|')
		return (ft_strdup("|"));
	if (line[tmp] == '<')
		return (ft_strdup("<"));
	if (line[tmp] == '>')
		return (ft_strdup(">"));
	(*i)--;
	return (NULL);
}

char	*extract_word(char *line, int *i)
{
	bool	squote;
	bool	dquote;
	int		start;

	start = (*i);
	squote = false;
	dquote = false;
	while (line[(*i)])
	{
		handle_quotes(line[(*i)], &squote, &dquote);
		(*i)++;
		if (!squote && !dquote && ft_strchr("|<> ", line[(*i)]))
			break ;
	}
	return (ft_substr(line, start, (*i) - start));
}
