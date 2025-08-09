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

// end of first child file_fd[1] and pipe_fd[1] are open
// end of second child file_fd all open and pipe_fd[1] are open
void	execute_child(t_pipex *pipex, pid_t *pid, int idx, char **envp)
{
	if (idx == 0)
	{
		if (dup2(pipex->file_fd[0], STDIN_FILENO) < 0)
			ft_exit(errno, "dup2 (stdin) failed", pipex);	
	}
	if (idx == pipex->cmds_count -1)
	{
		if (pipex->file_fd[1] < 0 ||dup2(pipex->file_fd[1], STDOUT_FILENO) < 0)
		{
			ft_clean_pipex(pipex);
			exit (1);
			// ft_exit(errno, "dup2 (stdout) failed", pipex);	
		}
	}
	else
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close_all(pipex);
	if (pipex->path[idx] && access(pipex->path[idx], F_OK) == 0)
		execve(pipex->path[idx], pipex->argv[idx], envp);
	// if (errno == ENOENT)
	// {
	// 	ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", pipex->argv[idx][0]);
	// 	exit(127);
	// }
	// else if (errno == EACCES)
	// {
	// 	ft_dprintf(STDERR_FILENO, "pipex: %s: Permission denied\n", pipex->argv[idx][0]);
	// 	exit(126);
	// }
	// else if (errno == EISDIR)
	// {
	// 	ft_dprintf(STDERR_FILENO, "pipex: %s: is a directory\n", pipex->argv[idx][0]);
	// 	exit(126);
	// }
	// else
	// {
	// 	perror("pipex");
	ft_clean_pipex(pipex);
	exit(127);
	// }
}

int	pe(t_pipex *pipex, pid_t *pid, int idx, char **envp)
{
	if (*pid == 0) // only child access here
	{
		// get_files(pipex);
		execute_child(pipex, pid, idx, envp);
	}
	else
	{
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		safe_close(&pipex->pipe_fd[1]);
		safe_close(&pipex->file_fd[0]);
	}
	return (0);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	if (pipe(pipex->pipe_fd) == -1)
		return (-1);
	pipex->pids[idx] = fork();
	if (pipex->pids[idx] < 0)
	{
		close_all(pipex);
		return (-1);
	}
	if (pe(pipex, &pipex->pids[idx], idx, envp) != 0)
		return (1);
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
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		// else if (WIFSIGNALED(status) && WTERMSIG(status))
		// 	last_status = 128 + WTERMSIG(status);
		i++;
	}
	return (last_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;
	int		i;

	i = 0;
	check_paths(envp, argv);
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
	status = wait_processes(pipex->pids,  pipex->cmds_count);
	return (ft_clean_pipex(pipex), status);
}
