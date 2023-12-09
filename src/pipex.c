/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:19:30 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 14:27:29 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

char *ft_get_correct_cmd_path(char *cmd, char **env_paths)
{
	int i;
	char *cmd_joined;
	char *tmp;

	i = 0;
	while (env_paths[i])
	{
		cmd_joined = ft_strjoin(env_paths[i], "/");
		tmp = cmd_joined;
		cmd_joined = ft_strjoin(cmd_joined, cmd);
		free(tmp);
		if (access(cmd_joined, X_OK) != -1)
			return cmd_joined;
		free(cmd_joined);
		i++;
	}
	return (NULL);
}

char **ft_parse_env_paths(int ac, char **envp)
{
	int i;
	char **paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
			{
				ft_printf_fd(2, "Failure while spliting ENV paths\n");
				exit(EXIT_FAILURE);
			}
			return (paths);
		}
		i++;
	}
	return (paths);
}

char ***ft_parse_args(int ac, char **av, t_pipex *pipe_d)
{
	int i;
	char ***args;

	i = 0;
	args = malloc(sizeof(char **) * (pipe_d->cmd_count + 1));
	args[pipe_d->cmd_count] = NULL;
	while (i < pipe_d->cmd_count)
	{
		args[i] = ft_split(av[i + pipe_d->cmd_offset], ' ');
		if (!args[i])
		{
			// TO DO: free
			ft_printf_fd(2, "Error: while spliting args array\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (args);
}

char **ft_parse_paths(int ac, t_pipex *pipe_d)
{
	int i;
	char **cmd_paths;

	i = 0;
	cmd_paths = (char **)malloc(sizeof(char *) * (pipe_d->cmd_count + 1));
	cmd_paths[pipe_d->cmd_count] = NULL;
	while (pipe_d->cmd_args[i])
	{
		if (!ft_strncmp(pipe_d->cmd_args[i][0], "/", 1))
		{
			cmd_paths[i] = ft_strdup(pipe_d->cmd_args[i][0]);
		}
		else
		{
			cmd_paths[i] = ft_get_correct_cmd_path(pipe_d->cmd_args[i][0], pipe_d->env_paths);
		}
		i++;
	}
	return (cmd_paths);
}

void ft_init_pipex(int ac, char **av, char **envp, t_pipex *pipe_d)
{
	pipe_d->cmd_count = 2;
	pipe_d->cmd_offset = 2;
	pipe_d->in_fd = open(av[1], O_RDONLY);
	pipe_d->out_fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT);
	if (pipe_d->out_fd < 0 || pipe_d->in_fd < 0)
	{
		perror("Error: while opening files");
		exit(EXIT_FAILURE);
	}
	pipe_d->env_paths = ft_parse_env_paths(ac, envp);
	pipe_d->cmd_args = ft_parse_args(ac, av, pipe_d);
	pipe_d->cmd_paths = ft_parse_paths(ac, pipe_d);
}

int main(int ac, char **av, char **envp)
{
	t_pipex *pipe_d;
	pid_t pid;
	int fd_pipe[2];

	if (ac != 5)
	{
		ft_fprintf(stderr, "Invalid Arguments: run the program as follows > ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	pipe_d = malloc(sizeof(t_pipex));
	if (!pipe_d)
	{
		ft_fprintf(stderr, "Error: while allocating memory\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd_pipe) < 0)
	{
		perror("Pipe Error");
		exit(EXIT_FAILURE);
	}
	ft_init_pipex(ac, av, envp, pipe_d);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork Error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(pipe_d->in_fd, STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		execve(pipe_d->cmd_paths[0], pipe_d->cmd_args[0], envp);
		perror("Error: while executing cmd1");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd_pipe[1]);
		pid = fork();
		if (pid < 0)
		{
			perror("Fork Error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dup2(fd_pipe[0], STDIN_FILENO);
			dup2(pipe_d->out_fd, STDOUT_FILENO);
			close(fd_pipe[0]);
			execve(pipe_d->cmd_paths[1], pipe_d->cmd_args[1], envp);
			perror("Error: while executing cmd2");
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd_pipe[0]);
			close(pipe_d->in_fd);
			close(pipe_d->out_fd);
			waitpid(pid, NULL, 0); // Wait for the second child process to complete
			wait(NULL); // Wait for the first child process to complete
		}
	}
	free(pipe_d);
	return 0;
}