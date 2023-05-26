/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:43:21 by bvaujour          #+#    #+#             */
/*   Updated: 2023/04/07 12:43:24 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	fileopen(char *file, int option)
{
	int	fd;

	if (option == 0)
		return (open(file, O_RDONLY, 0644));
	if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (option == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (option == 3)
		return (open("/tmp/pipextmp", O_RDONLY | O_CREAT, 0644));
	if (fd < 0)
		perror(file);
	return (fd);
}

char	*get_exec(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	paths = ft_split(find_path(env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (paths[++i])
	{
		path_part = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free(paths);
			ft_free(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free(paths);
	ft_free(s_cmd);
	return (cmd);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_exec(s_cmd[0], env);
	if (execve(path, s_cmd, env) <= -1)
	{
		errno = ESRCH;
		perror(s_cmd[0]);
		ft_free(s_cmd);
		exit(0);
	}
}
