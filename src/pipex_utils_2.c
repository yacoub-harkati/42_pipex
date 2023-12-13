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

int	open_infile(char **av, t_pipex *pipe_d)
{
	int	fd;

	if (pipe_d->here_doc)
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

int	open_outfile(int ac, char **av, t_pipex *pipe_d)
{
	int	fd;

	if (pipe_d->here_doc)
		fd = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	return (fd);
}

int	is_here_doc(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (1);
	else
		return (0);
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
	if (pipe_d->here_doc)
		unlink("here_doc");
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
