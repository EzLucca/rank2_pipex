/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:09 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/23 19:06:02 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

// Outputs the string ’s’ to the specified file descriptor.
// return ; just exit the function

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}
