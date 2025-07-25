/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:06:16 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/08 14:59:50 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_print_base(unsigned long nbr, unsigned int base, char *str)
{
	int	index;
	int	len;
	int	total;

	len = 0;
	total = 0;
	index = nbr % base;
	if (nbr > (base - 1))
	{
		len = ft_print_base(nbr / base, base, str);
		if (len == -1)
			return (-1);
		total += len;
	}
	len = write(1, &str[index], 1);
	if (len == -1)
		return (-1);
	total += len;
	return (total);
}

int	ft_print_hex(unsigned long hex, int check_upper)
{
	if (check_upper)
		return (ft_print_base(hex, 16, HEXUP));
	return (ft_print_base(hex, 16, HEXDN));
}

int	ft_print_ptr(void *pointer)
{
	int	len;
	int	total;

	len = 0;
	total = 0;
	if (!pointer)
		return (ft_print_str("(nil)"));
	len = write(1, "0x", 2);
	if (len == -1)
		return (-1);
	total += len;
	len = ft_print_hex(((unsigned long)pointer), 0);
	if (len == -1)
		return (-1);
	total += len;
	return ((uintptr_t)total);
}

int	ft_print_unbr(unsigned int unbr)
{
	return (ft_print_base(unbr, 10, DECIMAL));
}

int	ft_print_snbr(long nbr)
{
	int	total;
	int	len;

	total = 0;
	len = 0;
	if (nbr == -2147483648)
		return (ft_print_str("-2147483648"));
	if (nbr < 0)
	{
		len = write(1, "-", 1);
		if (len == -1)
			return (-1);
		total += len;
		nbr = -nbr;
	}
	len = ft_print_base((unsigned long)nbr, 10, DECIMAL);
	if (len == -1)
		return (-1);
	total += len;
	return (total);
}
