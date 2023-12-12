/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:21:40 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/02 10:14:12 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	find_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static size_t	find_end(char const *s1, char const *set, size_t start)
{
	size_t	last_i;

	last_i = ft_strlen(s1) - 1;
	while (last_i > start && ft_strchr(set, s1[last_i]))
		last_i--;
	return (last_i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	length;
	char	*buffer;

	if (!s1 || !set || !*s1)
		return (ft_strdup(""));
	start = find_start(s1, set);
	end = find_end(s1, set, start);
	if (start > end)
		return (ft_strdup(""));
	length = end - start + 1;
	buffer = (char *)malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, (s1 + start), (length + 1));
	return (buffer);
}
