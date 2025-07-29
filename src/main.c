
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
void	ft_error(char *str)
{
	ft_putstr_fd("Pipex: ", STDERR_FILENO);
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_clean_pipex(t_pipex *pipex)
{
	if (pipex->argv)
		ft_free_array(*pipex->argv);
	if (pipex->envp)
		ft_free_array(pipex->envp);
	if (pipex->invalid_input)
		unlink(INVALID_INPUT_PATH);
	if (pipex->here_doc)
		unlink(HERE_DOC_PATH);
	// free(pipex->file_fd);
	// free(pipex->pipe_fd);
	free(pipex);
}

int	fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx)
{
	if (pipe(fd) == -1)
		return (-1);
	*pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0) // only child access here
	{
		if (idx == 0)
			dup2(pipex->file_fd[0], STDIN_FILENO);
		if (idx == pipex->cmds_count -1)
			dup2(pipex->file_fd[1], STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	return (0);
}

int	spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (!fork_and_pipe(pipex, fd, &pid, idx))
		return (-1);
	if (pid == 0)
	{
		if (pipex->fullpath[idx])
			execve(pipex->fullpath[idx], pipex->argv[idx], envp);
		else
			ft_error("pipex:");
		ft_clean_pipex(pipex);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
	}
	return (0);
}

char	**ft_get_env_paths(char **envp)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	command = "PATH";
	while (envp[++i])
	{
		if(ft_strncmp(command, envp[i], ft_strlen(command)) == 0
				&& envp[i][ft_strlen(command)] == '=')
			path = ft_strchr(envp[i], '=') + 1;
		if (!path)
			return (NULL);
	}
	return (ft_split(path, ':'));
}

char	*ft_find_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*full_path;

	if (access(cmd, F_OK) == 0)
		return (ft_substr(cmd, 0, ft_strlen(cmd)));
	paths = ft_get_env_paths(envp);
	if (!paths)
		return (NULL); // might need review
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_array(paths), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (ft_free_array(paths), NULL);
		if (access(full_path, F_OK) == 0)
			return (ft_free_array(paths), full_path);
		// ft_printf("full_path: %s\n", full_path); // TESTING:
		free(full_path);
	}
	return (ft_free_array(paths), NULL);
}

void	ft_parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
    int     i;
    char    **cmd;

    pipex->fullpath = ft_calloc(sizeof(char *), pipex->cmds_count);
    pipex->argv = ft_calloc(sizeof(char **), pipex->cmds_count);
    if (!pipex->fullpath || !pipex->argv)
    {
        ft_free_array(pipex->fullpath);
        ft_free_2d_array(pipex->argv, pipex->cmds_count);
        // return (false);
		return ;
    }

    i = 1 + pipex->here_doc;
    while (++i < argc - 1)
    {
        cmd = ft_split(argv[i], ' ');
        if (!cmd)
        {
            ft_free_array(pipex->fullpath);
            ft_free_2d_array(pipex->argv, i - 2 - pipex->here_doc);
            pipex->fullpath = NULL;
            pipex->argv = NULL;
			return ;
            // return (false);
        }
        pipex->fullpath[i - 2 - pipex->here_doc] = ft_find_path(cmd[0], envp);
        pipex->argv[i - 2 - pipex->here_doc] = cmd;
    }
	return ;
    // return (true);
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
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", STDIN_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex->here_doc = true;
	get_infile(pipex, argv);
	get_outfile(pipex, argc, argv);
	pipex->cmds_count = argc - 3 - pipex->here_doc;
}

// void	ft_init_pipex(t_pipex *pipex, char **argv, char **envp)
// {
// 	ft_memset(pipex, 0, sizeof(t_pipex));
// 	pipex->argv = argv;
// 	pipex->envp = envp;
// }


int main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_memset(pipex, 0, sizeof(t_pipex));
	// ft_init_pipex(&pipex, argv, envp);
	ft_check_args(pipex, argc, argv);
	ft_parse_cmds(pipex, argc, argv, envp);
	while (i < pipex->cmds_count)
	{
		if (!spawn_child(pipex, envp, i))
			return (ft_clean_pipex(pipex), ft_error("pipex: "), 0);
		i++;
	}
	i = 0;
	while (i < pipex->cmds_count)
	{
		wait (NULL);
		i++;
	}
	ft_clean_pipex(pipex);
	return (0);
}
