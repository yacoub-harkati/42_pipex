/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:50:30 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/12 21:50:30 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

int	get_cmd_number(int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (ac - 4);
	else
		return (ac - 3);
}

int	get_cmd_offset(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (3);
	else
		return (2);
}

void	ft_cleanup_exit(t_pipex *pipe_d)
{
	ft_cleanup_pipe(pipe_d);
	exit(EXIT_FAILURE);
}

void	close_both_fds(t_pipex *pipe_d)
{
	close(pipe_d->fd_pipe[0]);
	close(pipe_d->fd_pipe[1]);
}
