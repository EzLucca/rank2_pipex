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

// INFILE: pipex->file_fd[0] = 3
// OUTFILE: pipex->file_fd[1] = 4
// pipe read: pipex->pipe_fd[0] = 5
// pipe write: pipex->pipe_fd[1] = 6

int	pe(t_pipex *pipex, pid_t *pid, int idx, char **envp)
{
	if (*pid == 0) // only child access here
	{
		safe_close(&pipex->pipe_fd[0]);
		if (idx == 0)
		{
			if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0)
				ft_exit(errno, "dup2 (stdin) failed", pipex);	
			safe_close(&pipex->file_fd[0]);
		}
		if (idx == pipex->cmds_count -1)
		{
			if (dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
				return (1);
		}
		else
			dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		safe_close(&pipex->pipe_fd[1]);
		safe_close(&pipex->file_fd[0]);
		safe_close(&pipex->file_fd[1]);
		if (pipex->path[idx])
			execve(pipex->path[idx], pipex->argv[idx], envp);
		ft_clean_pipex(pipex);
		exit(127);
	}
	else
	{
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		// safe_close(&pipex->pipe_fd[0]);
		safe_close(&pipex->pipe_fd[1]);
		safe_close(&pipex->file_fd[0]);
	}
	return (0);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;

	if (pipe(pipex->pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		safe_close(&pipex->pipe_fd[0]);
		safe_close(&pipex->pipe_fd[1]);
		return (-1);
	}
	if (pe(pipex, &pid, idx, envp) != 0)
		return (1);
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
	if (!envp || envp[0] == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Empty enviroment.\n");
		return (127);
	}
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
