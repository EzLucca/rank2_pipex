
#include "../include/pipex.h"

int	ft_exec()
{
	pid_t	pid1;
	pid_t	pid2;
	int fd[2];

	if (pipe(fd) == -1)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0) // only child access here
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve();
	}
	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0) // only child access here
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve();
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	ft_init_pipex(t_pipex *pipex)
{
}

int main()
{
	t_pipex	*pipex;
	ft_init_pipex(pipex);
	ft_check_args();
	ft_parse_cmds();
	ft_parse_args();
	while (cmds)
		ft_exec();
	ft_cleanup();
}
