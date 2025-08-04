/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:08:06 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/04 18:09:43 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

int	format_specifier_fd(int fd, const char *format, va_list *arg_ptr)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_putchar_fd(va_arg(*arg_ptr, int), fd);
	else if (*format == 's')
		count += ft_putstr_fd(va_arg(*arg_ptr, char *), fd);
	else if (*format == 'p')
		count += ft_print_ptr_fd(va_arg(*arg_ptr, void *), fd);
	else if (*format == 'd' || *format == 'i')
		count += ft_print_snbr_fd(va_arg(*arg_ptr, int), fd);
	else if (*format == 'u')
		count += ft_print_unbr_fd(va_arg(*arg_ptr, unsigned int), fd);
	else if (*format == 'x' || *format == 'X')
		count += ft_print_hex_fd(va_arg(*arg_ptr, unsigned int),
				*format == 'X', fd);
	else if (*format == '%')
		count += ft_putchar_fd('%', fd);
	if (*format == '\0')
		return (-1);
	return (count);
}

// Check if the format is valid
static int	format_validation(const char *format)
{
	if (ft_strchr(SPECIFIERS, *format) != 0)
		return (1);
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	arg_ptr;
	int		len;
	int		total;

	len = 0;
	total = 0;
	if (!format)
		return (-1);
	va_start(arg_ptr, format);
	while (*format)
	{
		if (*format == '%' && format_validation(format + 1) != 0 && format++)
			len = format_specifier_fd(fd, format, &arg_ptr);
		else
			len = write(fd, format, 1);
		if (len == -1)
			return (-1);
		total += len;
		format++;
	}
	va_end(arg_ptr);
	return (total);
}
