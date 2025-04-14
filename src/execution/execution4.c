/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:19:24 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/14 02:51:08 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtin(char *cmd)
{
	int	len;

	if (!cmd)
		return (false);
	len = ft_strlen(cmd);
	if (!ft_strncmp("echo", cmd, len) || !ft_strncmp("cd", cmd, len)
	|| !ft_strncmp("pwd", cmd, len) || !ft_strncmp("export", cmd, len)
	|| !ft_strncmp("unset", cmd, len) || !ft_strncmp("env", cmd, len)
	|| !ft_strncmp("exit", cmd, len))
		return (true);
	return (false);
}

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

/* remplie le infile et outfile dans la struct si neccesair */
int	redirect(t_cmd *hcmd)
{
	int		fd;
	int 	i;

	i = 0;
	while (i < hcmd->size) // se deplace sans *next donc pas besoin de tmp
	{
		if (hcmd->types[i] == REDIR_IN && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
		{
			if (hcmd->infile)
				free(hcmd->infile);
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
				free(hcmd->outfile);
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
	}
	return (0);
}

// else if (hcmd->types[i] == CMD)
// path_cmd = get_cmd(hcmd->tokens[i], env);

char	**list_args(t_cmd *hcmd)
{
	char 	**args;
	bool 	flag_cmd;
	int		i;
	int		j;

	i = ((j = 0));
	flag_cmd = false;
	args = (char **)malloc(sizeof(char *) * (hcmd->size + 1));
	while (i < hcmd->size)
	{
		if ((hcmd->types[i] == REDIR_IN || hcmd->types[i] == HEREDOC) && !hcmd->fquotes[i] && (hcmd->size - i) > 1)
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

char *find_cmd(t_cmd *hcmd)
{
	int		i;

	i = 0;
	while (i < hcmd->size)
	{
		if (hcmd->types[i] == CMD)
			return (hcmd->tokens[i]);
		i++;
	}
	return (NULL);
}

int exec_builtin(char **args, char **env, t_env *envp)
{
	int	len;

	if (!args || !args[0])
		return (-1);
	len = ft_strlen(args[0]);
	if (!ft_strncmp(args[0], "pwd", len))
		builtin_pwd();
	else if (!ft_strncmp(args[0], "env", len))
		builtin_env(envp);
	else if (!ft_strncmp(args[0], "cd", len))
		builtin_cd(args, envp);
	else if (!ft_strncmp(args[0], "exit", len))
		builtin_exit(args, 23);
	else if (!ft_strncmp(args[0], "echo", len))
		builtin_echo(args);
	else if (!ft_strncmp(args[0], "export", len))
		builtin_export(envp, args);
	else if (!ft_strncmp(args[0], "unset", len))
		builtin_unset(&envp, args[1]);
	else
		return (-1);
	return (0);
}

int	supp_heredoc(int nbr)
{
	char *num;
	char *name;

	//printf("nbr :%d", nbr);
	while (nbr)
	{
		num = ft_itoa(nbr);
		if (!num)
			return (-1);
		name = ft_strjoin("tmp_", num);
		free(num);
		if (!name)
			return (-1);
		if (access(name, F_OK) == 0)
			unlink(name);
		free(name);
		nbr--;
	}
	return (0);
}

int execution(t_cmd **hcmd, int last_exit, char **env, t_env **envp)
{
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;
	int status;
	t_cmd *current = *hcmd;
	char **args;
	char *cmd;
	int fd;

	exec_heredoc(hcmd, last_exit);
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		if (check_builtin(find_cmd(current)) && !current->next && prev_fd == -1) //c'est chatgpt qui m'a donne cette condition pcq flemme de comprendre ton big code donc a verifier
		{
			if (redirect(current) == -1)
				exit(EXIT_FAILURE);
			if (current->infile)
			{
				fd = open(current->infile, O_RDONLY);
				if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
					perror("dup2 infile");
				close(fd);
			}
			if (current->outfile)
			{
				fd = openfile_output(current->outfile, current->is_append);
				if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
					perror("dup2 outfile");
				close(fd);
			}
			args = list_args(current);
			if (exec_builtin(args, env, *envp) == -1)
				perror("builtin execution failed");
			current = current->next;
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (prev_fd > -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			if (redirect(current) == -1)
				exit(EXIT_FAILURE);
			if (current->infile)
			{
				fd = open(current->infile, O_RDONLY);
				if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
					perror("dup2 infile");
				close(fd);
			}
			if (current->outfile)
			{
				fd = openfile_output(current->outfile, current->is_append);
				if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
					perror("dup2 outfile");
				close(fd);
			}
			args = list_args(current);
			cmd = get_cmd(args[0], env);
			execve(cmd, args, env);
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		current = current->next;
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
