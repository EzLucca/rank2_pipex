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

void	ft_error(char *str, char **argv)
{
	ft_putstr_fd(*argv, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(str);
	exit(EXIT_FAILURE);
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
