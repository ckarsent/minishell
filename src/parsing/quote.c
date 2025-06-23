/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:57:48 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/13 16:03:21 by ckarsent         ###   ########.fr       */
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

bool	flag_quote(char *token)
{
	bool	squote;
	bool	dquote;
	bool	ret;
	int		i;

	i = 0;
	squote = false;
	dquote = false;
	ret = true;
	while (token[i])
	{
		if (!handle_quotes(token[i], &squote, &dquote))
			ret = false;
		else
			ret = true;
		i++;
	}
	return (ret);
}
