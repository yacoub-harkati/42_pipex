/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:19:30 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/08 00:09:02 by yaharkat         ###   ########.fr       */
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
		cmd_joined = ft_strjoin(cmd_joined, cmd);
		if (access(cmd_joined, X_OK) != -1)
			return cmd_joined;
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
	cmd_paths = malloc(sizeof(char *) * (pipe_d->cmd_count + 1));
	cmd_paths[pipe_d->cmd_count] = NULL;
	while (i < pipe_d->cmd_count)
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
	if (pipe_d->in_fd < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	pipe_d->out_fd = open(av[1], O_RDWR | O_TRUNC | O_CREAT);
	if (pipe_d->out_fd < 0)
	{
		perror("Error");
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
	
	if (ac < 5 || ac > 5)
	{
		ft_printf_fd(2, "Invalid Arguments: run the program as follow > ./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
	if (pipe(fd_pipe) < 0)
	{
		perror("Pipe Error");
		exit(EXIT_FAILURE);
	}
	ft_init_pipex(ac, av, envp, pipe_d);
	while ()
	{
		
	}
}