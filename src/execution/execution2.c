/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:19:24 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/11 01:52:41 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	openfile_output(char *file, bool append)
{
	int	fd;

	if (append == true)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);	
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error open");
	}
	return (fd);
}

int	redirect(t_cmd *hcmd)
{
	char 	*path_cmd = NULL;
	int		fd = -1;
	int 	i = 0;

	while (i < hcmd->size)
	{
		if (hcmd->types[i] == REDIR_IN && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
		{
			if (hcmd->infile)
			{
				free(hcmd->infile);
				hcmd->infile = NULL;
			}
			hcmd->infile = ft_strdup(hcmd->tokens[i + 1]);
			fd = open(hcmd->infile, O_RDONLY, 0644);
			if (fd < 0)
				return (-1);
			close(fd);
			i++;
		}
		else if ((hcmd->types[i] == REDIR_OUT || hcmd->types[i] == APPEND) && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
		{
			if (hcmd->outfile)
			{
				free(hcmd->outfile);
				hcmd->outfile = NULL;
			}
			hcmd->outfile = ft_strdup(hcmd->tokens[i + 1]);
			if (hcmd->types[i] == APPEND)
				hcmd->is_append = true;
			else
				hcmd->is_append = false;
			fd = openfile_output(hcmd->tokens[i + 1], hcmd->is_append);
			if (fd < 0)
				return (-1);
			close(fd);
			i++;
		}
		i++;
		//printf("iter[%d] in [%d] out [%d]\n",i,hcmd->fd_infile,hcmd->fd_outfile);
	}
	return (0);
}

// else if (hcmd->types[i] == CMD)
// path_cmd = get_cmd(hcmd->tokens[i], env);

char	**list_args(t_cmd *hcmd)
{
	char 	**args;
	int		i;
	int		j;
	bool flag_cmd;

	i = 0;
	j = 0;
	flag_cmd = false;
	args = (char **)malloc(sizeof(char *) * (hcmd->size + 1));
	while (i < hcmd->size)
	{
		if (hcmd->types[i] == REDIR_IN && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
			i++;
		else if ((hcmd->types[i] == REDIR_OUT || hcmd->types[i] == APPEND) && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
			i++;
		else if (hcmd->types[i] == CMD)
		{
			flag_cmd = true;
			args[j++] = ft_strdup(hcmd->tokens[i]);
		}
		else if (flag_cmd == true)
			args[j++] = ft_strdup(hcmd->tokens[i]);
		i++;
	}
	args[j] = NULL;
	return (args);		
}

void run_command(char *cmd, char **args, char **env, t_cmd *hcmd)
{
	pid_t pid = fork();
	int	fd = -1;

	if (pid == 0) // enfant
	{
		if (redirect(&hcmd[0]) == -1)
			exit(1);
		if (hcmd[0].infile)
		{
			fd = open(hcmd[0].infile, O_RDONLY); 
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2 failed");
			}
			close(fd);
		}
		if (hcmd[0].outfile)
		{
			fd = openfile_output(hcmd[0].outfile, hcmd[0].is_append);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 failed");
			}
			close(fd);
		}
		if (execve(cmd, args, env) == -1)
		{
			perror("Error execve");
			exit(1);
		}
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0); // parent attend
	}
	else
	{
		perror("Error fork"); // erreur
	}
}


int		execution(t_cmd **hcmd, int last_exit, char **env)
{
	char	*path_cmd;
	char	**args;
	int		i;

	args = list_args(hcmd[0]);
	path_cmd = get_cmd(args[0], env);
	
	printf("cmd [%s]\n", path_cmd);
	i = 0;
	while (args[i])
	{
		printf("i[%d] args[%s]\n", i, args[i]);
		i++;
	}
	printf("i[%d] args[%s]\n", i, args[i]);
	printf("\n----------------------\n\n");
	run_command(path_cmd, args, env, hcmd[0]);
	printf("\n\nOK\n");
	return (0);
	
}