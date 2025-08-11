/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:24 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/11 19:13:06 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_execution(t_pipex *pipex, int idx, char **envp)
{
	if (idx == 0)
	{
		if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0
			|| dup2(pipex->pipe_fd[1], STDOUT_FILENO) < 0)
			ft_clean_exit(pipex);
	}
	else
	{
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) < 0
			|| dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
			ft_clean_exit(pipex);
	}
	close_all(pipex);
	if (pipex->path[idx] && access(pipex->path[idx], F_OK) == 0)
	{
		execve(pipex->path[idx], pipex->argv[idx], envp);
		handle_error(pipex->path[idx]);
		ft_clean_pipex(pipex);
		exit(126);
	}
	ft_clean_pipex(pipex);
	exit(127);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pipex->pids[idx] = fork();
	if (pipex->pids[idx] < 0)
	{
		close_all(pipex);
		return (1);
	}
	if (pipex->pids[idx] == 0)
		child_execution(pipex, idx, envp);
	if (idx == 0)
		close(pipex->pipe_fd[1]);
	else
		close(pipex->pipe_fd[0]);
	return (0);
}

int	wait_processes(pid_t *pid, int cmds_count)
{
	int		status;
	pid_t	term_pid;
	int		exit_status;

	exit_status = EXIT_FAILURE;
	while (cmds_count > 0)
	{
		term_pid = waitpid(-1, &status, 0);
		if (term_pid == -1)
			return (1);
		if (term_pid == pid[0] || term_pid == pid[1])
		{
			cmds_count--;
			if (term_pid == pid[1] && (WIFEXITED(status)))
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;
	int		i;

	if (argc != 5)
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
	close_all(pipex);
	status = wait_processes(pipex->pids, pipex->cmds_count);
	return (ft_clean_pipex(pipex), status);
}
