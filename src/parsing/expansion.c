/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:25:45 by ckarsent          #+#    #+#             */
/*   Updated: 2025/03/27 12:34:08 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_var_value(int *j, char *var, char **result)
{
	char	*value;

	value = getenv(var);
	if (!value)
		value = "";
	while (*value)
		(*result)[(*j)++] = *(value++);
}

void	handle_exit_status(int *j, char **result, int last_exit)
{
	int		k;
	char	*var;

	var = ft_itoa(last_exit);
	if (!var)
		return ;
	k = 0;
	while (var[k])
		(*result)[(*j)++] = var[k++];
	free(var);
}

void	process_variable(char *token, int *var, char **result, int last_exit)
{
	char	*varr;

	if (token[var[0] + 1] == '?')
	{
		handle_exit_status(&var[1], result, last_exit);
		(var[0])++;
	}
	else if (ft_isalpha(token[var[0] + 1]) || token[var[0] + 1] == '_')
	{
		varr = extract_var(token, var[0] + 1);
		if (varr)
		{
			append_var_value(&var[1], varr, result);
			var[0] += ft_strlen(varr);
			free(varr);
		}
	}
	else if (ft_isdigit(token[var[0] + 1]))
		var[0]++;
	else
		(*result)[(var[1])++] = '$';
}

char	*expansion(char *token, int last_exit)
{
	int		var[2];
	bool	quote[2];
	char	*result;

	var[0] = 0;
	var[1] = 0;
	quote[0] = ((quote[1] = false));
	result = ft_calloc(len_expansion(token, last_exit) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (token[var[0]])
	{
		handle_quotes(token[var[0]], &quote[0], &quote[1]);
		if (token[var[0]] == '$' && !quote[0] && token[var[0] + 1])
			process_variable(token, var, &result, last_exit);
		else
			result[var[1]++] = token[var[0]];
		var[0]++;
	}
	return (free(token), result);
}
