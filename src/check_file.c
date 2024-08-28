/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:46:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/28 11:28:15 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	print_struct(t_data *data, int sphere_count, int plane_count, int cylinder_count)
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
	int j = 0;
	while (sphere_count > j)
	{
		printf("Sphere %d\n", j + 1);
		printf("data.set.sp[%d].coords.x: %f\n", j, data->set.sp[j].coords.x);
		printf("data.set.sp[%d].coords.y: %f\n", j, data->set.sp[j].coords.y);
		printf("data.set.sp[%d].coords.z: %f\n", j, data->set.sp[j].coords.z);
		printf("data.set.sp[%d].diameter: %f\n", j, data->set.sp[j].diameter);
		printf("data.set.sp[%d].color.x: %f\n", j, data->set.sp[j].color.x);
		printf("data.set.sp[%d].color.y: %f\n", j, data->set.sp[j].color.y);
		printf("data.set.sp[%d].color.z: %f\n", j, data->set.sp[j].color.z);
		printf("\n\n");
		j++;
	}
	j = 0;
	while (plane_count > j)
	{
		printf("Plane %d\n", j + 1);
		printf("data.set.pl[%d].coords.x: %f\n", j, data->set.pl[j].coords.x);
		printf("data.set.pl[%d].coords.y: %f\n", j, data->set.pl[j].coords.y);
		printf("data.set.pl[%d].coords.z: %f\n", j, data->set.pl[j].coords.z);
		printf("data.set.pl[%d].normalized.x: %f\n", j, data->set.pl[j].normalized.x);
		printf("data.set.pl[%d].normalized.y: %f\n", j, data->set.pl[j].normalized.y);
		printf("data.set.pl[%d].normalized.z: %f\n", j, data->set.pl[j].normalized.z);
		printf("data.set.pl[%d].color.x: %f\n", j, data->set.pl[j].color.x);
		printf("data.set.pl[%d].color.y: %f\n", j, data->set.pl[j].color.y);
		printf("data.set.pl[%d].color.z: %f\n", j, data->set.pl[j].color.z);
		printf("\n\n");
		j++;
	}
	j = 0;
	while (cylinder_count > j)
	{
		printf("Cylinder %d\n", j + 1);
		printf("data.set.cy[%d].coords.x: %f\n", j, data->set.cy[j].coords.x);
		printf("data.set.cy[%d].coords.y: %f\n", j, data->set.cy[j].coords.y);
		printf("data.set.cy[%d].coords.z: %f\n", j, data->set.cy[j].coords.z);
		printf("data.set.cy[%d].normalized.x: %f\n", j, data->set.cy[j].normalized.x);
		printf("data.set.cy[%d].normalized.y: %f\n", j, data->set.cy[j].normalized.y);
		printf("data.set.cy[%d].normalized.z: %f\n", j, data->set.cy[j].normalized.z);
		printf("data.set.cy[%d].diameter: %f\n", j, data->set.cy[j].diameter);
		printf("data.set.cy[%d].height: %f\n", j, data->set.cy[j].height);
		printf("data.set.cy[%d].color.x: %f\n", j, data->set.cy[j].color.x);
		printf("data.set.cy[%d].color.y: %f\n", j, data->set.cy[j].color.y);
		printf("data.set.cy[%d].color.z: %f\n", j, data->set.cy[j].color.z);
		printf("\n\n");
		j++;
	}
}

char	*clean_line(char *line)
{
	int		i;
	int		j;
	int		in_space;
	char	*result;
	char	*trimmed_result;

	in_space = 0;
	if (!line)
		return (NULL);
	result = malloc(ft_strlen(line) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == ' ')
		{
			if (!in_space)
			{
				result[j++] = ' ';
				in_space = 1;
			}
		}
		else
		{
			result[j++] = line[i];
			in_space = 0;
		}
		i++;
	}
	result[j] = '\0';
	trimmed_result = ft_strtrim(result, " ");
	free(result);
	return (trimmed_result);
}

int	check_param_nbr(char **line)
{
	int	count_a;
	int	count_c;
	int	count_l;
	int	i;

	i = 0;
	count_a = 0;
	count_c = 0;
	count_l = 0;
	while (line[i] != NULL)
	{
		if (ft_strncmp(line[i], "A ", 2) == 0)
			count_a++;
		else if (ft_strncmp(line[i], "C ", 2) == 0)
			count_c++;
		else if (ft_strncmp(line[i], "L ", 2) == 0)
			count_l++;
		i++;
	}
	if (count_a == 1 && count_c == 1 && count_l == 1)
		return (0);
	else
	{
		printf("Error: Wrong number of parameters\n");
		return (1);
	}
}

int	read_rt_file(int fd, t_data *data, char *argv)
{
	int		i;
	int		rows;
	char	**line;
	int		sphere_count;
	int		plane_count;
	int		cylinder_count;

	i = 0;
	rows = 0;
	while (get_next_line(fd))
		rows++;
	close(fd);
	line = malloc(sizeof(char *) * (rows + 1));
	fd = open(argv, O_RDONLY);
	while (i < rows)
	{
		line[i] = get_next_line(fd);
		if (!line[i])
			break ;
		line[i] = clean_line(line[i]);
		i++;
	}
	line[i] = NULL;
	check_param_nbr(line);
	i = 0;
	sphere_count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "sp", 2) == 0)
			sphere_count++;
		i++;
	}
	data->set.sp = malloc(sizeof(t_sphere) * sphere_count);
	i = 0;
	plane_count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "pl", 2) == 0)
			plane_count++;
		i++;
	}
	data->set.pl = malloc(sizeof(t_plane) * plane_count);
	i = 0;
	cylinder_count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "cy", 2) == 0)
			cylinder_count++;
		i++;
	}
	data->set.cy = malloc(sizeof(t_cylinder) * cylinder_count);
	i = 0;
	while (line[i] != NULL)
	{
		parse_line(data, &line[i]);
		i++;
	}
	print_struct(data, sphere_count, plane_count, cylinder_count);
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
	if (read_rt_file(fd, data, argv))
		return (0);
	return (1);
}
