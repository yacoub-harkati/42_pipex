/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:32:29 by yaharkat          #+#    #+#             */
/*   Updated: 2023/11/13 22:24:09 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	buffer = malloc(nmemb * size);
	if (buffer)
		ft_bzero(buffer, nmemb * size);
	return (buffer);
}
