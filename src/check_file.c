/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:46:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/30 13:30:58 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	print_struct(t_data *data)
{
	printf("Ambient\n");
	printf("data.set.ambient.ratio: %f\n", data->set.ambient.ratio);
	printf("data.set.ambient.color.x: %f\n", data->set.ambient.color.x);
	printf("data.set.ambient.color.y: %f\n", data->set.ambient.color.y);
	printf("data.set.ambient.color.z: %f\n", data->set.ambient.color.z);
	printf("\n\n");
	printf("Camera\n");
	printf("data.set.cam.coords.x: %f\n", data->set.cam.coords.x);
	printf("data.set.cam.coords.y: %f\n", data->set.cam.coords.y);
	printf("data.set.cam.coords.z: %f\n", data->set.cam.coords.z);
	printf("data.set.cam.normalized.x: %f\n", data->set.cam.normalized.x);
	printf("data.set.cam.normalized.y: %f\n", data->set.cam.normalized.y);
	printf("data.set.cam.normalized.z: %f\n", data->set.cam.normalized.z);
	printf("data.set.cam.fov: %d\n", data->set.cam.fov);
	printf("\n\n");
	printf("Light\n");
	printf("data.set.light.coords.x: %f\n", data->set.light.coords.x);
	printf("data.set.light.coords.y: %f\n", data->set.light.coords.y);
	printf("data.set.light.coords.z: %f\n", data->set.light.coords.z);
	printf("data.set.light.brightness: %f\n", data->set.light.brightness);
	printf("data.set.light.color.x: %f\n", data->set.light.color.x);
	printf("data.set.light.color.y: %f\n", data->set.light.color.y);
	printf("data.set.light.color.z: %f\n", data->set.light.color.z);
	printf("\n\n");
	printf("\033[1;31mSphere\033[0m\n\n");
	for (int i = 0; i < data->set.sp_count; i++)
	{
		printf("\033[0;31mSphere %d\033[0m\n", i);
		printf("\033[0;31mdata.set.sp[%d].coords.x: %f\033[0m\n", i, data->set.sp[i].coords.x);
		printf("\033[0;31mdata.set.sp[%d].coords.y: %f\033[0m\n", i, data->set.sp[i].coords.y);
		printf("\033[0;31mdata.set.sp[%d].coords.z: %f\033[0m\n", i, data->set.sp[i].coords.z);
		printf("\033[0;31mdata.set.sp[%d].diameter: %f\033[0m\n", i, data->set.sp[i].diameter);
		printf("\033[0;31mdata.set.sp[%d].color.x: %f\033[0m\n", i, data->set.sp[i].color.x);
		printf("\033[0;31mdata.set.sp[%d].color.y: %f\033[0m\n", i, data->set.sp[i].color.y);
		printf("\033[0;31mdata.set.sp[%d].color.z: %f\033[0m\n", i, data->set.sp[i].color.z);
	}
	printf("\n\n");
	printf("\033[0;32mPlane\033[0m\n\n");
	for (int i = 0; i < data->set.pl_count; i++)
	{
		printf("\033[0;32mPlane %d\033[0m\n", i);
		printf("\033[0;32mdata.set.pl[%d].coords.x: %f\033[0m\n", i, data->set.pl[i].coords.x);
		printf("\033[0;32mdata.set.pl[%d].coords.y: %f\033[0m\n", i, data->set.pl[i].coords.y);
		printf("\033[0;32mdata.set.pl[%d].coords.z: %f\033[0m\n", i, data->set.pl[i].coords.z);
		printf("\033[0;32mdata.set.pl[%d].normalized.x: %f\033[0m\n", i, data->set.pl[i].normalized.x);
		printf("\033[0;32mdata.set.pl[%d].normalized.y: %f\033[0m\n", i, data->set.pl[i].normalized.y);
		printf("\033[0;32mdata.set.pl[%d].normalized.z: %f\033[0m\n", i, data->set.pl[i].normalized.z);
		printf("\033[0;32mdata.set.pl[%d].color.x: %f\033[0m\n", i, data->set.pl[i].color.x);
		printf("\033[0;32mdata.set.pl[%d].color.y: %f\033[0m\n", i, data->set.pl[i].color.y);
		printf("\033[0;32mdata.set.pl[%d].color.z: %f\033[0m\n", i, data->set.pl[i].color.z);
	}
	printf("\n\n");
	printf("\033[0;34mCylinder\033[0m\n\n");
	for (int i = 0; i < data->set.cy_count; i++)
	{
		printf("\033[0;34mCylinder %d\033[0m\n", i);
		printf("\033[0;34mdata.set.cy[%d].coords.x: %f\033[0m\n", i, data->set.cy[i].coords.x);
		printf("\033[0;34mdata.set.cy[%d].coords.y: %f\033[0m\n", i, data->set.cy[i].coords.y);
		printf("\033[0;34mdata.set.cy[%d].coords.z: %f\033[0m\n", i, data->set.cy[i].coords.z);
		printf("\033[0;34mdata.set.cy[%d].normalized.x: %f\033[0m\n", i, data->set.cy[i].normalized.x);
		printf("\033[0;34mdata.set.cy[%d].normalized.y: %f\033[0m\n", i, data->set.cy[i].normalized.y);
		printf("\033[0;34mdata.set.cy[%d].normalized.z: %f\033[0m\n", i, data->set.cy[i].normalized.z);
		printf("\033[0;34mdata.set.cy[%d].diameter: %f\033[0m\n", i, data->set.cy[i].diameter);
		printf("\033[0;34mdata.set.cy[%d].height: %f\033[0m\n", i, data->set.cy[i].height);
		printf("\033[0;34mdata.set.cy[%d].color.x: %f\033[0m\n", i, data->set.cy[i].color.x);
		printf("\033[0;34mdata.set.cy[%d].color.y: %f\033[0m\n", i, data->set.cy[i].color.y);
		printf("\033[0;34mdata.set.cy[%d].color.z: %f\033[0m\n", i, data->set.cy[i].color.z);
	}
}

int	read_lines_from_file(int fd, char ***line, char *argv)
{
	int		rows;
	int		i;

	rows = 0;
	while (get_next_line(fd))
		rows++;
	close(fd);
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
	print_struct(data);
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
		error("File not found");
	if (rt_file_check(argv))
		error("Wrong file format");
	if (process_rt_file(fd, data, argv))
		return (0);
	return (1);
}
