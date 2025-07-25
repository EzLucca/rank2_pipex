/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:15:00 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/26 21:48:39 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
// Transform a string into an int
// Behaviour is the same as strtol() but atoi don't detect errors.
//
// Return:
// The converted value or 0 on error.

int	ft_atoi(const char *nptr)
{
	long	number;
	int		sign;

	number = 0;
	sign = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' '))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10 + (*nptr - '0');
		if (sign == 1 && number < 0)
			return (-1);
		else if (sign == -1 && number < 0)
			return (0);
		nptr++;
	}
	return ((int)(number * sign));
}

int	ft_atoi_base(const char *nptr, const char *base)
{
	int	neg;
	int	result;
	int	nbase;	

	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r')
		nptr++;
	neg = 1;
	if (*nptr == '-')
	{
		neg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	nbase = ft_strlen(base);
	result = 0;
	while (nptr && *nptr && ft_strchr(base, *nptr))
	{
		result = result * nbase + ft_strchr(base, *nptr) - base;
		nptr++;
	}
	return (neg * result);
}
