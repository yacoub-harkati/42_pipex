/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:07:33 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/02 10:14:12 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	i;
	size_t	old_i;
	size_t	count;

	i = 0;
	old_i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		old_i = i;
		while (s[i] && s[i] != c)
			i++;
		if (old_i < i)
			count++;
	}
	return (count);
}

static size_t	compute_w_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s == c)
		s++;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**free_strs(char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i <= size)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words_count;
	size_t	i;
	size_t	cpd_w;

	if (!s)
		return (NULL);
	i = 0;
	cpd_w = 0;
	words_count = ft_countword(s, c);
	split = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!split)
		return (NULL);
	split[words_count] = NULL;
	while (s[i] && cpd_w < words_count)
	{
		while (s[i] && s[i] == c)
			i++;
		split[cpd_w] = ft_substr(s, i, compute_w_len(s + i, c));
		if (!split[cpd_w++])
			return (free_strs(split, words_count));
		i += compute_w_len(s + i, c);
	}
	return (split);
}
