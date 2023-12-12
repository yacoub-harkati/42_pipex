/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:21:43 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/12 21:21:43 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

void write_here_doc(int in_fd, char *eof)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free(line);
			break;
		}
		ft_fprintf(in_fd, "%s\n", line);
		free(line);
	}
}

void run_cmd(char **env, t_pipex *pipe_d)
{
	execve(pipe_d->cmd_paths[pipe_d->cmd_iter], pipe_d->cmd_args[pipe_d->cmd_iter], env);
	perror("Error: while executing command");
	ft_cleanup_pipe(pipe_d);
	exit(EXIT_FAILURE);
}

void child_exec(t_pipex *pipe_d, char **env)
{
	if (pipe_d->cmd_iter == pipe_d->cmd_count - 1)
	{
		if (dup2(pipe_d->out_fd, STDOUT_FILENO) == -1)
		{
			perror("Dup2 Error");
			ft_cleanup_pipe(pipe_d);
			exit(EXIT_FAILURE);
		}
		close(pipe_d->out_fd);
	}
	else
	{
		if (dup2(pipe_d->fd_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("Dup2 Error");
			ft_cleanup_pipe(pipe_d);
			exit(EXIT_FAILURE);
		}
		close(pipe_d->in_fd);
	}
	close(pipe_d->fd_pipe[0]);
	close(pipe_d->fd_pipe[1]);
	run_cmd(env, pipe_d);
}

void ft_exec(t_pipex *pipe_d, char **env)
{
	pid_t pid;

	if (pipe(pipe_d->fd_pipe) == -1)
	{
		perror("Pipe Error");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1 && pipe_d->cmd_iter < pipe_d->cmd_count)
	{
		perror("Fork Error");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_exec(pipe_d, env);
	else
	{
		if (dup2(pipe_d->fd_pipe[0], STDIN_FILENO) == -1)
		{
			perror("Dup2 Error");
			ft_cleanup_pipe(pipe_d);
			exit(EXIT_FAILURE);
		}
		close(pipe_d->fd_pipe[0]);
		close(pipe_d->fd_pipe[1]);
	}
}

void pipex(t_pipex *pipe_d, char **env)
{
	if (dup2(pipe_d->in_fd, STDIN_FILENO) < 0)
	{
		perror("Dup2 Error");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	close(pipe_d->in_fd);
	while (pipe_d->cmd_iter < pipe_d->cmd_count)
	{
		ft_exec(pipe_d, env);
		pipe_d->cmd_iter++;
	}
	while (wait(NULL) != -1)
		;
}