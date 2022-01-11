/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 06:43:47 by dmillan           #+#    #+#             */
/*   Updated: 2022/01/11 08:12:51 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(char **buffer_read, char **line)
{
	size_t	i;
	char	*buffer_new;

	i = 0;
	buffer_new = NULL;
	while ((*(*buffer_read + i) != '\n') && (*(*buffer_read + i) != '\0'))
		i++;
	if (*(*buffer_read + i) == '\n')
	{
		i++;
		*line = ft_substr(*buffer_read, 0, i);
		buffer_new = ft_strdup(*buffer_read + i);
	}
	else
		*line = ft_strdup(*buffer_read);
	free(*buffer_read);
	*buffer_read = NULL;
	return (buffer_new);
}

ssize_t	ft_read_file(int fd, char **buffer, char **buffer_read, char **line)
{
	char	*tmp;
	ssize_t	n;

	n = 1;
	while (n && !ft_strchr(*buffer_read, '\n'))
	{
		n = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[n] = '\0';
		tmp = *buffer_read;
		*buffer_read = ft_strjoin(tmp, *buffer);
		free (tmp);
	}
	free(*buffer);
	*buffer = NULL;
	*buffer_read = ft_read_line(buffer_read, line);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*buffer_read;
	char		*buffer;
	char		*line;
	ssize_t		n;

	buffer_read = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!buffer_read)
		buffer_read = ft_strdup("");
	n = ft_read_file(fd, &buffer, &buffer_read, &line);
	if (n == 0 && !line)
		return (NULL);
	return (line);
}
