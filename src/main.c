/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:24 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/02 21:27:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx)
{
	if (pipe(fd) == -1)
		return (-1);
	*pid = fork();
	if (*pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (*pid == 0) // only child access here
	{
		close(fd[0]);
		if (idx == 0)
			if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0)
				ft_exit(errno, "dup2 (stdin) failed", pipex);	
		if (idx == pipex->cmds_count -1)
		{
			if (dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
				// ft_exit(errno, "dup2 (stdout) failed", pipex);	
				return (1);
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (0);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (fork_and_pipe(pipex, fd, &pid, idx) != 0)
		return (1);
	if (pid == 0)
	{
		if (pipex->fullpath[idx])
			execve(pipex->fullpath[idx], pipex->argv[idx], envp);
		else
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", *pipex->argv[idx]);
		ft_clean_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	pipex->return_status = wait_processes(&pid, pipex->cmds_count);
	return (0);
}

int	wait_processes(pid_t *pid, int cmds_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmds_count)
		waitpid(pid[i++], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;
	int		i;

	i = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_check_args(pipex, argc, argv);
	ft_parse_cmds(pipex, argc, argv, envp);
	while (i < pipex->cmds_count)
	{
		if (spawn_child(pipex, envp, i) != 0)
			return (ft_clean_pipex(pipex), 1);
		i++;
	}
	status = pipex->return_status;
	return (ft_clean_pipex(pipex), status);
}
