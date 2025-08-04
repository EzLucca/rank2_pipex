/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:24 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/04 18:28:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
//
// int	fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx)
// {
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	*pid = fork();
// 	if (*pid < 0)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		return (-1);
// 	}
// 	if (*pid == 0)
// 	{
// 		close(fd[0]);
// 		if (idx == 0)
// 			if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0)
// 				ft_exit(errno, "dup2 (stdin) failed", pipex);
// 		if (idx == pipex->cmds_count -1)
// 		{
// 			if (dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
// 				return (1);
// 		}
// 		else
// 		{
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[1]);
// 		}
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 	}
// 	return (0);
// }
//
// int	spawn_child(t_pipex *pipex, char **envp, int idx)
// {
// 	pid_t	pid;
// 	int		fd[2];
//
// 	if (fork_and_pipe(pipex, fd, &pid, idx) != 0)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		if (pipex->path[idx])
// 			execve(pipex->path[idx], pipex->argv[idx], envp);
// 		ft_clean_pipex(pipex);
// 		exit(127);
// 	}
// 	pipex->return_status = wait_processes(&pid, pipex->cmds_count);
// 	return (0);
// }
//
// Spawns a single child process

int	parent_process(t_pipex *pipex, pid_t pid, int idx, int *fd)
{
	if (idx < pipex->cmds_count - 1)
	{
		close(fd[1]);
		pipex->pipe_fd[0] = fd[0];
	}
	pipex->pids[idx] = pid;
	return (0);
}

void	child_process(t_pipex *pipex, char **envp, int idx, int *fd)
{
	if (idx == 0)
	{
		if (pipex->file_fd[0] == -1)
		{
			ft_clean_pipex(pipex);
			exit(1);
		}
		if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0)
			ft_exit(errno, "dup2 (infile) failed", pipex);
	}
	else
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) < 0)
			ft_exit(errno, "dup2 (pipe read) failed", pipex);
	if (idx == pipex->cmds_count - 1)
	{
		if (dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
			ft_exit(errno, "dup2 (outfile) failed", pipex);
	}
	else
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			ft_exit(errno, "dup2 (pipe write) failed", pipex);
		close(fd[1]);
	}
	if (pipex->path[idx])
		execve(pipex->path[idx], pipex->argv[idx], envp);
	ft_clean_pipex(pipex);
	exit(127);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (idx < pipex->cmds_count - 1)
	{
		if (pipe(fd) == -1)
			return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		if (idx < pipex->cmds_count - 1)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return (-1);
	}
	if (pid == 0)
		child_process(pipex, envp, idx, fd);
	else
		return (parent_process(pipex, pid, idx, fd));
	return (0);
}

int	wait_processes(pid_t *pids, int cmds_count)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < cmds_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;
	int		status;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_check_args(pipex, argc, argv);
	ft_parse_cmds(pipex, argc, argv, envp);
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmds_count);
	if (!pipex->pids)
		ft_exit(EXIT_FAILURE, "Malloc failure", pipex);
	i = 0;
	while (i < pipex->cmds_count)
	{
		if (spawn_child(pipex, envp, i) != 0)
			return (ft_clean_pipex(pipex), 1);
		i++;
	}
	status = wait_processes(pipex->pids, pipex->cmds_count);
	ft_clean_pipex(pipex);
	return (status);
}
