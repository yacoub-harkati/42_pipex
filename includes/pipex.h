/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:24:44 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/16 11:24:44 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		cmd_count;
	int		cmd_iter;
	int		cmd_offset;
	int		here_doc;
	char	**cmd_paths;
	char	**env_paths;
	char	***cmd_args;
	int		fd_pipe[2];
}			t_pipex;

char		*ft_get_correct_cmd_path(char *cmd, char **env_paths);
char		**ft_parse_env_paths(char **envp, t_pipex *pipe_d);
char		***ft_parse_args(char **av, t_pipex *pipe_d);
char		**ft_parse_paths(t_pipex *pipe_d);
void		ft_init_pipex(int ac, char **av, char **envp, t_pipex *pipe_d);
void		ft_exec(t_pipex *pipe_d, char **env);
void		free_double_p(char **str);
void		ft_cleanup_pipe(t_pipex *pipe_d);
void		pipex(t_pipex *pipe_d, char **env);
void		child_exec(t_pipex *pipe_d, char **env);
void		run_cmd(char **env, t_pipex *pipe_d);
void		write_here_doc(int in_fd, char *eof);
int			is_here_doc(char **av);
int			open_outfile(int ac, char **av, t_pipex *pipe_d);
int			open_infile(char **av, t_pipex *pipe_d);
int			get_cmd_number(int ac, char **av);
int			get_cmd_offset(char **av);
void		ft_cleanup_exit(t_pipex *pipe_d);
void		close_both_fds(t_pipex *pipe_d);

#endif