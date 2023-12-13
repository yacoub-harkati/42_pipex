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

void	ft_init_pipex(int ac, char **av, char **envp, t_pipex *pipe_d)
{
	pipe_d->here_doc = is_here_doc(av);
	pipe_d->cmd_count = get_cmd_number(ac, av);
	pipe_d->cmd_offset = get_cmd_offset(av);
	pipe_d->cmd_iter = 0;
	pipe_d->env_paths = ft_parse_env_paths(envp, pipe_d);
	pipe_d->cmd_args = ft_parse_args(av, pipe_d);
	pipe_d->cmd_paths = ft_parse_paths(pipe_d);
	pipe_d->in_fd = open_infile(av, pipe_d);
	pipe_d->out_fd = open_outfile(ac, av, pipe_d);
	if (pipe_d->out_fd < 0 || pipe_d->in_fd < 0)
	{
		ft_cleanup_pipe(pipe_d);
		perror("Error: while opening files");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipe_d;

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
	pipex(pipe_d, envp);
	ft_cleanup_pipe(pipe_d);
	return (EXIT_SUCCESS);
}
