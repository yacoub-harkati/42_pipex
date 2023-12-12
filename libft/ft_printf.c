/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:03:08 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 14:27:13 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_putnbr_base(size_t nbr, char *base, int fd)
{
	size_t	base_len;
	int		count;

	count = 0;
	base_len = ft_strlen(base);
	if (nbr >= base_len)
		count += ft_putnbr_base(nbr / base_len, base, fd);
	count += ft_putchar_fd(base[nbr % base_len], fd);
	return (count);
}

static int	ft_print_pointer(unsigned long long n, int fd)
{
	int	count;

	if (((void *)n) == ((void *)0))
		return (ft_putstr_fd("(nil)", fd));
	count = 0;
	count += ft_putstr_fd("0x", fd);
	count += ft_putnbr_base(n, HEX, fd);
	return (count);
}

static int	proccess_conversion(char c, va_list list, int fd)
{
	int	count;

	count = 0;
	if (c == 'c')
		return (ft_putchar_fd(va_arg(list, int), fd));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(list, char *), fd));
	else if (c == 'p')
		return (ft_print_pointer(va_arg(list, size_t), fd));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(list, long), fd));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(list, unsigned int), "0123456789", fd));
	else if (c == 'x')
		return ((ft_putnbr_base(va_arg(list, unsigned int), HEX, fd)));
	else if (c == 'X')
		return ((ft_putnbr_base(va_arg(list, unsigned int), MHEX, fd)));
	else if (c == '%')
		return (ft_putchar_fd('%', fd));
	return (count);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	list;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!s)
		return (-1);
	va_start(list, s);
	while (s[i])
	{
		if (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]))
		{
			count += proccess_conversion(s[i + 1], list, fd);
			i++;
		}
		else
			count += ft_putchar_fd(s[i], fd);
		i++;
	}
	va_end(list);
	return (count);
}
