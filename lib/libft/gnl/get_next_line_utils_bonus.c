/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:00:41 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/18 18:32:59 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	p;

	if (!s)
		return (0);
	p = 0;
	while (s[p])
		p++;
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	c = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*tmp_dst;
	const unsigned char		*tmp_src;

	if (!dest || !src)
		return (NULL);
	tmp_dst = (unsigned char *) dest;
	tmp_src = (const unsigned char *) src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*string;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		string = malloc(1);
		if (!string)
			return (NULL);
		string[0] = '\0';
		return (string);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	string = malloc(len + 1);
	if (!string)
		return (NULL);
	ft_memcpy(string, s + start, len);
	string[len] = '\0';
	return (string);
}

char	*ft_strjoin(char *buffer, char *tmp_buf)
{
	int		s1_len;
	int		s2_len;
	char	*string;

	s1_len = 0;
	s2_len = 0;
	while (buffer[s1_len])
		s1_len++;
	while (tmp_buf[s2_len])
		s2_len++;
	string = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_memcpy(string, buffer, s1_len);
	ft_memcpy(string + s1_len, tmp_buf, s2_len);
	string[s1_len + s2_len] = '\0';
	return (string);
}
