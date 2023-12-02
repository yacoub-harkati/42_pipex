/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:48:21 by yaharkat          #+#    #+#             */
/*   Updated: 2023/11/01 15:16:19 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s[s_len] == (const char)c)
		return ((char *)(s + s_len));
	while (s_len--)
	{
		if (s[s_len] == (const char)c)
			return ((char *)(s + s_len));
	}
	return (NULL);
}
