/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:15:09 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/02 20:16:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_1darray(char **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

void	ft_free_2d_array(char ***array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			ft_free_1darray(array[i], -1);
	else
		while (++i < n)
			if (array[i])
				ft_free_1darray(array[i], -1);
	free(array);
}

void	ft_exit(int code, char *param1, void *param2)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)param2;
	ft_clean_pipex(pipex);
	if (param1)
	{
		if (code == 21 && ft_strchr(param1, '/'))
			ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", param1);
		else if (code == 127)
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", param1);
		else
			ft_dprintf(STDERR_FILENO, "%s\n", param1);
	}
	exit(code);
}

void	ft_clean_pipex(t_pipex *pipex)
{

	if (pipex->file_fd[0] != -1)
		close(pipex->file_fd[0]);
	if (pipex->file_fd[1] != -1)
		close(pipex->file_fd[1]);
	if (pipex->argv)
		ft_free_2d_array(pipex->argv, pipex->cmds_count);
	if (pipex->fullpath)
		ft_free_1darray(pipex->fullpath, pipex->cmds_count);
	if (pipex->pids)
		free(pipex->pids);
	// if (pipex->envp)
	// 	ft_free_array(pipex->envp);
	if (pipex->invalid_input)
		unlink(INVALID_INPUT_PATH);
	// ft_memset(pipex, 0, sizeof(t_pipex));
	free(pipex);
}

void	handle_files(char *filename)
{

	if (errno == EISDIR)
		ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", filename);
	else if (errno == ENOTDIR)
		ft_dprintf(STDERR_FILENO, "pipex: %s: Not a directory\n", filename);
	else if (errno == EACCES)
		ft_dprintf(STDERR_FILENO, "pipex: %s: Permission denied\n", filename);
	else if (errno == ENOENT)
		ft_dprintf(STDERR_FILENO, "pipex: %s: No such file or directory\n", filename);
	else
		ft_dprintf(STDERR_FILENO, "pipex: %s: Error opening\n", filename);
	// ft_clean_pipex(pipex);
	// exit(errno);
}
