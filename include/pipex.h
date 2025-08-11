/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:10:05 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/11 17:34:31 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "../lib/libft/include/libft.h"

typedef struct s_pipex
{
	char	**path;
	char	***argv;
	char	**av;
	int		ac;
	int		file_fd[2];
	int		pipe_fd[2];
	int		cmds_count;
	int		return_status;
	int		*pids;
}	t_pipex;

int		wait_processes(pid_t *pid, int cmds_count);
int		spawn_child(t_pipex *pipex, char **envp, int idx);
int		parent_execution(t_pipex *pipex, pid_t *pid, int idx, char **envp);
void	child_execution(t_pipex *pipex, int idx, char **envp);

char	*get_path(char *arg, char **cmd, char **envp);
void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp);
void	ft_init_pipex(t_pipex *pipex, int argc, char **argv);
int		get_files(t_pipex *pipex);
void	handle_error(char *filename);

int		check_paths(char **envp, char **argv);
char	*ft_find_path(char *cmd, char **envp);
char	**ft_get_env_paths(char **envp);

void	ft_free_1d_array(char **array);
void	ft_free_2d_array(char ***array, int n);
void	close_all(t_pipex *pipex);
void	ft_clean_pipex(t_pipex *pipex);
void	ft_clean_exit(t_pipex *pipex);

#endif // !PIPEX_H
