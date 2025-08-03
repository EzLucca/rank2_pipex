/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/02 20:14:30 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int     i;
	char    **cmd;
	char    *path;

	cmd = NULL;
	pipex->fullpath = ft_calloc(sizeof(char *) + 1, pipex->cmds_count);
	pipex->argv = ft_calloc(sizeof(char **) + 1, pipex->cmds_count);
	if (!pipex->fullpath || !pipex->argv)
	{
		ft_clean_pipex(pipex);
	}
	i = 1;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		// if (!cmd || !*cmd)
		// {
		// 	ft_dprintf(STDERR_FILENO, "%s: command not found\n", argv[i]);
		// 	// ft_clean_pipex(pipex); // Custom cleanup if allocation fails
		// }
		path = ft_find_path(cmd[0], envp);
		if (!path)
			ft_free_array(cmd);
		// ft_clean_pipex(pipex);
		if (!path || !path[0] || access(path, F_OK) == -1) 
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", argv[i]);
		pipex->fullpath[i - 2] = path;
		// ft_printf("fullpath[%d]: %s\n", i, pipex->fullpath[i - 2 - pipex->here_doc]); // TESTING:
		pipex->argv[i - 2] = cmd;
		// pipex->argv[i - 2] = &argv[i - 2];
	}
}

int	get_files(t_pipex *pipex, int argc, char **argv)
{
	pipex->file_fd[0] = open(argv[1], O_RDONLY);
	if (pipex->file_fd[0] == -1)
	{
		handle_files(argv[1]);
		pipex->invalid_input = true;
	}
	pipex->file_fd[1] = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->file_fd[1] == -1)
	{
		handle_files(argv[argc - 1]);
		// ft_clean_pipex(pipex);
		// exit(EXIT_FAILURE);
	}
	return (1);
}

void	ft_check_args(t_pipex *pipex,int argc, char **argv)
{
	ft_memset(pipex, 0, sizeof(t_pipex));
	if (argc != 5)
	{
		ft_dprintf(STDERR_FILENO, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		ft_clean_pipex(pipex); // Custom cleanup if allocation fails
		exit(EXIT_FAILURE);
	}
	ft_memset(pipex->pipe_fd, -1, sizeof(pipex->pipe_fd));
	pipex->cmds_count = argc - 3 - pipex->here_doc;
	get_files(pipex, argc, argv);
}
