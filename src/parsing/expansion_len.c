/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:30:41 by ckarsent          #+#    #+#             */
/*   Updated: 2025/03/27 12:34:18 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var(char *token, int start)
{
	char	*var;
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (token[start + len] && (ft_isalnum(token[start + len])
			|| token[start + len] == '_'))
		len++;
	var = ft_calloc((len + 1), sizeof(char));
	if (!var)
		return (NULL);
	while (j < len)
		var[j++] = token[start++];
	return (var);
}

int	get_var_length(char *token, int *i)
{
	char	*var;
	char	*value;
	int		len;

	var = extract_var(token, *i + 1);
	if (!var)
		return (-1);
	value = getenv(var);
	if (value)
		len = ft_strlen(value);
	else
		len = 0;
	*i += ft_strlen(var);
	free(var);
	return (len);
}

int	process_len(char *token, int *i, int last_exit)
{
	int	len;

	len = 0;
	if (token[*i + 1] == '?')
	{
		len = ft_nbrlen(last_exit);
		(*i)++;
	}
	else if (ft_isalpha(token[*i + 1]) || token[*i + 1] == '_')
		len = get_var_length(token, i);
	else if (ft_isdigit(token[*i + 1]))
		(*i)++;
	return (len);
}

int	len_expansion(char *token, int last_exit)
{
	int		i;
	int		len;
	bool	quote[2];

	i = ((len = 0));
	quote[0] = ((quote[1] = false));
	while (token[i])
	{
		handle_quotes(token[i], &quote[0], &quote[1]);
		if (token[i] == '$' && !quote[0] && token[i + 1])
			len += process_len(token, &i, last_exit);
		else
			len++;
		i++;
	}
	return (len);
}
