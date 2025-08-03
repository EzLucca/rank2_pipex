
#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "../lib/libft/include/libft.h"

# define HERE_DOC_PATH ".pipex_here_doc"
# define INVALID_INPUT_PATH ".pipex_invalid"
# define URANDOM_PATH ".pipex_urandom"

typedef struct s_pipex
{
	char	**fullpath;
	char	***argv;
	int		file_fd[2];
	int		pipe_fd[2][2];
	int		cmds_count;
	int		return_status;
	pid_t	*pids;
	bool	here_doc;
	bool	invalid_input;
}	t_pipex;


int		wait_processes(pid_t *pid, int cmds_count);
int		spawn_child(t_pipex *pipex, char **envp, int idx);
int		fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx);
// int		get_outfile(t_pipex *pipex, int argc, char **argv);
// int		get_infile(t_pipex *pipex, char **argv);
int		get_files(t_pipex *pipex, int argc, char **argv);
char	**ft_get_env_paths(char **envp);
char	*ft_find_path(char *cmd, char **envp);
char	*ft_find_path(char *cmd, char **envp);
char	**ft_get_env_paths(char **envp);
void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp);
void	ft_check_args(t_pipex *pipex,int argc, char **argv);
void	ft_clean_pipex(t_pipex *pipex);
// void	ft_error(char *str, char **argv);
void	ft_free_1d_array(char **array);
void	ft_free_2d_array(char ***array, int n);
void	handle_files(char *filename);
void	ft_exit(int code, char *param1, void *param2);

#endif // !PIPEX_H
