/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:29:01 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/27 12:33:41 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*handle_token(char *line, t_token **head, bool *flag, int last_exit)
{
	char	*process;
	int		i;

	i = 0;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		process = delete_quote(extract_operator(line, &i));
		append_node(head, process, -1);
		if (ft_strncmp(process, "<<", 2) == 0)
			*flag = true;
	}
	else
	{
		process = extract_word(line, &i);
		if (!(*flag))
			process = expansion(process, last_exit);
		append_node(head, delete_quote(process), -1);
		*flag = false;
	}
	return (line + i);
}

int	tokenize(char *line, t_token **head)
{
	bool	flag;
	int		last_exit;

	flag = false;
	last_exit = 2; //faudra appeler la fonction qui parcours la structure pour trouver le last exit
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (!(*line))
			break ;
		line = handle_token(line, head, &flag, last_exit);
	}
	return (0);
}

// int	tokenize(char *line, t_token **head)
// {
// 	char	*process;
// 	bool	flag;
// 	int		i;

// 	i = 0;
// 	flag = false;
// 	while (line[i])
// 	{
// 		while (line[i] && ft_isspace(line[i]))
// 			i++;
// 		if (!line[i])
// 			break ;
// 		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
// 		{
// 			process = delete_quote(extract_operator(line, &i));
// 			append_node(head, process, -1);
// 			if (ft_strncmp(process, "<<", 2) == 0)
// 				flag = true;
// 		}
// 		else if (line[i] == '\'' || line[i] == '"' || line[i] != ' ')
// 		{
// 			process = extract_word(line, &i);
// 			if (!flag)
// 				process = expansion(process);
// 			append_node(head, delete_quote(process), -1);
// 			flag = false;
// 		}
// 	}
// 	return (0);
// }
