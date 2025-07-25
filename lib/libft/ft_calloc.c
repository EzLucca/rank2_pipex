/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:18:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/25 13:29:45 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Create memory allocation with "size" bytes filled with 0 
// If nb_bytes overflows it should have a different value (!=) will be true
// The calloc() function allocates memory for an array  of  nmemb  elements  of
// size  bytes  each and returns a pointer to the allocated memory.  
// The memory is set to zero.  
// If nmemb or size is 0, then calloc() returns  either  NULL,
// or  a  unique pointer value that can later be successfully passed to free().
// If the multiplication of nmemb and size would result  in  integer  overflow,
// then  calloc() returns an error.  By contrast, an integer overflow would not

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;
	size_t	nb_bytes;

	nb_bytes = nmemb * size;
	if (size && (nb_bytes / size) != nmemb)
		return (NULL);
	tmp = malloc(nb_bytes);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nb_bytes);
	return (tmp);
}
