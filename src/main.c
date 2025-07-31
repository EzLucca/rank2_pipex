
#include "../include/pipex.h"

int	fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx)
{
	if (pipe(fd) == -1)
		return (-1);
	*pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (*pid == 0) // only child access here
	{
		if (idx == 0)
			dup2(pipex->file_fd[0], STDIN_FILENO);
		if (idx == pipex->cmds_count -1)
			dup2(pipex->file_fd[1], STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	return (0);
}

// int spawn_child(t_pipex *pipex, char **envp, int idx)
// {
// 	pid_t   pid;
// 	int curr = idx % 2;         // Toggle between 0 and 1
// 	int prev = (idx + 1) % 2;   // Opposite of curr
//
// 	if (pipe(pipex->pipe_fd[curr]) == -1)
// 		return (-1);
// 	pid = fork();
// 	pipex->pids[idx] = pid;
// 	if (pid < 0)
// 	{
// 		close(pipex->pipe_fd[curr][0]);
// 		close(pipex->pipe_fd[curr][1]);
// 		return (-1);
// 	}
// 	if (pid == 0) // child
// 	{
// 		if (idx == 0)
// 		{
// ft_dprintf(STDERR_FILENO, "FDs for cmd %d: curr read = %d, prev read = %d\n", idx, pipex->pipe_fd[curr][0], pipex->pipe_fd[prev][0]);
// 			dup2(pipex->file_fd[0], STDIN_FILENO);
// 			ft_dprintf(STDERR_FILENO, "FDs for cmd %d: curr read = %d, prev read = %d\n", idx, pipex->pipe_fd[curr][0], pipex->pipe_fd[prev][0]);
// 		}
// 		else
// 			dup2(pipex->pipe_fd[prev][0], STDIN_FILENO);
//
// 		if (idx == pipex->cmds_count - 1)
// 			dup2(pipex->file_fd[1], STDOUT_FILENO);
// 		else
// 			dup2(pipex->pipe_fd[curr][1], STDOUT_FILENO);
//
// 		// Close both ends of both pipes
// 		close(pipex->pipe_fd[curr][0]);
// 		close(pipex->pipe_fd[curr][1]);
// 		close(pipex->pipe_fd[prev][0]);
// 		close(pipex->pipe_fd[prev][1]);
//
// 		if (pipex->fullpath[idx])
// 			execve(pipex->fullpath[idx], pipex->argv[idx], envp);
// 		else
// 			ft_dprintf(STDERR_FILENO, "%s: command not found\n", *pipex->argv[idx]);
// 		ft_clean_pipex(pipex);
// 		exit(EXIT_FAILURE);
// 	}
// 	else // parent
// 	{
// 		if (idx != 0) {
// 			close(pipex->pipe_fd[prev][0]); // close previous read end
// 			close(pipex->pipe_fd[prev][1]); // close previous write end
// 		}
// 	}
//
// 	return (0);
// }

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (fork_and_pipe(pipex, fd, &pid, idx) != 0)
		return (-1);
	// pipex->pids[idx] = pid;
	if (pid == 0)
	{
		if (pipex->fullpath[idx])
			execve(pipex->fullpath[idx], pipex->argv[idx], envp);
		else
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", *pipex->argv[idx]);
		// ft_error("command not found\n", pipex->argv[idx]);
		ft_clean_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
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
	ft_memset(pipex, 0, sizeof(t_pipex));
	ft_memset(pipex->pipe_fd, -1, sizeof(pipex->pipe_fd));
	ft_check_args(pipex, argc, argv);
	ft_parse_cmds(pipex, argc, argv, envp);
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmds_count);
	if (!pipex->pids)
		return (EXIT_FAILURE);
	while (i < pipex->cmds_count)
	{
		if (spawn_child(pipex, envp, i) != 0)
			return (ft_clean_pipex(pipex), ft_error("", argv), 127);
		i++;
	}
	status = pipex->return_status;
	// i = 0;
	// while (i < pipex->cmds_count)
	// {
	// 	pipex->return_status = wait (NULL);
	// 	i++;
	// }
	return (ft_clean_pipex(pipex), status);
}
