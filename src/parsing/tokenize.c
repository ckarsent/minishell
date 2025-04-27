/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:29:01 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/27 13:28:36 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_operator(char *line, int *i, bool *fheredoc, t_data *d)
{
	char	*process;
	bool	fquote;

	process = extract_operator(line, i);
	fquote = flag_quote(process);
	if (ft_strcmp(process, "<<") == 0)
		*fheredoc = true;
	append_node_token(&d->tlst, delete_quote(process), -1, fquote);
}

void	handle_word(char *line, int *i, bool *fheredoc, t_data *d)
{
	char	*process;
	char	**split;
	bool	fquote;
	int		j;

	process = extract_word(line, i);
	if (!(*fheredoc))
		process = expansion(process, d);
	fquote = flag_quote(process);
	if (!fquote && ft_strchr(process, ' '))
	{
		split = ft_split(process, ' ');
		if (!split)
			return ;
		j = -1;
		while (split[++j])
			append_node_token(&d->tlst, ft_strdup(split[j]), EXPANSE, false);
		free_split(split);
		free(process);
	}
	else
		append_node_token(&d->tlst, delete_quote(process), -1, fquote);
	*fheredoc = false;
}

char	*handle_token(char *line, bool *fheredoc, t_data *d)
{
	int	i;

	i = 0;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		handle_operator(line, &i, fheredoc, d);
	else
		handle_word(line, &i, fheredoc, d);
	return (line + i);
}

int	tokenize(char *line, t_data *d)
{
	bool	fheredoc;

	fheredoc = false;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (!(*line))
			break ;
		line = handle_token(line, &fheredoc, d);
	}
	return (0);
}
