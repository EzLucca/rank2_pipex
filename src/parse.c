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

char	*get_path(char *arg, char **cmd, char **envp)
{
	char	*path;

	if (cmd[0] && access(cmd[0], F_OK) == 0)
		return (ft_strdup(cmd[0]));
	path = ft_find_path(cmd[0], envp);
	if (!path || !*path)
	{
		if (ft_strchr(arg, '/'))
			handle_files(arg);
		else
			ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", arg);
	}
	return (path);
}

void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;
	char	**cmd;

	i = 1;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		pipex->path[i - 2] = get_path(argv[i], cmd, envp);
		pipex->argv[i - 2] = cmd;
	}
}

int	get_files(t_pipex *pipex)
{
	pipex->file_fd[0] = open(pipex->av[1], O_RDONLY);
	if (pipex->file_fd[0] == -1)
		handle_files(pipex->av[1]);
	pipex->file_fd[1] = open(pipex->av[pipex->ac - 1], O_CREAT | O_WRONLY
			| O_TRUNC, 0644);
	if (pipex->file_fd[1] == -1)
	{
		handle_files(pipex->av[pipex->ac - 1]);
	}
	return (1);
}

void	ft_init_pipex(t_pipex *pipex, int argc, char **argv)
{
	ft_memset(pipex, 0, sizeof(t_pipex));
	ft_memset(pipex->pipe_fd, -1, sizeof(pipex->pipe_fd));
	pipex->ac = argc;
	pipex->av = argv;
	pipex->cmds_count = argc - 3;
	pipex->path = ft_calloc(sizeof(char *), pipex->cmds_count + 1);
	pipex->argv = ft_calloc(sizeof(char **), pipex->cmds_count + 1);
	pipex->pids = ft_calloc(sizeof(int), pipex->cmds_count);
	if (!pipex->path || !pipex->argv || !pipex->pids)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failure");
		ft_clean_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	get_files(pipex);
}

void	handle_files(char *filename)
{
	if (errno == EISDIR)
		ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", filename);
	else if (errno == ENOTDIR)
		ft_dprintf(STDERR_FILENO, "pipex: %s: Not a directory\n", filename);
	else if (errno == EACCES)
		ft_dprintf(STDERR_FILENO, "pipex: %s: Permission denied\n", filename);
	else if (errno == ENOENT)
		ft_dprintf(STDERR_FILENO, "pipex: %s: No such file or directory\n",
			filename);
	else
		ft_dprintf(STDERR_FILENO, "pipex: %s: Error opening\n", filename);
}
