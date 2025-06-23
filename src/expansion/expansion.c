/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:25:45 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/27 00:07:53 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_var(char *token, int *i, t_data *d)
{
	char	*exp;
	int		i_mem;
	int		j;
	int		len_exp;
	int		len_ret;

	len_exp = 0;
	j = 0;
	(*i)++;
	i_mem = (*i);
	while (token[(*i)] && (ft_isalnum(token[(*i)]) || token[(*i)] == '_'))
	{
		len_exp++;
		(*i)++;
	}
	exp = (char *)ft_calloc(len_exp + 1, sizeof(char));
	if (!exp)
		return (-1);
	while (j < len_exp)
		exp[j++] = token[i_mem++];
	len_ret = ft_strlen(ft_getenv(d->elst, exp));
	free(exp);
	return (len_ret);
}

int	len_expansion(char *t, t_data *d)
{
	int		v[2];
	bool	q[2];

	v[0] = ((v[1] = 0));
	q[0] = ((q[1] = false));
	while (t[v[0]])
	{
		handle_quotes(t[v[0]], &q[0], &q[1]);
		if (t[v[0]] == '$' && !q[0] && t[v[0] + 1] && (a(t[v[0] + 1])
				|| t[v[0] + 1] == '_'))
			v[1] += len_var(t, &v[0], d);
		else if (t[v[0]] == '$' && !q[0] && t[v[0] + 1] && t[v[0] + 1] == '?')
			v[1] += nbrlen(d->last_exit, &v[0]);
		else if (t[v[0]] == '$' && !q[0] && t[v[0] + 1] && a(t[v[0] + 1]))
		{
			v[1]--;
			v[0]++;
		}
		else
		{
			v[1]++;
			v[0]++;
		}
	}
	return (v[1]);
}

char	*var_expansion(char *token, int *i, t_data *d)
{
	char	*exp;
	char	*var_ret;
	int		i_mem;
	int		j;
	int		len_exp;

	len_exp = 0;
	j = 0;
	(*i)++;
	i_mem = (*i);
	while (token[(*i)] && (ft_isalnum(token[(*i)]) || token[(*i)] == '_'))
	{
		len_exp++;
		(*i)++;
	}
	exp = (char *)ft_calloc(len_exp + 1, sizeof(char));
	if (!exp)
		return (NULL);
	while (j < len_exp)
		exp[j++] = token[i_mem++];
	var_ret = ft_getenv(d->elst, exp);
	if (!var_ret)
		return (free(exp), ft_strdup("\0"));
	return (free(exp), ft_strdup(var_ret));
}

void	process_expansion(char *t, int *v, char **result, t_data *d)
{
	char	*tmp;
	int		idx_tmp;

	idx_tmp = 0;
	if (t[v[0]] == '$' && !v[2] && t[v[0] + 1]
		&& (a(t[v[0] + 1]) || t[v[0] + 1] == '_'))
	{
		tmp = var_expansion(t, &v[0], d);
		while (tmp[idx_tmp])
			(*result)[v[1]++] = tmp[idx_tmp++];
		free(tmp);
	}
	else if (t[v[0]] == '$' && !v[2] && t[v[0] + 1] && t[v[0] + 1] == '?')
	{
		tmp = ft_itoa(d->last_exit);
		while (tmp[idx_tmp])
			(*result)[v[1]++] = tmp[idx_tmp++];
		free(tmp);
		v[0] += 2;
	}
	else if (t[v[0]] == '$' && !v[2] && t[v[0] + 1]
		&& ft_isdigit(t[v[0] + 1]))
		v[0] += 2;
	else
		(*result)[v[1]++] = t[v[0]++];
}

char	*expansion(char *token, t_data *d)
{
	int		var[3];
	bool	quote[2];
	char	*result;

	var[0] = ((var[1] = 0));
	quote[0] = ((quote[1] = false));
	result = (char *)ft_calloc(len_expansion(token, d) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (token[var[0]])
	{
		handle_quotes(token[var[0]], &quote[0], &quote[1]);
		var[2] = (int)quote[0];
		process_expansion(token, var, &result, d);
	}
	return (free(token), result);
}
