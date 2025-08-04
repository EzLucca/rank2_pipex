/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:08:46 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/04 18:09:00 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

static int	ft_print_base_fd(unsigned long nbr, unsigned int base, char *str,
		int fd)
{
	int	index;
	int	len;
	int	total;

	len = 0;
	total = 0;
	index = nbr % base;
	if (nbr > (base - 1))
	{
		len = ft_print_base_fd(nbr / base, base, str, fd);
		if (len == -1)
			return (-1);
		total += len;
	}
	len = write(fd, &str[index], 1);
	if (len == -1)
		return (-1);
	total += len;
	return (total);
}

int	ft_print_hex_fd(unsigned long hex, int check_upper, int fd)
{
	if (check_upper)
		return (ft_print_base_fd(hex, 16, HEXUP, fd));
	return (ft_print_base_fd(hex, 16, HEXDN, fd));
}

int	ft_print_ptr_fd(void *pointer, int fd)
{
	int	len;
	int	total;

	len = 0;
	total = 0;
	if (!pointer)
		return (ft_print_str("(nil)"));
	len = write(fd, "0x", 2);
	if (len == -1)
		return (-1);
	total += len;
	len = ft_print_hex_fd(((unsigned long)pointer), 0, fd);
	if (len == -1)
		return (-1);
	total += len;
	return ((uintptr_t)total);
}

int	ft_print_unbr_fd(unsigned int unbr, int fd)
{
	return (ft_print_base_fd(unbr, 10, DECIMAL, fd));
}

int	ft_print_snbr_fd(long nbr, int fd)
{
	int	total;
	int	len;

	total = 0;
	len = 0;
	if (nbr == -2147483648)
		return (ft_print_str("-2147483648"));
	if (nbr < 0)
	{
		len = write(fd, "-", 1);
		if (len == -1)
			return (-1);
		total += len;
		nbr = -nbr;
	}
	len = ft_print_base_fd((unsigned long)nbr, 10, DECIMAL, fd);
	if (len == -1)
		return (-1);
	total += len;
	return (total);
}
