/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:40:42 by yaharkat          #+#    #+#             */
/*   Updated: 2023/11/01 21:47:36 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp_buffer;
	size_t			i;

	i = 0;
	temp_buffer = (unsigned char *)s;
	while (i < n)
	{
		temp_buffer[i] = c;
		i++;
	}
	return (s);
}
