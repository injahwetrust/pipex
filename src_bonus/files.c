/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:31:33 by bvaujour          #+#    #+#             */
/*   Updated: 2023/04/12 16:54:03 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_enter(char **argv)
{
	int	fd_infile;

	fd_infile = fileopen(argv[1], 0);
	if (fd_infile >= 0)
	{
		if (dup2(fd_infile, 0) == -1)
			perror("pipex");
		close(fd_infile);
		return (2);
	}
	else
	{
		perror(argv[1]);
		fd_infile = fileopen(NULL, 3);
		if (dup2(fd_infile, 0) == -1)
			perror("pipex");
		close(fd_infile);
		return (3);
	}
}

int	begin(int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			exit(write(2, "Error\nUse here_doc LIMITER cmd1 cmd2 outfile\n", 45));
		here_doc(argv);
		return (3);
	}
	else
		return (open_enter(argv));
}

void	end(int argc, char **argv)
{
	int	fd_outfile;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		fd_outfile = fileopen(argv[argc - 1], 2);
		if (dup2(fd_outfile, 1) == -1)
			perror("pipex");
		if (fd_outfile != -1)
			close(fd_outfile);
	}
	else
	{
		fd_outfile = fileopen(argv[argc - 1], 1);
		if (dup2(fd_outfile, 1) == -1)
			perror("pipex");
		if (fd_outfile != -1)
			close(fd_outfile);
	}
}
