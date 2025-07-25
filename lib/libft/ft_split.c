/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:20 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/08 14:35:37 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

//This should return the len of the substring
static int	substr_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

//This function count the word of the string
int	count_tokens(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += substr_len(s, c);
		}
		else
			s++;
	}
	return (count);
}

//Free every array if one of them are not properly allocated
static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

//Split the string in substring
char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	arr = ft_calloc(count_tokens(s, c) + 1, sizeof(char *));
	if (!s || !(arr))
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = substr_len(s, c);
			arr[i] = ft_substr(s, 0, len);
			if (!arr[i])
				return (free_array(arr));
			s += len;
			i++;
		}
		else
			s++;
	}
	return (arr[i] = NULL, arr);
}
