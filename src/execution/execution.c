/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:00:14 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/11 00:57:56 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	open_file(char *file, bool trunc)
// {
// 	int	fd;

// 	if (trunc)
// 		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else
// 		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd < 0)
// 	{
// 		perror("Error");
// 	}
// 	return (fd);
// }

// char	*redirect(t_cmd *hcmd, char **env)
// {
// 	char *path_cmd = NULL;
// 	int i = 0;

// 	while (i < hcmd->size)
// 	{
// 		if (hcmd->types[i] == REDIR_IN && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
// 		{
// 			if (hcmd->fd_infile > -1)
// 			{
// 				free(hcmd->infile);
// 				hcmd->infile = NULL;
// 				//hcmd->fd_infile = -1;
// 			}
// 			hcmd->fd_infile = open_file(hcmd->tokens[i + 1], true);
// 			hcmd->infile = ft_strdup(hcmd->tokens[i + 1]);
// 			close(hcmd->fd_infile);
// 			i++;
// 		}
// 		else if (hcmd->types[i] == REDIR_OUT && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
// 		{
// 			if (hcmd->fd_outfile > -1)
// 			{
// 				free(hcmd->outfile);
// 				hcmd->outfile = NULL;
// 			}
// 			hcmd->fd_outfile = open_file(hcmd->tokens[i + 1], true);
// 			hcmd->outfile = ft_strdup(hcmd->tokens[i + 1]);
// 			close(hcmd->fd_outfile);
// 			i++;
// 		}
// 		else if (hcmd->types[i] == APPEND && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
// 		{
// 			if (hcmd->fd_outfile > -1)
// 			{
// 				free(hcmd->outfile);
// 				hcmd->outfile = NULL;
// 			}
// 			hcmd->fd_outfile = open_file(hcmd->tokens[i + 1], false);
// 			hcmd->outfile = ft_strdup(hcmd->tokens[i + 1]);
// 			close(hcmd->fd_outfile);
// 			i++;
// 		}
// 		else if (hcmd->types[i] == CMD)
// 			path_cmd = get_cmd(hcmd->tokens[i], env);
// 		i++;
// 		printf("iter[%d] in [%d] out [%d]\n",i,hcmd->fd_infile,hcmd->fd_outfile);
// 	}
// 	return (path_cmd);
// }

// char	**list_args(t_cmd *hcmd)
// {
// 	char 	**args;
// 	int		i;
// 	int		j;
// 	bool flag_cmd;

// 	i = 0;
// 	j = 0;
// 	flag_cmd = false;
// 	args = (char **)malloc(sizeof(char *) * (hcmd->size + 1));
// 	while (i < hcmd->size)
// 	{
// 		if (hcmd->types[i] == REDIR_IN && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
// 			i++;
// 		else if ((hcmd->types[i] == REDIR_OUT || hcmd->types[i] == APPEND) && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
// 			i++;
// 		else if (hcmd->types[i] == CMD)
// 		{
// 			flag_cmd = true;
// 			args[j++] = ft_strdup(hcmd->tokens[i]);
// 		}
// 		else if (flag_cmd == true)
// 			args[j++] = ft_strdup(hcmd->tokens[i]);
// 		i++;
// 	}
// 	args[j] = NULL;
// 	return (args);		
// }

// void run_command(char *cmd, char **args, char **env, t_cmd **hcmd)
// {
// 	pid_t pid = fork();
// 	int fd = -1;
// 	if (pid == 0)
// 	{
// 		if (hcmd[0]->infile)
// 		{
// 			fd = open_file(hcmd[0]->infile, true);
// 			if (dup2(fd, STDIN_FILENO) == -1)
// 			{
// 				perror("dup2 failed");
// 			}
// 			close(fd);
// 		}
// 		if (hcmd[0]->outfile)
// 		{
// 			fd = open_file(hcmd[0]->outfile, true);
// 			//printf("fd outfile : %d\n", hcmd[0]->fd_outfile);
// 			dup2(fd, STDOUT_FILENO);
// 			//printf("av close\n");
// 			close(fd);
// 			// printf("fin du if\n");
// 		}
// 		// enfant → exécute la commande
// 		if (execve(cmd, args, env) == -1)
// 		{
// 			perror("Error execve");
// 			exit(1);
// 		}
// 	}
// 	else if (pid > 0)
// 	{
// 		int status;
// 		waitpid(pid, &status, 0); // parent attend
// 	}
// 	else
// 	{
// 		perror("Error fork"); // erreur
// 	}
// }

// int		execution(t_cmd **hcmd, int last_exit, char **env)
// {
// 	char	*path_cmd;
// 	char	**args;
// 	int		i;

// 	//exec_heredoc(hcmd, last_exit);
// 	path_cmd = redirect(hcmd[0], env);
// 	args = list_args(hcmd[0]);
// 	printf("cmd [%s]\n", path_cmd);
// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("i[%d] args[%s]\n", i, args[i]);
// 		i++;
// 	}
// 	printf("i[%d] args[%s]\n", i, args[i]);
// 	printf("\n----------------------\n\n");
// 	run_command(path_cmd, args, env, &hcmd[0]);
// 	printf("\n\nOK\n");
// 	return (0);
	
// }