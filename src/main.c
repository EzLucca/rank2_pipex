
#include "../include/pipex.h"

// int	ft_exec()
// {
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int fd[2];
//
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0) // only child access here
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve();
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (2);
// 	if (pid2 == 0) // only child access here
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve();
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }

void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
}

int	get_infile(t_pipex *pipex, char **argv)
{
	if (access(argv[1], F_OK) == -1)
	{
		perror("infile");
		pipex->file_fd[0] = open(INVALID_INPUT_PATH, O_RDONLY | O_CREAT, 0644);
		pipex->invalid_input = true;
	}
	else
		pipex->file_fd[0] = open(argv[1], O_RDONLY);
	return (1);
}

int	get_outfile(t_pipex *pipex, int argc, char **argv)
{
	if (pipex->here_doc)
		pipex->file_fd[1] = open(argv[4], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		pipex->file_fd[1] = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->file_fd[1] == -1)
	{
		perror("outfile");
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	ft_check_args(t_pipex *pipex,int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", STDIN_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex->here_doc = true;
	get_infile(pipex, argv);
	get_outfile(pipex, argc, argv);
}

void	ft_init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	ft_memset(pipex, 0, sizeof(t_pipex));
	pipex->argv = argv;
	pipex->envp = envp;
}

void	ft_clean_pipex(t_pipex *pipex)
{
	// if (pipex->argv)
	// 	ft_free_array(pipex->argv);
	// if (pipex->envp)
	// 	ft_free_array(pipex->envp);
	if (pipex->invalid_input)
		unlink(INVALID_INPUT_PATH);
	if (pipex->here_doc)
		unlink(HERE_DOC_PATH);
	free(pipex->file_fd);
	free(pipex->pipe_fd);
	free(pipex);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_init_pipex(&pipex, argv, envp);
	ft_check_args(&pipex, argc, argv);
	ft_parse_cmds(&pipex, argc, argv, envp);
	// ft_parse_args();
	// while (cmds)
	// 	ft_exec();
	ft_clean_pipex(&pipex);
	return (0);
}
