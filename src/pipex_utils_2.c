/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:52:28 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 16:48:27 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

void	ft_init_pipe(t_pipex *pipe_d)
{
	if (pipe_d->cmd_iter == 0)
	{
		close(pipe_d->fd_pipe[0]);
		dup2(pipe_d->in_fd, STDIN_FILENO);
		dup2(pipe_d->fd_pipe[1], STDOUT_FILENO);
		close(pipe_d->fd_pipe[1]);
	}
	else if (pipe_d->cmd_iter == pipe_d->cmd_count - 1)
	{
		dup2(pipe_d->fd_pipe[0], STDIN_FILENO);
		dup2(pipe_d->out_fd, STDOUT_FILENO);
		close(pipe_d->fd_pipe[0]);
	}
	else
	{
		dup2(pipe_d->fd_pipe[0], STDIN_FILENO);
		dup2(pipe_d->fd_pipe[1], STDOUT_FILENO);
		close(pipe_d->fd_pipe[0]);
		close(pipe_d->fd_pipe[1]);
	}
}

void	ft_close_pipe(t_pipex *pipe_d)
{
	if (pipe_d->cmd_iter == 0)
		close(pipe_d->fd_pipe[1]);
	else if (pipe_d->cmd_iter == pipe_d->cmd_count - 1)
		close(pipe_d->fd_pipe[0]);
	else
	{
		close(pipe_d->fd_pipe[0]);
		close(pipe_d->fd_pipe[1]);
	}
}

void	free_double_p(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_cleanup_pipe(t_pipex *pipe_d)
{
	int	i;

	i = 0;
	while (i < pipe_d->cmd_count)
	{
		free_double_p(pipe_d->cmd_args[i]);
		i++;
	}
	free(pipe_d->cmd_args);
	free_double_p(pipe_d->cmd_paths);
	free_double_p(pipe_d->env_paths);
	free(pipe_d);
}
