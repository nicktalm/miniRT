/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:30:10 by lbohm             #+#    #+#             */
/*   Updated: 2024/07/31 15:26:15 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *word, int letter)
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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
