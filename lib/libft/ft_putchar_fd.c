/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/30 22:50:02 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

// Outputs the character ’c’ to the specified file descriptor.
// File descriptors are int assossiated with an open file or resource

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
