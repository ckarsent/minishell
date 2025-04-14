/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:25:45 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/14 02:58:04 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_var(char *token, int *i)
{
	char	*exp;
	int		i_mem;
	int		j;
	int		len_exp;
	int		len_ret;

	len_exp = 0;
	j = 0;
	(*i)++; //passer le $
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
	len_ret = ft_strlen(getenv(exp));
	free(exp);
	return (len_ret); // LEN de la variable expanser
}

int	len_expansion(char *t, int last_exit)
{
	int		v[2];
	bool	q[2];

	v[0] = ((v[1] = 0));
	q[0] = ((q[1] = false));
	while (t[v[0]])
	{
		handle_quotes(t[v[0]], &q[0], &q[1]);
		if (t[v[0]] == '$' && !q[0] && t[v[0] + 1] && (ft_isalpha(t[v[0] + 1])
				|| t[v[0] + 1] == '_'))
			v[1] += len_var(t, &v[0]);
		else if (t[v[0]] == '$' && !q[0] && t[v[0] + 1] && t[v[0] + 1] == '?')
			v[1] += nbrlen(last_exit, &v[0]); // nbrlen avance l'index i
		else if (t[v[0]] == '$' && !q[0] && t[v[0] + 1] && ft_isdigit(t[v[0] + 1]))
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

char	*var_expansion(char *token, int *i)
{
	char	*exp;
	char	*var_ret;
	int		i_mem;
	int		j;
	int		len_exp;

	len_exp = 0;
	j = 0;
	(*i)++; //passer le $
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
	var_ret = getenv(exp);
	if (!var_ret)
		return (free(exp), ft_strdup("\0"));
	return (free(exp), ft_strdup(var_ret)); // VARIABLE EXPENSER
}


void	process_expansion(char *token, int *var, char **result, int last_exit)
{
	char	*tmp;
	int		idx_tmp;

	idx_tmp = 0;
	if (token[var[0]] == '$' && !var[2] && token[var[0] + 1] && (ft_isalpha(token[var[0] + 1]) || token[var[0] + 1] == '_'))
	{
		tmp = var_expansion(token, &var[0]);
		while (tmp[idx_tmp])
			(*result)[var[1]++] = tmp[idx_tmp++];
		free(tmp);
	}
	else if (token[var[0]] == '$' && !var[2] && token[var[0] + 1] && token[var[0] + 1] == '?')
	{
		tmp = ft_itoa(last_exit);
		while (tmp[idx_tmp])
			(*result)[var[1]++] = tmp[idx_tmp++];
		free(tmp);
		var[0]+=2;
	}
	else if (token[var[0]] == '$' && !var[2] && token[var[0] + 1] && ft_isdigit(token[var[0] + 1]))
		var[0]+=2;
	else
		(*result)[var[1]++] = token[var[0]++];
}

char	*expansion(char *token, int last_exit)
{
	int		var[3]; /*!!!! i j quote[0] !!!!*/
	bool	quote[2];
	char	*result;

	var[0] = ((var[1] = 0));
	quote[0] = ((quote[1] = false));
	result = (char *)ft_calloc(len_expansion(token, last_exit) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (token[var[0]])
	{
		handle_quotes(token[var[0]], &quote[0], &quote[1]);
		var[2] = (int)quote[0];
		process_expansion(token, var, &result, last_exit);
	}
	return (free(token), result);
}


/*version non decouper*/
// char	*expansion(char *token, int last_exit)
// {
// 	int		i;
// 	int		j;
// 	bool	quote[2];
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	quote[0] = ((quote[1] = false));
// 	int t = len_expansion(token, last_exit);
// 	printf("\n\nLEN FINAL : %d\n\n\n", t);
// 	result = (char *)ft_calloc(t + 1, sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	while (token[i])
// 	{
// 		handle_quotes(token[i], &quote[0], &quote[1]);
// 		if (token[i] == '$' && !quote[0] && token[i + 1] && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
// 		{
// 			char *var = var_expansion(token, &i);
// 			int l = 0;
// 			while (var[l])
// 				result[j++] = var[l++];
// 			free(var);
// 		}
// 		else if (token[i] == '$' && !quote[0] && token[i + 1] && token[i + 1] == '?')
// 		{
// 			char *vart = ft_itoa(last_exit);
// 			int		m = 0;
// 			while (vart[m])
// 				result[j++] = vart[m++];
// 			free(vart);
// 			i+=2;
// 		}
// 		else if (token[i] == '$' && !quote[0] && token[i + 1] && ft_isdigit(token[i + 1]))
// 			i+=2;
// 		else
// 			result[j++] = token[i++];
// 	}
// 	return (free(token), result);
// }
