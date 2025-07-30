
#include "../include/ft_printf.h"
#include "../include/libft.h"

int	format_specifier(int fd, const char *format, va_list *arg_ptr)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += (size_t)ft_putchar_fd(va_arg(*arg_ptr, int), fd);
	else if (*format == 's')
		count += ft_print_str(va_arg(*arg_ptr, char *));
	else if (*format == 'p')
		count += ft_print_ptr(va_arg(*arg_ptr, void *));
	else if (*format == 'd' || *format == 'i')
		count += ft_print_snbr(va_arg(*arg_ptr, int));
	else if (*format == 'u')
		count += ft_print_unbr(va_arg(*arg_ptr, unsigned int));
	else if (*format == 'x' || *format == 'X')
		count += ft_print_hex(va_arg(*arg_ptr, unsigned int), *format == 'X');
	else if (*format == '%')
		count += ft_print_char('%');
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
			len = format_specifier(fd, format,&arg_ptr);
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
