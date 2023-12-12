/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:49:31 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/02 10:14:12 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t_s;
	size_t			i;

	i = 0;
	t_s = (unsigned char *)s;
	while (i < n)
	{
		if (t_s[i] == (unsigned char)c)
			return ((void *)(t_s + i));
		i++;
	}
	return (NULL);
}
