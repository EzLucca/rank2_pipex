/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:03 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/25 13:02:10 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Scan n bytes for first instance of c in the memory area pointed by s
// Both c and s are interpreted as unsigned char.

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	instance_c;
	size_t			i;

	string = (unsigned char *)s;
	instance_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (string[i] == instance_c)
			return ((void *)&string[i]);
		i++;
	}
	return (NULL);
}
