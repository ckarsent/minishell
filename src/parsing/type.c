/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:31:57 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/27 00:08:11 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_type1(t_token *tmp, bool *flags)
{
	if (tmp->type == EXPANSE)
	{
		tmp->type = CMD;
		while (tmp && tmp->type == EXPANSE && tmp->token != NULL)
		{
			tmp->type = STR;
			tmp = tmp->next;
		}
		return (1);
	}
	else if ((arg(tmp->token) || (flags[1] && cd(tmp->token))) && flags[0])
	{
		tmp->type = ARG;
		return (1);
	}
	else if (tmp->token[0] == '|' || !ft_strcmp(tmp->token, "||"))
	{
		tmp->type = PIPE;
		flags[0] = false;
		return (1);
	}
	return (0);
}

int	process_type2(t_token *tmp, bool *flags)
{
	if (tmp->token[0] == '>' && ft_strlen(tmp->token) == 1 && tmp->fquote == 0)
	{
		tmp->type = REDIR_OUT;
		return (1);
	}
	else if (tmp->token[0] == '<' && ft_strlen(tmp->token) == 1
		&& tmp->fquote == 0)
	{
		tmp->type = REDIR_IN;
		flags[2] = true;
		return (1);
	}
	else if (!ft_strcmp(tmp->token, ">>") && tmp->fquote == 0)
	{
		tmp->type = APPEND;
		return (1);
	}
	else if (!ft_strcmp(tmp->token, "<<") && tmp->fquote == 0)
	{
		tmp->type = HEREDOC;
		flags[2] = true;
		return (1);
	}
	return (0);
}

int	process_type3(t_token *tmp, bool *flags)
{
	if (!flags[0] && !flags[2])
	{
		tmp->type = CMD;
		flags[0] = true;
		if (!ft_strcmp(tmp->token, "cd"))
			flags[1] = true;
		return (1);
	}
	else
	{
		tmp->type = STR;
		flags[2] = false;
		return (1);
	}
	return (0);
}

void	which_type(t_data *data)
{
	t_token	*tmp;
	bool	flags[3];

	tmp = data->tlst;
	flags[0] = ((flags[1] = (flags[2] = false)));
	while (tmp)
	{
		if (process_type1(tmp, flags) == 0)
		{
			if (process_type2(tmp, flags) == 0)
			{
				process_type3(tmp, flags);
			}
		}
		tmp = tmp->next;
	}
}
