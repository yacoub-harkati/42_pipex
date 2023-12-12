#ifndef PIPEX_H
#define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

typedef struct s_pipex
{
	int in_fd;
	int out_fd;
	int cmd_count;
	int cmd_iter;
	int cmd_offset;
	char **cmd_paths;
	char **env_paths;
	char ***cmd_args;
	int fd_pipe[2];
} t_pipex;

char *ft_get_correct_cmd_path(char *cmd, char **env_paths);
char **ft_parse_env_paths(char **envp, t_pipex *pipe_d);
char ***ft_parse_args(char **av, t_pipex *pipe_d);
char **ft_parse_paths(t_pipex *pipe_d);
void ft_init_pipex(int ac, char **av, char **envp, t_pipex *pipe_d);

void ft_init_pipe(t_pipex *pipe_d);
void ft_close_pipe(t_pipex *pipe_d);
void ft_exec(t_pipex *pipe_d, char **envp);
void free_double_p(char **str);
void ft_cleanup_pipe(t_pipex *pipe_d);

#endif