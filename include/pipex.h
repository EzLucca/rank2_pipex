
#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"

# define HERE_DOC_PATH ".pipex_here_doc"
# define INVALID_INPUT_PATH ".pipex_invalid"
# define URANDOM_PATH ".pipex_urandom"

typedef struct s_pipex
{
	char	**fullpath;
	char	***argv;
	int		file_fd[2];
	int		pipe_fd[2];
	int		cmds_count;
	bool	here_doc;
	bool	invalid_input;
}	t_pipex;


int		spawn_child(t_pipex *pipex, char **envp, int idx);
int		fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx);
int		get_outfile(t_pipex *pipex, int argc, char **argv);
int		get_infile(t_pipex *pipex, char **argv);
char	**ft_get_env_paths(char **envp);
char	*ft_find_path(char *cmd, char **envp);
char	*ft_find_path(char *cmd, char **envp);
char	**ft_get_env_paths(char **envp);
void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp);
void	ft_check_args(t_pipex *pipex,int argc, char **argv);
void	ft_clean_pipex(t_pipex *pipex);
void	ft_error(char *str, char **argv);
void	ft_free_2d_array(char ***array, int n);

#endif // !PIPEX_H

