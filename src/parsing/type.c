/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:31:57 by ckarsent          #+#    #+#             */
/*   Updated: 2025/04/12 20:28:26 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
	*/

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
/*
int	check_builtins(char *token, char *next)
{
	if (ft_strncmp(token, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(token, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(token, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(token, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(token, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "echo", 4) == 0 && (!(ft_strncmp(next, "-n", 2) == 0) || !next))
		return (1);
	else if (ft_strncmp(token, "env", 3) == 0)
		return (1);
	return (0);
}
	*/

bool	check_arg_cd(char *arg)
{
	if (!ft_strncmp(arg, "..", ft_strlen(arg)))
		return (true);
	while (*arg)
	{
		if (ft_strncmp(arg, "../", 3))
			return (false);
		arg+=3;
		if (ft_strlen(arg) == 2 && !ft_strncmp(arg, "..", ft_strlen(arg)))
			arg+=2;
	}
	return (true);	
}
	
void	which_type(t_token **htoken)
{
	t_token	*tmp;
	t_token	*prec;
	bool	cmd;
	bool	flag_cd;
	bool	flag_redir;

	tmp = *htoken;
	cmd = false;
	flag_redir = false;
	while (tmp)
	{

		if ((check_arg(tmp->token) || (flag_cd == true && check_arg_cd(tmp->token))) && cmd == true)//&& !check_builtins(prec->token, tmp->token))
			tmp->type = ARG;
		else if ((tmp->token[0] == '|' || !ft_strncmp(tmp->token, "||", 2)) && ft_strlen(tmp->token) < 3)
		{
			tmp->type = PIPE;
			cmd = false;
		}
		else if (tmp->token[0] == '>' && ft_strlen(tmp->token) == 1 && tmp->fquote == 0)
			tmp->type = REDIR_OUT;
		else if (tmp->token[0] == '<' && ft_strlen(tmp->token) == 1 && tmp->fquote == 0)
		{
			tmp->type = REDIR_IN;
			flag_redir = true;
		}
		else if (!ft_strncmp(tmp->token, ">>", 2) && ft_strlen(tmp->token) == 2 && tmp->fquote == 0)
			tmp->type = APPEND;
		else if (!ft_strncmp(tmp->token, "<<", 2) && ft_strlen(tmp->token) == 2 && tmp->fquote == 0)
		{
			tmp->type = HEREDOC;
			flag_redir = true;
		}
		//else if ((flag && (check_cmd(tmp->token) || check_builtins(tmp->token, NULL))) 
		// || (cmd == false && (check_cmd(tmp->token) || check_builtins(tmp->token, NULL)) && ft_strlen(tmp->token) > 0 && (prec == NULL || prec->type == PIPE)))
		else if (cmd == false && flag_redir == false) 
		{
			tmp->type = CMD;
			cmd = true;
			if (ft_strncmp(tmp->token, "cd", ft_strlen(tmp->token)) == 0)
				flag_cd = true;
			//flag = false;
		}
		else //if (tmp->type == -1)
		{
			tmp->type = STR;
			flag_redir = false;
			//if (prec == NULL || prec->type == REDIR_IN || prec->type == HEREDOC)
			//	flag = true;
		}
		//prec = tmp;
		tmp = tmp->next;
	}
}

// int	check_cmd(char *cmd)
// {
// 	char	**tmp_paths;
// 	char	**paths;
// 	char	*tmp;

// 	if (access(cmd, F_OK | X_OK) == 0)
// 		return (1);
// 	cmd = ft_strjoin("/", cmd);
// 	if (!cmd)
// 		return (-1);
// 	paths = ft_split(getenv("PATH"), ':');
// 	if (!paths)
// 		return (free(cmd), -1);
// 	tmp_paths = paths;
// 	while (*tmp_paths)
// 	{
// 		tmp = ft_strjoin(*tmp_paths, cmd);
// 		if (!tmp)
// 			return (free_split(paths), free(cmd), -1);
// 		if (access(tmp, F_OK | X_OK) == 0)
// 			return (free_split(paths), free(tmp), free(cmd), 1);
// 		free(tmp);
// 		tmp_paths++;
// 	}
// 	return (free_split(paths), free(cmd), 0);
// }

// int	check_arg(char *arg)
// {
// 	int	i;

// 	i = 1;
// 	if (arg[0] != '-')
// 		return (0);
// 	if (!arg[1])
// 		return (0);
// 	while (arg[i])
// 		if (!ft_isalpha(arg[i++]))
// 			return (0);
// 	return (1);
// }

// int	check_bultins(char *token)
// {
// 	if (ft_strncmp(token, "cd", 2) == 0)
// 		return (1);
// 	else if (ft_strncmp(token, "export", 6) == 0)
// 		return (1);
// 	else if (ft_strncmp(token, "unset", 5) == 0)
// 		return (1);
// 	else if (ft_strncmp(token, "exit", 4) == 0)
// 		return (1);
// 	return (0);
// }


// void	which_type(t_token **htoken)
// {
// 	t_token	*tmp;
// 	bool	cmd;

// 	cmd = false;
// 	tmp = *htoken;
// 	while (tmp)
// 	{
// 		if (cmd == true)
// 		{
// 			if (check_arg(tmp->token))
// 				tmp->type = ARG;
// 			else
// 				cmd = false;
// 		}
// 		if ((tmp->token[0] == '|' || !ft_strncmp(tmp->token, "||", 2)) && ft_strlen(tmp->token) < 3)
// 			tmp->type = PIPE;
// 		else if (tmp->token[0] == '>' && ft_strlen(tmp->token) == 1)
// 			tmp->type = REDIR_OUT;
// 		else if (tmp->token[0] == '<' && ft_strlen(tmp->token) == 1)
// 			tmp->type = REDIR_IN;
// 		else if (!ft_strncmp(tmp->token, ">>", 2) && ft_strlen(tmp->token) == 2)
// 			tmp->type = APPEND;
// 		else if (!ft_strncmp(tmp->token, "<<", 2) && ft_strlen(tmp->token) == 2)
// 			tmp->type = HEREDOC;
// 		else if ((check_cmd(tmp->token) || check_bultins(tmp->token)) && ft_strlen(tmp->token) > 0)
// 		{
// 			tmp->type = CMD;
// 			cmd = true;
// 		}
// 		else if (cmd == false && tmp->type == -1)
// 			tmp->type = STR;
// 		tmp = tmp->next;
// 	}
// }
