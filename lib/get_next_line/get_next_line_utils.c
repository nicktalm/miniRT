/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:30:10 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/28 15:08:12 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_g(const char *word, int letter)
{
	int	i;

	i = 0;
	if (!(word))
		return (NULL);
	while (word[i] != (char)letter)
	{
		if (word[i] == '\0')
			return (0);
		i++;
	}
	if (letter == '\0')
		return ((char *)(word + i));
	return ((char *)(word + i));
}

size_t	ft_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy_g(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		len;

	i = 0;
	len = ft_len(src);
	if (size == 0)
		return (len);
	while ((size - 1) > i && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*freeup(char *buffer)
{
	if (buffer)
		free(buffer);
	return (NULL);
}
