/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:46:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/10 17:39:49 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	count_rows(int fd)
{
	char	*str;
	int		rows;

	rows = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		free(str);
		str = get_next_line(fd);
		rows++;
	}
	close(fd);
	return (rows);
}

int	read_lines_from_file(int fd, char ***line, char *argv)
{
	int		rows;
	int		i;

	rows = count_rows(fd);
	*line = malloc(sizeof(char *) * (rows + 1));
	if (!*line)
		return (-1);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	while (i < rows)
	{
		(*line)[i] = get_next_line(fd);
		if (!(*line)[i])
			break ;
		(*line)[i] = clean_line((*line)[i]);
		i++;
	}
	line[0][i] = NULL;
	close(fd);
	return (0);
}

int	process_rt_file(int fd, t_data *data, char *argv)
{
	char	**line;
	int		result;
	int		i;

	result = read_lines_from_file(fd, &line, argv);
	if (result < 0)
		return (result);
	ft_count(data, line);
	i = 0;
	while (line[i] != NULL)
	{
		parse_line(data, &line[i]);
		i++;
	}
	i = 0;
	while (line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
	return (0);
}

int	rt_file_check(char *argv)
{
	int	len;

	len = ft_strlen(argv) - 3;
	if (len > 3)
		return (ft_strncmp(argv + len, ".rt", 3));
	return (1);
}

int	open_file(char *argv, t_data *data)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error("File not found", data);
	if (rt_file_check(argv))
		error("Wrong file format", data);
	if (process_rt_file(fd, data, argv))
		return (0);
	return (1);
}
