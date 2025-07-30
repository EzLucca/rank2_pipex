
#include "../include/pipex.h"

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
	// i = -1;
	// while (paths[++i])
	// 	ft_printf("paths: %s\n", paths[i]); // TESTING:
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
