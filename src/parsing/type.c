/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:31:57 by ckarsent          #+#    #+#             */
/*   Updated: 2025/03/26 00:09:12 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char *cmd)
{
	char	**tmp_paths;
	char	**paths;
	char	*tmp;

	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (-1);
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (free(cmd), -1);
	tmp_paths = paths;
	while (*tmp_paths)
	{
		tmp = ft_strjoin(*tmp_paths, cmd);
		if (!tmp)
			return (free_split(paths), free(cmd), -1);
		if (access(tmp, F_OK | X_OK) == 0)
			return (free_split(paths), free(tmp), free(cmd), 1);
		free(tmp);
		tmp_paths++;
	}
	return (free_split(paths), free(cmd), 0);
}

int	check_arg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (!arg[1])
		return (0);
	while (arg[i])
		if (!ft_isalpha(arg[i++]))
			return (0);
	return (1);
}

int	check_bultins(char *token)
{
	if (ft_strncmp(token, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(token, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(token, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(token, "exit", 4) == 0)
		return (1);
	return (0);
}

void	which_type(t_token **head)
{
	t_token	*tmp;
	bool	cmd;

	cmd = false;
	tmp = *head;
	while (tmp)
	{
		if (cmd == true)
		{
			if (check_arg(tmp->token))
				tmp->type = ARG;
			else
				cmd = false;
		}
		if ((tmp->token[0] == '|' || !ft_strncmp(tmp->token, "||", 2)) && ft_strlen(tmp->token) < 3)
			tmp->type = PIPE;
		else if (tmp->token[0] == '>' && ft_strlen(tmp->token) == 1)
			tmp->type = REDIR_OUT;
		else if (tmp->token[0] == '<' && ft_strlen(tmp->token) == 1)
			tmp->type = REDIR_IN;
		else if (!ft_strncmp(tmp->token, ">>", 2) && ft_strlen(tmp->token) == 2)
			tmp->type = APPEND;
		else if (!ft_strncmp(tmp->token, "<<", 2) && ft_strlen(tmp->token) == 2)
			tmp->type = HEREDOC;
		else if ((check_cmd(tmp->token) || check_bultins(tmp->token)) && ft_strlen(tmp->token) > 0)
		{
			tmp->type = CMD;
			cmd = true;
		}
		else if (cmd == false && tmp->type == -1)
			tmp->type = STR;
		tmp = tmp->next;
	}
}
