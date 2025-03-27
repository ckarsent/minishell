/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:44:09 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/24 17:26:50 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line)
{
	bool	squote;
	bool	dquote;
	int		i;

	i = 0;
	squote = false;
	dquote = false;
	while (line[i])
		handle_quotes(line[i++], &squote, &dquote);
	if (!squote && !dquote)
		return (0);
	return (-1);
}

/* retourne true si on est renter dans une des conditions */
bool	handle_quotes(char c, bool *squote, bool *dquote)
{
	if (c == '\'' && !(*dquote))
	{
		*squote = !(*squote);
		return (true);
	}
	if (c == '"' && !(*squote))
	{
		*dquote = !(*dquote);
		return (true);
	}
	return (false);
}

int	len_quote(char *token)
{
	bool	squote;
	bool	dquote;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(token);
	squote = false;
	dquote = false;
	while (token[i])
	{
		if (token[i] == '\'' && !dquote)
			squote ^= true;
		if (token[i] == '"' && !squote)
		{
			dquote ^= true;
			len--;
		}
		i++;
	}
	return (len);
}

char	*delete_quote(char *token)
{
	bool	squote;
	bool	dquote;
	char	*delete;
	int		i;
	int		j;

	i = 0;
	j = 0;
	squote = false;
	dquote = false;
	delete = (char *)malloc((len_quote(token) + 1) * sizeof(char));
	if (!delete)
		return (free(token), NULL);
	while (token[i])
	{
		if (!handle_quotes(token[i], &squote, &dquote))
			delete[j++] = token[i];
		i++;
	}
	delete[j] = '\0';
	return (free(token), delete);
}

int	ft_nbrlen(int nb)
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
	return (count);
}
