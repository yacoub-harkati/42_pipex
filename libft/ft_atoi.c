/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:00:20 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/02 10:14:12 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	check_valid_number(size_t number, int sign)
{
	if (number > LLONG_MAX && sign > 0)
		return (-1);
	else if (number > LLONG_MAX && sign < 0)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	size_t				i;
	unsigned long long	number;
	int					sign;

	i = 0;
	sign = 1;
	number = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		number = number * 10 + nptr[i++] - 48;
		if (check_valid_number(number, sign) <= 0)
			return (check_valid_number(number, sign));
	}
	return (number * sign);
}
