/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:36 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/02 19:15:04 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_get_env_paths(char **envp)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	command = "PATH";
	path = NULL;
	while (envp[++i])
	{
		if(ft_strncmp(command, envp[i], ft_strlen(command)) == 0
				&& envp[i][ft_strlen(command)] == '=')
		{
			path = ft_strchr(envp[i], '=') + 1;
			break ;
		}
	}
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	*ft_find_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*full_path;

	if (!cmd || !*cmd ||access(cmd, F_OK) == 0)
		return (ft_strdup(""));
	paths = ft_get_env_paths(envp);
	if (!paths)
		return (NULL);
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
		free(full_path);
	}
	return (ft_free_array(paths), NULL);
}
