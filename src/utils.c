/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:15:09 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/06 19:10:57 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_1darray(char **array, int n)
{
	int	i;
	int	limit;

	if (!array)
		return ;
	limit = n;
	if (n < 0)
	{
		limit = 0;
		while (array[limit])
			limit++;
	}
	i = 0;
	while (i < limit)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free_2d_array(char ***array, int n)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	if (n == -1)
		while (array[++i])
			ft_free_1darray(array[i], -1);
	else
		while (++i < n)
			if (array[i])
				ft_free_1darray(array[i], -1);
	free(array);
	array = NULL;
}

void	ft_clean_exit(t_pipex *pipex)
{
	ft_clean_pipex(pipex);
	exit(1);
}

void	close_all(t_pipex *pipex)
{
	close(pipex->file_fd[0]);
	close(pipex->file_fd[1]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

void	ft_clean_pipex(t_pipex *pipex)
{
	close(pipex->file_fd[0]);
	close(pipex->file_fd[1]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (pipex->argv)
		ft_free_2d_array(pipex->argv, pipex->cmds_count);
	if (pipex->path)
		ft_free_1darray(pipex->path, pipex->cmds_count);
	if (pipex->pids)
		free(pipex->pids);
	free(pipex);
}
