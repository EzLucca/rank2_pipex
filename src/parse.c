/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/06 18:49:28 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	cmd = NULL;
	i = 1;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (!cmd[0] || access(cmd[0], F_OK) == -1)
		{
			path = ft_find_path(cmd[0], envp);
			if (!path || !path[0] || access(path, F_OK) == -1)
				ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", argv[i]);
		}
		else
			path = ft_strdup(cmd[0]);
		pipex->path[i - 2] = path;
		pipex->argv[i - 2] = cmd;
	}
}

int	get_files(t_pipex *pipex, int argc, char **argv)
{
	pipex->file_fd[0] = open(argv[1], O_RDONLY);
	if (pipex->file_fd[0] == -1)
		handle_files(argv[1]);
	pipex->file_fd[1] = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->file_fd[1] == -1)
	{
		handle_files(argv[argc - 1]);
	}
	return (1);
}

void	ft_check_args(t_pipex *pipex, int argc, char **argv)
{
	ft_memset(pipex, 0, sizeof(t_pipex));
	if (argc != 5)
	{
		ft_dprintf(STDERR_FILENO, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		ft_clean_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	ft_memset(pipex->pipe_fd, -1, sizeof(pipex->pipe_fd));
	pipex->cmds_count = argc - 3;
	pipex->path = ft_calloc(sizeof(char *), pipex->cmds_count + 1);
	pipex->argv = ft_calloc(sizeof(char **), pipex->cmds_count + 1);
	if (!pipex->path || !pipex->argv)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failure");
		ft_clean_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	get_files(pipex, argc, argv);
}
