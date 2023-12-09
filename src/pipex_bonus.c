/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:19:30 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 16:28:43 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

void	ft_init_pipex(int ac, char **av, char **envp, t_pipex *pipe_d)
{
	pipe_d->cmd_count = 2;
	pipe_d->cmd_offset = 2;
	pipe_d->cmd_iter = 0;
	pipe_d->in_fd = open(av[1], O_RDONLY, 0644);
	pipe_d->out_fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipe_d->out_fd < 0 || pipe_d->in_fd < 0)
	{
		perror("Error: while opening files");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	pipe_d->env_paths = ft_parse_env_paths(ac, envp, pipe_d);
	pipe_d->cmd_args = ft_parse_args(ac, av, pipe_d);
	pipe_d->cmd_paths = ft_parse_paths(ac, pipe_d);
	if (pipe(pipe_d->fd_pipe) < 0)
	{
		perror("Pipe Error");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
}

void	ft_exec(t_pipex *pipe_d, char **envp)
{
	pid_t	pid;

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
		perror("Error: while executing command");
		ft_cleanup_pipe(pipe_d);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_close_pipe(pipe_d);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipe_d;

	if (ac < 5)
	{
		ft_fprintf(2,
			"Invalid Arguments: > ./pipex file1 cmd1 cmd2 file2\n");
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
	return (0);
}
