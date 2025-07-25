/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:26:06 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/25 13:16:55 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locate the first len elements of "little" string inside the "big".
//
// Return:
// "big" if "little" is empty
// "NULL" if "little" is not found
// "*big" to the first char where is found

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	n = 0;
	if (little[0] == 0)
		return ((char *) big);
	while (big[h] && h < len)
	{
		while (big[h + n] == little[n] && big[h + n] && h + n < len)
		{
			n++;
			if (little[n] == 0)
				return ((char *) big + h);
		}
		h++;
		n = 0;
	}
	return (0);
}
