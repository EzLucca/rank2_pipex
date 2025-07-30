
#include "../include/pipex.h"

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
	// int j = -1;
	// while (pipex->fullpath[++j])
	// 	ft_printf("pipex->fullpath[%d]: %s\n", j, pipex->fullpath[i - 2 - pipex->here_doc]); // TESTING:
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
	if (argc < 5 + pipex->here_doc)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex->here_doc = true;
	get_infile(pipex, argv);
	get_outfile(pipex, argc, argv);
	pipex->cmds_count = argc - 3 - pipex->here_doc;
}
