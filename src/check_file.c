/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:46:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/26 16:49:45 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	read_file(int fd)
{

}

int	rt_file(char *argv)
{
	int	len;

	len = ft_strlen(argv) - 3;
	if (len > 3)
		return (ft_strncmp(argv + len, ".rt", 3));
	return (1);
}

int	open_file(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		printf("Error\n");
	if (!rt_file(argv))
		printf("Error\n");
	if (read_file(fd))
		return (0);
	return (1);
}
