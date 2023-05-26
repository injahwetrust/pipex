/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:27:42 by bvaujour          #+#    #+#             */
/*   Updated: 2023/04/12 16:53:36 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

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
	if (execve(path, s_cmd, env) < 0)
	{
		write(2, "command not found: ", 20);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free(s_cmd);
		exit(0);
	}
}

int	child2(char **argv, int *p_fd, char **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(p_fd[1]);
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(argv[4]);
			close(p_fd[0]);
			exit(0);
		}
		if (dup2(fd, 1) == -1)
			perror("pipex");
		if (dup2(p_fd[0], 0))
			perror("pipex");
		close(p_fd[0]);
		close(fd);
		exec(argv[3], env);
	}
	return (pid);
}

int	child(char **argv, int *p_fd, char **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(p_fd[0]);
		fd = open(argv[1], O_RDONLY, 0644);
		if (fd < 0)
		{
			perror(argv[1]);
			close (p_fd[1]);
			exit(0);
		}
		if (dup2(fd, 0) == -1)
			perror("pipex");
		close(fd);
		if (dup2(p_fd[1], 1) == -1)
			perror("pipex");
		close(p_fd[1]);
		exec(argv[2], env);
		exit(0);
	}
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	int	p_fd[2];
	int	pids[2];

	if (argc != 5)
		return (write(2, "use |infile cmd cmd outfile| arguments\n",
				39));
	if (pipe(p_fd) == -1)
		return (write(2, "error with opening the pipes\n", 29));
	pids[0] = child(argv, p_fd, env);
	pids[1] = child2(argv, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}
