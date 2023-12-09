/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:52:28 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 16:23:50 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/pipex.h"

char	*ft_get_correct_cmd_path(char *cmd, char **env_paths)
{
	int		i;
	char	*cmd_joined;
	char	*tmp;

	i = 0;
	while (env_paths[i])
	{
		cmd_joined = ft_strjoin(env_paths[i], "/");
		tmp = cmd_joined;
		cmd_joined = ft_strjoin(cmd_joined, cmd);
		free(tmp);
		if (access(cmd_joined, X_OK) != -1)
			return (cmd_joined);
		free(cmd_joined);
		i++;
	}
	return (NULL);
}

char	**ft_parse_env_paths(int ac, char **envp, t_pipex *pipe_d)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
			{
				ft_cleanup_pipe(pipe_d);
				ft_fprintf(2, "Failure while spliting ENV paths\n");
				exit(EXIT_FAILURE);
			}
			return (paths);
		}
		i++;
	}
	return (paths);
}

char	***ft_parse_args(int ac, char **av, t_pipex *pipe_d)
{
	int		i;
	char	***args;

	i = 0;
	args = malloc(sizeof(char **) * (pipe_d->cmd_count + 1));
	args[pipe_d->cmd_count] = NULL;
	while (i < pipe_d->cmd_count)
	{
		args[i] = ft_split(av[i + pipe_d->cmd_offset], ' ');
		if (!args[i])
		{
			ft_cleanup_pipe(pipe_d);
			ft_fprintf(2, "Error: while spliting args array\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (args);
}

char	**ft_parse_paths(int ac, t_pipex *pipe_d)
{
	int		i;
	char	**cmd_paths;

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
			cmd_paths[i] = ft_get_correct_cmd_path(pipe_d->cmd_args[i][0],
					pipe_d->env_paths);
		}
		i++;
	}
	return (cmd_paths);
}
