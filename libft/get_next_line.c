/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:59:16 by yaharkat          #+#    #+#             */
/*   Updated: 2023/12/09 16:19:54 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*get_clean_line(char *buffer)
{
	int	i;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	return (ft_substr(buffer, 0, i + 1));
}

char	*get_rest(char *s)
{
	char	*rest;
	int		i;
	int		len;

	i = 0;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	len = ft_strlen(&s[i]) + 1;
	rest = (char *)malloc(sizeof(char) * len);
	ft_strlcpy(rest, s + i, len);
	free(s);
	return (rest);
}

char	*initisalize_buffer(void)
{
	char	*buffer;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}

char	*read_line_lines(char *buffer, char *line, int fd, ssize_t *bytes_read)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	*bytes_read = read(fd, line, BUFFER_SIZE);
	if (*bytes_read < 0)
	{
		free(buffer);
		free(line);
		return (NULL);
	}
	line[*bytes_read] = '\0';
	buffer = ft_strjoin(buffer, line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line[2];
	static char	*buffer[1024];
	ssize_t		bytes_read;

	line[0] = initisalize_buffer();
	if (line[0] == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(line[0]);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(line[0], '\n'))
	{
		buffer[fd] = read_line_lines(buffer[fd], line[0], fd, &bytes_read);
		if (!buffer[fd])
			return (NULL);
	}
	line[1] = get_clean_line(buffer[fd]);
	buffer[fd] = get_rest(buffer[fd]);
	free(line[0]);
	return (line[1]);
}
