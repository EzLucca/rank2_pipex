/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:24 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/06 19:19:20 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_execution(t_pipex *pipex, int idx, char **envp)
{
	if (idx == 0)
	{
		if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0)
			ft_clean_exit(pipex);
	}
	if (idx == pipex->cmds_count -1)
	{
		if (pipex->file_fd[1] < 0 || dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
			ft_clean_exit(pipex);
	}
	else
	{
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) < 0)
			ft_clean_exit(pipex);
	}
	close_all(pipex);
	if (pipex->path[idx] && access(pipex->path[idx], F_OK) == 0)
		execve(pipex->path[idx], pipex->argv[idx], envp);
	ft_clean_pipex(pipex);
	exit(127);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	if (pipe(pipex->pipe_fd) == -1)
		return (-1);
	pipex->pids[idx] = fork();
	if (pipex->pids[idx] < 0)
	{
		close_all(pipex);
		return (1);
	}
	if (pipex->pids[idx] == 0)
		child_execution(pipex, idx, envp);
	else
	{
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) < 0)
			ft_clean_exit(pipex);
		close(pipex->pipe_fd[1]);
		close(pipex->pipe_fd[0]);
		close(pipex->file_fd[0]);
		if (idx == pipex->cmds_count)
			close(pipex->file_fd[1]);
	}
	return (0);
}

int	wait_processes(pid_t *pid, int cmds_count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	while (i < cmds_count)
	{
		waitpid(pid[i], &status, 0);
		// wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && WTERMSIG(status))
			last_status = 128 + WTERMSIG(status);
		i++;
	}
	return (last_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;
	int		i;

	if (argc < 5)
	{
		ft_dprintf(STDERR_FILENO, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	check_paths(envp, argv);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_init_pipex(pipex, argc, argv);
	ft_parse_cmds(pipex, argc, argv, envp);
	while (i < pipex->cmds_count)
	{
		if (spawn_child(pipex, envp, i) != 0)
			return (ft_clean_pipex(pipex), 1);
		i++;
	}
	status = wait_processes(pipex->pids, pipex->cmds_count);
	return (ft_clean_pipex(pipex), status);
}
