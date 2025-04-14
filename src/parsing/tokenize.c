/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:29:01 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/07 12:00:46 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*handle_token(char *line, t_token **head, bool *fheredoc, int last_exit)
{
	bool	fquote;
	char	*process;
	char	*tmp;
	int		i;

	i = 0;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		process = extract_operator(line, &i);
		fquote = flag_quote(process);
		if (ft_strncmp(process, "<<", 2) == 0)
			*fheredoc = true;
		append_node_token(head, delete_quote(process), -1, fquote);
	}
	else
	{
		process = extract_word(line, &i);
		if (!(*fheredoc))
			process = expansion(process, last_exit);
		fquote = flag_quote(process);
		append_node_token(head, delete_quote(process), -1, fquote);
		*fheredoc = false;
	}
	return (line + i);
}

int	tokenize(char *line, t_token **htoken, int last_exit)
{
	bool	fheredoc;

	fheredoc = false;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (!(*line))
			break ;
		line = handle_token(line, htoken, &fheredoc, last_exit);
	}
	//printf("OK\n");
	return (0);
}


/*
char	*handle_token(char *line, t_token **head, bool *fheredoc, int last_exit)
{
	bool	fquote;
	char	*process;
	int		i;

	i = 0;
	fquote = 1;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		process = delete_quote(extract_operator(line, &i));
		append_node_token(head, process, -1);
		if (ft_strncmp(process, "<<", 2) == 0)
			*fheredoc = true;
	}
	else
	{
		process = extract_word(line, &i);
		//printf("process : %s\n", process);
		if (!(*fheredoc))
			process = expansion(process, last_exit);
		append_node_token(head, delete_quote(process), -1);
		*fheredoc = false;
	}
	return (line + i);
}*/

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
