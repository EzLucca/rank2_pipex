
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

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (fork_and_pipe(pipex, fd, &pid, idx) != 0)
		return (-1);
	if (pid == 0)
	{
		if (pipex->fullpath[idx])
			execve(pipex->fullpath[idx], pipex->argv[idx], envp);
		else
			ft_error("command not found\n", pipex->argv[idx]);
		ft_clean_pipex(pipex);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_memset(pipex, 0, sizeof(t_pipex));
	ft_check_args(pipex, argc, argv);
	ft_parse_cmds(pipex, argc, argv, envp);
	while (i < pipex->cmds_count)
	{
		if (spawn_child(pipex, envp, i) != 0)
			return (ft_clean_pipex(pipex), ft_error("", argv), 127);
		i++;
	}
	i = 0;
	while (i < pipex->cmds_count)
	{
		wait (NULL);
		i++;
	}
	ft_clean_pipex(pipex);
	return (0);
}
