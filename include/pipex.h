
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
	char	**envp;
	int		file_fd[2];
	int		pipe_fd[2];
	int		cmds_count;
	bool	here_doc;
	bool	invalid_input;
}	t_pipex;


char	**ft_get_env_paths(char **envp);
char	*ft_find_path(char *cmd, char **envp);
#endif // !PIPEX_H

