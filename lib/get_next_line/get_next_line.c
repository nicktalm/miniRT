/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:35:26 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/28 15:07:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	int			byt_size;
	char		*finishline;

	byt_size = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer, &byt_size);
	if (byt_size == -1)
		buffer = freeup(buffer);
	if (!(buffer))
		return (NULL);
	finishline = clean_buffer(buffer);
	buffer = next_line(buffer);
	return (finishline);
}

char	*read_file(int fd, char *buffer, int *byt_size)
{
	char	*newline;

	newline = (char *)malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!(newline))
		return (freeup(buffer));
	while (*byt_size > 0)
	{
		*byt_size = read(fd, newline, BUFFER_SIZE);
		if (*byt_size <= 0)
		{
			free(newline);
			break ;
		}
		newline[*byt_size] = '\0';
		buffer = strjoin(buffer, newline);
		if (ft_strchr_g(newline, '\n'))
		{
			free(newline);
			break ;
		}
	}
	return (buffer);
}

char	*strjoin(char *buffer, char *newline)
{
	char	*str;
	int		i;
	int		j;

	if (!buffer)
	{
		buffer = (char *)malloc (1 * sizeof(char));
		if (!(buffer))
			return (NULL);
		buffer[0] = '\0';
	}
	if (!(buffer) || !(newline))
		return (NULL);
	str = malloc((ft_len(buffer) + ft_len(newline) + 1) * sizeof(char));
	if (!(str))
		return (freeup(buffer));
	i = -1;
	while (buffer[++i])
		str[i] = buffer[i];
	j = -1;
	while (newline[++j])
		str[i + j] = newline[j];
	str[i + j] = '\0';
	free(buffer);
	return (str);
}

char	*clean_buffer(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!(buffer))
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = (char *)malloc ((i + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	str[i] = '\0';
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i] = buffer[i];
	return (str);
}

char	*next_line(char *buffer)
{
	char	*nextline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(buffer))
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!(buffer[i]) || !(buffer[i + 1]))
		return (freeup(buffer));
	nextline = (char *)malloc ((ft_len(buffer) - i + 1) * sizeof(char));
	if (!(nextline))
		return (freeup(buffer));
	i++;
	j = 0;
	while (buffer[i])
		nextline[j++] = buffer[i++];
	nextline[j] = '\0';
	free(buffer);
	return (nextline);
}
