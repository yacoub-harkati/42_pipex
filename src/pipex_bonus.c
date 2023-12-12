/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:19:30 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 16:36:49 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

int get_cmd_number(int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (ac - 4);
	else
		return (ac - 3);
}

int get_cmd_offset(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (3);
	else
		return (2);
}

void write_here_doc(int in_fd, char *eof)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, eof, 3) == 0)
		{
			free(line);
			break;
		}
		ft_fprintf(in_fd, "%s\n", line);
		free(line);
	}
}

int open_infile(char **av, t_pipex *pipe_d)
{
	int fd;

	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		fd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
		{
			perror("Error: while opening here_doc file");
			ft_cleanup_pipe(pipe_d);
			exit(EXIT_FAILURE);
		}
		write_here_doc(fd, av[2]);
		close(fd);
		fd = open("here_doc", O_RDONLY, 0644);
	}
	else
		fd = open(av[1], O_RDONLY, 0644);
	return (fd);
}

int open_outfile(int ac, char **av)
{
	int fd;

	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		fd = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	return (fd);
}

void ft_init_pipex(int ac, char **av, char **envp, t_pipex *pipe_d)
{
	pipe_d->cmd_count = get_cmd_number(ac, av);
	pipe_d->cmd_offset = get_cmd_offset(av);
	pipe_d->cmd_iter = 0;
	pipe_d->env_paths = ft_parse_env_paths(envp, pipe_d);
	pipe_d->cmd_args = ft_parse_args(av, pipe_d);
	pipe_d->cmd_paths = ft_parse_paths(pipe_d);
	pipe_d->in_fd = open_infile(av, pipe_d);
	pipe_d->out_fd = open_outfile(ac, av);
	if (pipe_d->out_fd < 0 || pipe_d->in_fd < 0)
	{
		ft_cleanup_pipe(pipe_d);
		perror("Error: while opening files");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_d->fd_pipe) < 0)
	{
		perror("Pipe Error");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
}

void ft_exec(t_pipex *pipe_d, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork Error");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ft_init_pipe(pipe_d);
		execve(pipe_d->cmd_paths[pipe_d->cmd_iter],
			   pipe_d->cmd_args[pipe_d->cmd_iter], envp);
		ft_fprintf(2, "Error: while executing command %d: %s\n", pipe_d->cmd_iter + 1, strerror(errno));
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_close_pipe(pipe_d);
		waitpid(pid, NULL, 0);
	}
}

int main(int ac, char **av, char **envp)
{
	t_pipex *pipe_d;

	if (ac < 5)
	{
		ft_fprintf(2,
				   "Invalid Arguments: > ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		exit(EXIT_FAILURE);
	}
	pipe_d = malloc(sizeof(t_pipex));
	if (!pipe_d)
	{
		ft_fprintf(2, "Error: while allocating memory\n");
		exit(EXIT_FAILURE);
	}
	ft_init_pipex(ac, av, envp, pipe_d);
	while (pipe_d->cmd_iter < pipe_d->cmd_count)
	{
		ft_exec(pipe_d, envp);
		pipe_d->cmd_iter++;
	}
	ft_cleanup_pipe(pipe_d);
	return (EXIT_SUCCESS);
}
