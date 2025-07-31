
#include "../include/pipex.h"

void	ft_free_2d_array(char ***array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			ft_free_array(array[i]);
	else
		while (++i < n)
			if (array[i])
				ft_free_array(array[i]);
	free(array);
}

void	ft_error(char *str, char **argv)
{
	ft_putstr_fd(*argv, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_clean_pipex(t_pipex *pipex)
{
	if (pipex->argv)
		ft_free_array(*pipex->argv);
	if (pipex->fullpath)
		ft_free_2d_array(&pipex->fullpath, sizeof(pipex->cmds_count));
	if (pipex->pids)
		free(pipex->pids);
	// if (pipex->envp)
	// 	ft_free_array(pipex->envp);
	if (pipex->invalid_input)
		unlink(INVALID_INPUT_PATH);
	if (pipex->here_doc)
		unlink(HERE_DOC_PATH);
	// free(pipex->file_fd);
	// free(pipex->pipe_fd);
	// free(pipex);
	ft_memset(pipex, 0, sizeof(t_pipex));
}
