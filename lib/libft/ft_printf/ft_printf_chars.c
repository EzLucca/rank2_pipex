/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/08 14:59:40 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static size_t	ft_strlen(const char *s)
{
	int	p;

	p = 0;
	while (*s++)
		++p;
	return (p);
}

int	ft_print_char(char c)
{
	int	bytes;

	bytes = write(1, &c, 1);
	if (bytes == -1)
		return (-1);
	return (bytes);
}

int	ft_print_str(char *s)
{
	int	bytes;

	bytes = 0;
	if (!s)
		return (write(1, "(null)", 6));
	bytes = write(1, s, ft_strlen(s));
	if (bytes == -1)
		return (-1);
	return (bytes);
}
