/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:02:49 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/02 10:14:12 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	compute_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	gen_char_array(char *int_str, long number, int len, int sign)
{
	while (number && len--)
	{
		int_str[len + sign] = (number % 10) + 48;
		number /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*int_str;
	long	number;

	number = (long)n;
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		number = -number;
	}
	len = compute_len(number);
	int_str = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (!int_str)
		return (NULL);
	if (sign)
		int_str[0] = '-';
	int_str[len + sign] = '\0';
	gen_char_array(int_str, number, len, sign);
	return (int_str);
}
