/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:42:36 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/25 14:42:41 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

// Outputs the integer ’n’ to the specified file descriptor.

int	ft_putnbr_fd(int n, int fd)
{
	int	value;

	value = 0;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		value = n % 10 + 48;
		write(fd, &value, 1);
	}
	return (1);
}
