/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:29:04 by edlucca           #+#    #+#             */
/*   Updated: 2025/06/29 15:12:55 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_append(int fd, char *buffer, char *tmp_buf, ssize_t bytes)
{
	char	*new_buffer;

	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, tmp_buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		tmp_buf[bytes] = '\0';
		new_buffer = ft_strjoin(buffer, tmp_buf);
		if (!new_buffer)
		{
			free (buffer);
			return (NULL);
		}
		free (buffer);
		buffer = new_buffer;
	}
	return (buffer);
}

static char	*read_from_file(int fd, char *buffer)
{
	char	*tmp_buf;
	char	*result;
	ssize_t	bytes;

	tmp_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buf)
		return (NULL);
	bytes = 1;
	result = read_and_append(fd, buffer, tmp_buf, bytes);
	free (tmp_buf);
	return (result);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_substr(buffer, 0, i + 1);
	else
		line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*rest_of_line;
	char	*newline_ptr;
	size_t	rest_len;

	newline_ptr = ft_strchr(buffer, '\n');
	if (!newline_ptr)
	{
		free(buffer);
		return (NULL);
	}
	rest_len = ft_strlen(newline_ptr + 1);
	rest_of_line = ft_substr(newline_ptr + 1, 0, rest_len);
	if (!rest_of_line)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (rest_of_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	buffer[fd] = read_from_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}
