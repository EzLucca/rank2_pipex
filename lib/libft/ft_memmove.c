/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:21:52 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/26 20:51:42 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies n bytes from src to dest. It uses a temporary array between the copy. 
// The memory areas may overlap: copying takes place as though the bytes
// in  src are first copied into a temporary array that does not overlap src or
// dest, and the bytes are then copied from the temporary array to dest.
// The memmove() function returns a pointer to dest.
// Forward copy: no overlap or dest before src
// Backward copy: overlapping regions, dest after src

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;
	size_t				i;

	tmp_src = (const unsigned char *) src;
	tmp_dst = (unsigned char *) dest;
	i = 0;
	if (tmp_dst < tmp_src)
	{
		while (i < n)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			tmp_dst[n] = tmp_src[n];
	}
	return (dest);
}
