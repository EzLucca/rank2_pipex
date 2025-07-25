/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:30:59 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/26 20:02:42 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

// Fill the n bytes of the memory area pointed by s with the constant type c
// The memset() function returns a pointer to the memory area s.
// The casting on the void * ensure the type of unsigned char *
// The char is used to be byte by byte.

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp_ptr;

	temp_ptr = (unsigned char *) s;
	while (n > 0)
	{
		(*temp_ptr++) = (unsigned char) c;
		n--;
	}
	return (s);
}
