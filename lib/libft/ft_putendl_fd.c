/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:14 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/23 19:06:06 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

// Outputs the string ’s’ to the specified file descriptor followed by a newline

int	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return (0);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	return (1);
}
