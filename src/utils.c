
#include "../include/pipex.h"

void	ft_free_2d_array(char ***array)
{
	if (!array || !*array)
		return ;

	ft_free_array(*array);
	*array = NULL;
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
		ft_free_2d_array(pipex->argv);
	if (pipex->fullpath)
		ft_free_array(pipex->fullpath);
	if (pipex->pids)
		free(pipex->pids);
	// if (pipex->envp)
	// 	ft_free_array(pipex->envp);
	if (pipex->invalid_input)
		unlink(INVALID_INPUT_PATH);
	// ft_memset(pipex, 0, sizeof(t_pipex));
}
