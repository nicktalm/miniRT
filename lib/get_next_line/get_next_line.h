/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:06:13 by lbohm             #+#    #+#             */
/*   Updated: 2024/07/31 15:26:29 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_file(int fd, char *buffer, int *byt_size);
char	*strjoin(char *newline, char *buffer);
char	*clean_buffer(char *buffer);
char	*next_line(char *buffer);
char	*ft_strchr(const char *word, int letter);
size_t	ft_len(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*freeup(char *buffer);

#endif