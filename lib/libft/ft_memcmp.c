/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:23:33 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/25 13:05:29 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compares the first n bytes (as unsigned char) of the memory areas s1 and s2.
// The memcmp() function returns an integer less than, equal to, or  greater
// than  zero  if  the first  n bytes of s1 is found, respectively,
// to be less than, to match, or be greater than the first n bytes of s2.
//
// For a nonzero return value, the sign is determined by the sign of the
// difference  between  the first pair of bytes (interpreted as unsigned char)
// that differ in s1 and s2.
//
// If n is zero, the return value is zero.

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((str1[i] > str2[i]) - (str1[i] < str2[i]));
		i++;
	}
	return (0);
}
